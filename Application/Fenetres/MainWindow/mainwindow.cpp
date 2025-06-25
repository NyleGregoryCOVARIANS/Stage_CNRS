#include "mainwindow.h"
#include "Fenetres/Connexion/fenetreconnexion.h"
#include "ui_mainwindow.h"
#include <string>
#include <QDebug>
#include "Classes/ReleverMesure/relevermesure.h"
#include <QCheckBox>
#include "Classes/ControleInstrument/controleinstrument.h"
#include "Classes/Graphique/qcustomplot.h"
#include <QtMath>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_communication_SPECS = new Communication();
    m_communication_PICO = new Communication();
    m_controleInstrument = new ControleInstrument(m_communication_SPECS, m_communication_PICO, nullptr);
    m_fenetreConnexion = new FenetreConnexion(this, m_communication_SPECS, m_communication_PICO);
    m_customPlot = m_ui->customPlot;
    if (!m_customPlot) {
        qDebug() << "Erreur : m_customPlot non trouvé dans l'interface.";
    }
    m_releverMesure = new ReleverMesure(m_communication_SPECS, m_communication_PICO, nullptr);
    m_threadMesure = new QThread(this);
    m_releverMesure->moveToThread(m_threadMesure);
    connect(this, &MainWindow::destroyed, m_threadMesure, &QThread::quit);
    connect(m_threadMesure, &QThread::finished, m_releverMesure, &QObject::deleteLater);
    connect(m_threadMesure, &QThread::finished, m_threadMesure, &QObject::deleteLater);
    connect(m_fenetreConnexion, &FenetreConnexion::connexionEtablie, this, [=]() {
        if (!m_threadMesure->isRunning()) m_threadMesure->start();
        QMetaObject::invokeMethod(m_releverMesure, "start", Qt::QueuedConnection);
    });
    connect(m_releverMesure, &ReleverMesure::transmissionResultatSPECS, this, &MainWindow::affichageResultatRecuSPECS);
    connect(m_ui->pushButtonConnexion, &QPushButton::clicked, this, &MainWindow::connexion_button_clicked);
    connect(m_ui->ValidatePushButtonSPECS, &QPushButton::clicked, this, [=]() {
        m_controleInstrument->validate_button_clickedSPECS(
            m_ui->lineEditEnergie->text().trimmed(),
            m_ui->lineEditCourantEmission->text().trimmed(),
            m_ui->lineEditFocus->text().trimmed(),
            m_ui->lineEditWehnelt->text().trimmed(),
            m_ui->lineEditPositionX->text().trimmed(),
            m_ui->lineEditPositionY->text().trimmed(),
            m_ui->lineEditBalayageX->text().trimmed(),
            m_ui->lineEditBalayageY->text().trimmed()
            );
    });
    connect(m_ui->checkBoxOperate, &QCheckBox::toggled, m_controleInstrument, &ControleInstrument::on_checkBoxOperate_toggled);
    connect(m_ui->checkBoxHV, &QCheckBox::toggled, m_controleInstrument, &ControleInstrument::on_checkBoxHV_toggled);
    connect(m_ui->ValidatePushButtonPICO, &QPushButton::clicked, this, [=]() {
        m_controleInstrument->validate_button_clickedPICO(
            m_ui->lineEditEnergieMinimum->text(),
            m_ui->lineEditEnergieMaximum->text(),
            m_ui->lineEditPas->text(),
            m_ui->lineEditDuree->text()
            );
        updateCurve(); // Mettre à jour la courbe après le balayage
    });
    connect(m_controleInstrument, &ControleInstrument::balayageStatusChanged, this, &MainWindow::updateBalayageStatus);
    this->show();
}

void MainWindow::affichageResultatRecuSPECS(QString CurrentEnergie, QString CurrentCourantEmission, QString CurrentFocus, QString CurrentWehnelt,
                                            QString CurrentPosX, QString CurrentPosY, QString CurrentBalX, QString CurrentBalY, QString CurrentCourant) {
    m_ui->valeurMesurerEnergie->setText(CurrentEnergie + "eV");
    m_ui->valeurMesurerFocus->setText(CurrentFocus + " V");
    m_ui->valeurMesurerCourantEmission->setText(QString::number(CurrentCourantEmission.toFloat() / 100) + " µA");
    m_ui->valeurMesurerFocusEv->setText(QString::number((CurrentFocus.toFloat() / CurrentEnergie.toFloat()) * 100) + " %");
    m_ui->valeurMesurerWehnelt->setText(QString::number(CurrentWehnelt.toFloat() / 10) + " V");
    m_ui->valeurMesurerPositionX->setText(QString::number(CurrentPosX.toFloat() / 1000) + " mm");
    m_ui->valeurMesurerPositionY->setText(QString::number(CurrentPosY.toFloat() / 1000) + " mm");
    m_ui->valeurMesurerBalayageX->setText(QString::number(CurrentBalX.toFloat() / 1000) + " mm");
    m_ui->valeurMesurerBalayageY->setText(QString::number(CurrentBalY.toFloat() / 1000) + " mm");
    m_ui->labelIntensite->setText("Intensité : " + CurrentCourant);
    m_ui->labelIntensite_2->setText("Intensité : " + CurrentCourant);
}

void MainWindow::updateCurve()
{
    m_customPlot->clearGraphs();
    m_customPlot->clearPlottables();

    m_customPlot->addGraph();
    QVector<double> x, y;

    QFile file("C:/Users/Mesure/Documents/Nyle/mesures_pico.csv");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QVector<QStringList> secondTableData; // Stocker toutes les lignes du second tableau
        QString lastPolarization;

        bool firstLine = true;
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (firstLine) {
                firstLine = false;
                if (line.contains("Date et heure;Temps ecoule (s);Energie (eV);Polarisation;Intensite brute;;"
                                  "Energie (eV);Intensite moyenne (+50V);Intensite moyenne (-50V);SEY")) {
                    continue; // Ignorer l'en-tête
                }
            }
            QStringList parts = line.split(";;");
            if (parts.size() >= 1) {
                QStringList firstPart = parts[0].split(";");
                if (firstPart.size() >= 4) {
                    lastPolarization = firstPart[3]; // Stocker la dernière polarisation vue
                }
                if (parts.size() >= 2) {
                    QStringList values = parts[1].split(";");
                    if (values.size() >= 4) { // Vérifier qu'il y a assez de colonnes
                        secondTableData.append(values);
                    }
                }
            }
        }
        file.close();

        // Prendre les données du dernier balayage (basé sur la dernière polarisation)
        int startIndex = 0;
        if (lastPolarization == "-50V") {
            startIndex = qMax(0, secondTableData.size() - 12); // 12 lignes pour -50V (ajustable)
        } else if (lastPolarization == "+50V") {
            startIndex = qMax(0, secondTableData.size() - 24); // 24 lignes pour +50V (ajustable)
        }
        for (int i = startIndex; i < secondTableData.size(); ++i) {
            bool okEnergie, okSEY;
            double energie = secondTableData[i][0].toDouble(&okEnergie); // Colonne 1 : Energie
            double sey = secondTableData[i][3].toDouble(&okSEY);        // Colonne 4 : SEY
            if (okEnergie && okSEY && !secondTableData[i][3].isEmpty()) {
                x.append(energie);
                y.append(sey);
            }
        }
    } else {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier mesures_pico.csv";
        // Courbe par défaut en cas d'échec
        for (int i = 0; i < 100; ++i) {
            x.append(i * 0.1);
            y.append(qSin(i * 0.1));
        }
    }

    m_customPlot->graph(0)->setData(x, y);
    m_customPlot->xAxis->setLabel("Energie (eV)");
    m_customPlot->yAxis->setLabel("SEY");
    if (!x.isEmpty() && !y.isEmpty()) {
        m_customPlot->xAxis->setRange(*std::min_element(x.begin(), x.end()) - 0.5, *std::max_element(x.begin(), x.end()) + 0.5);
        m_customPlot->yAxis->setRange(*std::min_element(y.begin(), y.end()) - 0.1, *std::max_element(y.begin(), y.end()) + 0.1);
    } else {
        m_customPlot->xAxis->setRange(0, 10);
        m_customPlot->yAxis->setRange(-1.5, 1.5);
    }
    m_customPlot->replot();
    m_customPlot->setMinimumSize(400, 300);
}

void MainWindow::connexion_button_clicked()
{
    m_fenetreConnexion->show();
}

MainWindow::~MainWindow()
{
    delete m_fenetreConnexion;
    delete m_communication_SPECS;
    delete m_communication_PICO;
    delete m_ui;
}

void MainWindow::updateBalayageStatus(const QString& status)
{
    m_ui->labelInformationBalayage->setText(status);
}
