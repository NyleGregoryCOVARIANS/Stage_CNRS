#include "fenetreconnexion.h"
#include "ui_fenetreconnexion.h"
#include <iostream>

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

void FenetreConnexion::on_pushButton_rs232_clicked()
{
    m_com = m_ui->lineEdit->text();
    m_baudRate = m_ui->comboBox->currentText();
    bool estConnecte = m_communication->connexion(m_com, m_baudRate);

    m_communication->envoyer("RE"); // Activation du remote
    qDebug() << m_communication->recevoir();

    QString resultatRequeteCourantEmission;
    QString resultatRequeteFocus;

    //Demande de récupérer le courant d'émission actuelle et l'affiche
    m_communication->envoyer("eni");
    resultatRequeteCourantEmission = m_communication->recevoir();
    qDebug() << "Résultat de la requête est : " + resultatRequeteCourantEmission;


    //Demande de récupérer le focus et l'affiche
    m_communication->envoyer("f1i");
    resultatRequeteFocus = m_communication->recevoir();
    qDebug() << "Résultat de la requête est : " + resultatRequeteFocus;
    emit transmissionResultat(resultatRequeteEnergie, resultatRequeteFocus);


    qDebug() << "--------------------------------";
    qDebug() << "Suis-je connecte ? " + QVariant(estConnecte).toString();
    qDebug() << "m_com : " + m_com;
    qDebug() << "m_baudRate : " + m_baudRate;


    this->hide();
}
