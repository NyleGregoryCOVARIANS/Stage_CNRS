#include "mainwindow.h"
#include "Fenetres/Connexion/fenetreconnexion.h" // Inclure la bonne classe
#include "ui_mainwindow.h"

#include <QDebug>

// Constructeur
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this); // Charge l'interface graphique
    m_communication = new Communication(); // Crée une instance de communication
    m_fenetreConnexion = new FenetreConnexion(this, m_communication); // Crée une instance d'une fenêtre de connexion


    connect(m_fenetreConnexion, &FenetreConnexion::transmissionResultatPret, this, &MainWindow::transmissionResultatRecu);
    connect(m_ui->pushButtonConnexion, &QPushButton::clicked, this, &MainWindow::connexion_button_clicked); // Si le bouton connexion est cliqué, alors lance la fonction connexion_button_clicked() qui affiche la fenêtre de connexion
    connect(m_ui->ValidatePushButton, &QPushButton::clicked, this, &MainWindow::validate_button_clicked);
    this->show();
}




void MainWindow::transmissionResultatRecu(QString &CurrentEnergie, QString &CurrentCourantEmission, QString &CurrentFocus, QString &CurrentWehnelt,
                                          QString &CurrentPosX, QString &CurrentPosY, QString &CurrentBalX, QString &CurrentBalY) {
    m_ui->lineEditCourantEmission->setText(CurrentCourantEmission);
    m_ui->lineEditFocus->setText(CurrentFocus);
    m_ui->lineEditEnergie->setText(CurrentEnergie);
    m_ui->lineEditWehnelt->setText(CurrentWehnelt);
    m_ui->lineEditPositionX->setText(CurrentPosX);
    m_ui->lineEditPositionY->setText(CurrentPosY);
    m_ui->lineEditBalayageX->setText(CurrentBalX);
    m_ui->lineEditBalayageY->setText(CurrentBalY);
}






// Récupére les valeurs des editLine et modifie les paramètres de l'alimentation
void MainWindow::validate_button_clicked()
{
    QString x;
    QString y;
    QString z;
    // =========================
    // Modification de l'énergie de l'alimentation ( attention valeur entre 0 et 5000 | eV )
    // =========================
    QString Energie = m_ui->lineEditEnergie->text().trimmed();
    if(!Energie.isEmpty()){
        qDebug() << "-------------------------------------";

        m_communication->envoyer("EN ?");
        x = m_communication->recevoir();
        qDebug() << "Lecture valeur energie avant changement : " + x;

        qDebug() << "-------------------------------------";
        m_communication->envoyer("EN " + Energie); // N'envoie pas la commande
        y = m_communication->recevoir();
        qDebug() << "Energie : " + Energie + " Réponse du changement d'énergie : " + y;

        m_communication->envoyer("EN ?");
        z = m_communication->recevoir();
        qDebug() << "Lecture valeur energie après changement : " + z;

        qDebug() << "-------------------------------------";
    } else {
        qDebug() << "Aucune valeur renseignée pour l'énergie";
    }

    // =========================
    // Modification du courant d'émission ( attention valeur entre 10 et 10000 | mA )
    // =========================
    QString CourantEmission = m_ui->lineEditCourantEmission->text().trimmed();
    if(!CourantEmission.isEmpty()){
        m_communication->envoyer("EC " + CourantEmission);
        qDebug() << "Courant d'émission : " + CourantEmission;
    } else {
        qDebug() << "Aucune valeur renseignée pour le courant d'émission";
    }

    // =========================
    // Modification du focus ( attention valeur entre 0 et 100 | % )
    // =========================
    QString Focus = m_ui->lineEditFocus->text().trimmed();
    if(!Focus.isEmpty()){
        m_communication->envoyer("F1 " + Focus);
        qDebug() << "Focus : " + Focus;
    } else {
        qDebug() << "Aucune valeur renseignée pour le focus";
    }

    // =========================
    // Modification du Wehnelt ( attention valeur entre 0 et 2500 | 1/10 V )
    // =========================
    QString Wehnelt = m_ui->lineEditWehnelt->text().trimmed();
    if(!Wehnelt.isEmpty()){

        m_communication->envoyer("WE ?");
        x = m_communication->recevoir();
        qDebug() << "Lecture valeur Wehnelt avant changement : " + x;

        m_communication->envoyer("WE " + Wehnelt);
        y = m_communication->recevoir();
        qDebug() << "Changement valeur Wehnelt " + y;

        m_communication->envoyer("WE ?");
        z = m_communication->recevoir();
        qDebug() << "Lecture valeur Wehnelt après changement : " + z;

        qDebug() << "Wehnelt : " + Wehnelt;
    } else {
        qDebug() << "Aucune valeur renseignée pour le Wehnelt";
    }

    // =========================
    // Modification de la position X ( attention valeur entre -5000 et 5000 | mm )
    // =========================
    QString PositionX = m_ui->lineEditPositionX->text().trimmed();
    if(!PositionX.isEmpty()){
        m_communication->envoyer("X0 " + PositionX);
        qDebug() << "Position X : " + PositionX;
    } else {
        qDebug() << "Aucune valeur renseignée pour la position X";
    }

    // =========================
    // Modification de la position Y ( attention valeur entre -5000 et 5000 | mm )
    // =========================
    QString PositionY = m_ui->lineEditPositionY->text().trimmed();
    if(!PositionY.isEmpty()){
        m_communication->envoyer("Y0 " + PositionY);
        qDebug() << "Position Y : " + PositionY;
    } else {
        qDebug() << "Aucune valeur renseignée pour la position Y";
    }

    // =========================
    // Modification du balayage X ( attention valeur entre 1 et 200 | V / ° )
    // =========================
    QString BalayageX = m_ui->lineEditBalayageX->text().trimmed();
    if(!BalayageX.isEmpty()){
        m_communication->envoyer("WX " + BalayageX);
        qDebug() << "Balayage X : " + BalayageX;
    } else {
        qDebug() << "Aucune valeur renseignée pour le balayage X";
    }

    // =========================
    // Modification du balayage Y ( attention valeur entre 1 et 200 | V / ° )
    // =========================
    QString BalayageY = m_ui->lineEditBalayageY->text().trimmed();
    if(!BalayageY.isEmpty()){
        m_communication->envoyer("WY " + BalayageY);
        qDebug() << "Balayage Y : " + BalayageY;
    } else {
        qDebug() << "Aucune valeur renseignée pour le balayage Y";
    }

    // =========================
    // Indique que le bouton a été cliqué
    // =========================
    qDebug() << "BOUTON CLIQUE";
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
