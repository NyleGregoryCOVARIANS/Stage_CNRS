#include "mainwindow.h"
#include "Fenetres/Connexion/fenetreconnexion.h" // Inclure la bonne classe
#include "ui_mainwindow.h"
#include <string>
#include <QDebug>
#include "Classes/ReleverMesure/relevermesure.h"  // Ajoute l'inclusion de la nouvelle classe
#include <QCheckBox>
#include "Classes/ControleInstrument/controleinstrument.h"


// Constructeur
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    // Initialisation des objets principaux
    m_ui->setupUi(this);
    m_communication_SPECS = new Communication();
    m_communication_PICO = new Communication();

    m_communication_SPECS = new Communication();
    m_communication_PICO = new Communication();

    m_controleInstrument = new ControleInstrument(m_communication_SPECS, this);

    m_fenetreConnexion = new FenetreConnexion(this, m_communication_SPECS,m_communication_PICO);

    // Implématation d'un thread
    m_releverMesure = new ReleverMesure(m_communication_SPECS, m_communication_PICO, nullptr);
    // Création du thread de mesure
    m_threadMesure = new QThread(this); // pour que le thread soit détruit automatiquement avec MainWindow
    m_releverMesure->moveToThread(m_threadMesure);


    // Ferme proprement le thread à la fermeture de MainWindow
    connect(this, &MainWindow::destroyed, m_threadMesure, &QThread::quit);
    connect(m_threadMesure, &QThread::finished, m_releverMesure, &QObject::deleteLater);
    connect(m_threadMesure, &QThread::finished, m_threadMesure, &QObject::deleteLater);


    connect(m_fenetreConnexion, &FenetreConnexion::connexionEtablie, this, [=]() {
        if (!m_threadMesure->isRunning()) {
            m_threadMesure->start(); // Lance le thread si pas encore lancé
        }
        QMetaObject::invokeMethod(m_releverMesure, "start", Qt::QueuedConnection); // Lance les mesures dans le bon thread
    });


    // Connexions : Signaux et Slots
    connect(m_fenetreConnexion, &FenetreConnexion::connexionEtablie,
            m_releverMesure, &ReleverMesure::actualisationMesuresSPECS); // Dès que l'utilisateur se connecte, on relève une mesure.

    connect(m_releverMesure, &ReleverMesure::transmissionResultatSPECS,
            this, &MainWindow::affichageResultatRecuSPECS); // Dès qu'une mesure est réalisée, on affiche les paramètres correspondants dans l'interface.

    connect(m_ui->pushButtonConnexion, &QPushButton::clicked, // Dès que l'utilisateur clique sur le bouton "Connexion", on affiche la fenêtre de connexion
            this, &MainWindow::connexion_button_clicked);


    // Dès que l'utilisateur clique sur le bouton "Valider" de l'onglet SPECS, on met à jour l'alimentation SPECS avec les paramètres correspondants.

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

    connect(m_ui->checkBoxOperate, &QCheckBox::toggled,
            m_controleInstrument, &ControleInstrument::on_checkBoxOperate_toggled);

    connect(m_ui->checkBoxHV, &QCheckBox::toggled,
            m_controleInstrument, &ControleInstrument::on_checkBoxHV_toggled);

    connect(m_ui->ValidatePushButtonPICO, &QPushButton::clicked, this, [=]() {
        m_controleInstrument->validate_button_clickedPICO(
            m_ui->lineEditEnergieMinimum->text(),
            m_ui->lineEditEnergieMaximum->text(),
            m_ui->lineEditPas->text(),
            m_ui->lineEditDuree->text()
            );
    });




    this->show(); // Affiche la fenêtre main Window
}

// Récupère les paramètres de l'alimentation SPECS, règle les problèmes d'échelles, et affiche les paramètres sur l'application
void MainWindow::affichageResultatRecuSPECS(QString CurrentEnergie, QString CurrentCourantEmission, QString CurrentFocus, QString CurrentWehnelt,
                                          QString CurrentPosX, QString CurrentPosY, QString CurrentBalX, QString CurrentBalY, QString CurrentCourant) {

    // Pas de problème d'échelle. Ainsi, affichage des paramètres
    m_ui->valeurMesurerEnergie->setText(CurrentEnergie + "eV");
    m_ui->valeurMesurerFocus->setText(CurrentFocus + " V");


    // Correction de l'échelle et affichage des paramètres de SPECS
    m_ui->valeurMesurerCourantEmission->setText(QString::number(CurrentCourantEmission.toFloat() / 100) + " µA");
    m_ui->valeurMesurerFocusEv->setText(QString::number((CurrentFocus.toFloat() / CurrentEnergie.toFloat()) * 100) + " %");
    m_ui->valeurMesurerWehnelt->setText(QString::number(CurrentWehnelt.toFloat() / 10) + " V");
    m_ui->valeurMesurerPositionX->setText(QString::number(CurrentPosX.toFloat() / 1000) + " mm");
    m_ui->valeurMesurerPositionY->setText(QString::number(CurrentPosY.toFloat() / 1000) + " mm");
    m_ui->valeurMesurerBalayageX->setText(QString::number(CurrentBalX.toFloat() / 1000) + " mm");
    m_ui->valeurMesurerBalayageY->setText(QString::number(CurrentBalY.toFloat() / 1000) + " mm");


    // Affichage du courant
    m_ui->labelIntensite->setText("Intensité : " + CurrentCourant);
    m_ui->labelIntensite_2->setText("Intensité : " + CurrentCourant);

}



// Affiche la fenetre de connexion
void MainWindow::connexion_button_clicked(){
    m_fenetreConnexion->show();
}

// Destructeur
MainWindow::~MainWindow()
{
    delete m_fenetreConnexion;
}
