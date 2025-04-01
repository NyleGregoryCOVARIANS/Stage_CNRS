#include "fenetreconnexion.h"
#include "ui_fenetreconnexion.h"
#include <iostream>
#include <QTimer>

#include <QDebug>

FenetreConnexion::FenetreConnexion(QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::FenetreConnexion)
{
    m_ui->setupUi(this);
}


FenetreConnexion::FenetreConnexion(QWidget *parent, Communication *communication)
    : QDialog(parent)
    , m_ui(new Ui::FenetreConnexion)
{
    m_ui->setupUi(this);

    // Recuperation des infos depuis l'interface
    m_com = m_ui->lineEdit->text();
    m_baudRate = m_ui->comboBox->currentText();

    m_communication = communication;
}

FenetreConnexion::~FenetreConnexion()
{
    delete m_ui;
}


// Se connecte à l'alimentation, active le control à distance et actualise
void FenetreConnexion::on_pushButton_rs232_clicked()
{
    m_com = m_ui->lineEdit->text();
    m_baudRate = m_ui->comboBox->currentText();
    bool estConnecte = m_communication->connexion(m_com, m_baudRate);

    m_communication->envoyer("RE"); // Activation du remote
    qDebug() << m_communication->recevoir();

    m_communication->envoyer("HE 2"); // Activation du haut voltage
    qDebug() << m_communication->recevoir();

    m_communication->envoyer("OP 1"); // Activation du haut voltage
    qDebug() << m_communication->recevoir();

    qDebug() << "--------------------------------";
    qDebug() << "Suis-je connecte ? " + QVariant(estConnecte).toString();
    qDebug() << "m_com : " + m_com;
    qDebug() << "m_baudRate : " + m_baudRate;


    // Récupère les paramètres et les affiches toutes les 5 secondes
    ActualisationMesures();
    if (!m_timer) {
        m_timer = new QTimer(this);  // Assurez-vous que m_timer est bien initialisé
    }
    connect(m_timer, &QTimer::timeout, this, &FenetreConnexion::ActualisationMesures); // Connecter le signal timeout du timer à la fonction ActualisationMesures
    m_timer->start(10000);     // Lancer le timer pour exécuter la fonction toutes les 1000 ms (5 seconde)


    this->hide();
}


// Récupère tous les paramètres de l'alimentation et les transmets à mainWindow
void FenetreConnexion::ActualisationMesures(){
    qDebug() << "ACTUALISATION";


    // Initialisation des variables
    QString resultatRequeteEnergie;
    QString resultatRequeteCourantEmission;
    QString resultatRequeteFocus;
    QString resultatRequeteWehnelt;
    QString resultatRequetePosX;
    QString resultatRequetePosY;
    QString resultatRequeteBalX;
    QString resultatRequeteBalY;




    // Demande de récupérer l'énergie actuelle et l'affiche
    m_communication->envoyer("EN ?");
    resultatRequeteEnergie = m_communication->recevoir();
    qDebug() << "Résultat de la requête energie est : " + resultatRequeteEnergie;

    // Demande de récupérer le courant d'émission actuelle et l'affiche
    m_communication->envoyer("EC ?");
    resultatRequeteCourantEmission = m_communication->recevoir();
    qDebug() << "Résultat de la requête courant emission est : " + resultatRequeteCourantEmission;

    // Demande de récupérer le focus actuelle et l'affiche
    m_communication->envoyer("F1 ?");
    resultatRequeteFocus = m_communication->recevoir();
    qDebug() << "Résultat de la requête focus est : " + resultatRequeteFocus;

    // Demande de récupérer le wehnelt actuelle et l'affiche
    m_communication->envoyer("WE ?");
    resultatRequeteWehnelt = m_communication->recevoir();
    qDebug() << "Résultat de la requête wehnelt est : " + resultatRequeteWehnelt;

    // Demande de récupérer la position X et l'affiche
    m_communication->envoyer("X0 ?");
    resultatRequetePosX = m_communication->recevoir();
    qDebug() << "Résultat de la requête Pos X est : " + resultatRequetePosX;

    // Demande de récupérer la position Y et l'affiche
    m_communication->envoyer("Y0 ?");
    resultatRequetePosY = m_communication->recevoir();
    qDebug() << "Résultat de la requête Pos Y est : " + resultatRequetePosY;

    // Demande de récupérer le balayage X et l'affiche
    m_communication->envoyer("WX ?");
    resultatRequeteBalX = m_communication->recevoir();
    qDebug() << "Résultat de la requête bal X est : " + resultatRequeteBalX;

    // Demande de récupérer le balayage Y et l'affiche
    m_communication->envoyer("WY ?");
    resultatRequeteBalY = m_communication->recevoir();
    qDebug() << "Résultat de la requête balY est : " + resultatRequeteBalY;

    // transmission des paramètres
    emit transmissionResultatPret(resultatRequeteEnergie, resultatRequeteCourantEmission, resultatRequeteFocus, resultatRequeteWehnelt, resultatRequetePosX,
     resultatRequetePosY,resultatRequeteBalX, resultatRequeteBalY);

}
