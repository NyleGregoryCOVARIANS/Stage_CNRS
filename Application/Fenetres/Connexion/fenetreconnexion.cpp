#include "fenetreconnexion.h"
#include "ui_fenetreconnexion.h"
#include <iostream>
#include "Classes/Communication/communication.h"

#include <QDebug>

FenetreConnexion::FenetreConnexion(QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::FenetreConnexion)
{
    m_ui->setupUi(this);
    m_communication_SPECS = new Communication();
    m_communication_PICO = new Communication();
}

FenetreConnexion::FenetreConnexion(QWidget *parent, Communication *m_communicationSPECS, Communication *m_communicationPICO)
    : QDialog(parent)
    , m_ui(new Ui::FenetreConnexion)
{
    m_ui->setupUi(this);
    m_communication_SPECS = m_communicationSPECS;
    m_communication_PICO = m_communicationPICO;
}


FenetreConnexion::~FenetreConnexion()
{
    delete m_ui;
}


// Se connecte à l'alimentation, active le control à distance et actualise
void FenetreConnexion::on_pushButton_rs232_clicked()
{
    // Récupére le baud rate et le COM
    m_com_SPECS = m_ui->lineEditSPECS->text();
    m_baudRate_SPECS = m_ui->comboBoxSPECS->currentText();

    m_com_PICO = m_ui->lineEditPICO->text();
    m_baudRate_PICO = m_ui->comboBoxPICO->currentText();


    qDebug() << "SPECS port: " << m_communication_SPECS->obtenirPort();
    qDebug() << "PICO port: " << m_communication_PICO->obtenirPort();



    estConnecteSPECS = m_communication_SPECS->connexion(m_com_SPECS, m_baudRate_SPECS);

    if (estConnecteSPECS) {
        qDebug() << "--------------OPERATION SPECS-----------------";
        // Activation du remote
        m_communication_SPECS->envoyer("RE");
        qDebug() << m_communication_SPECS->recevoir();

        qDebug() << "Connexion SPECS réussie !";

        emit connexionEtablie(); // Envoie le signal que la connexion a réussis à MainWindow
        qDebug() << "---------------------------------------";

    }
    else{
        qDebug() << "Echec de connection SPECS";
    }


    estConnectePICO = m_communication_PICO->connexion(m_com_PICO, m_baudRate_PICO);



    if(estConnectePICO){
        qDebug() << "--------------OPERATION PICO-----------------";

        // Réinitialisation de l'appareil
        m_communication_PICO->envoyer("*RST");

        // Activer le Zero Check
        m_communication_PICO->envoyer("SYST:ZCH ON");

        // Plage fixe
        m_communication_PICO->envoyer("CURR:RANG:AUTO ON");

        // Initier la mesure pour capter l'offset
        m_communication_PICO->envoyer("INIT");

        // Acquisition de la correction de zéro
        m_communication_PICO->envoyer("SYST:ZCOR:ACQ");

        // Activer la correction de zéro
        m_communication_PICO->envoyer("SYST:ZCOR ON");

        // Remettre en auto-range
        m_communication_PICO->envoyer("CURR:RANG:AUTO ON");

        // Désactiver le Zero Check
        m_communication_PICO->envoyer("SYST:ZCH OFF");

        float i = 0;
        while (i < 10) {
            m_communication_PICO->envoyer("READ?"); // seulement la valeur mesurée
            QString valeur = m_communication_PICO->recevoirKeithley6485();
            qDebug() << "📏 Courant mesuré : " << valeur;

            QThread::msleep(100); // Pause de 100 ms
            i++;
        }

    }
    else{
        qDebug() << "Echec de connection PICO";
    }


    this->hide();
}
