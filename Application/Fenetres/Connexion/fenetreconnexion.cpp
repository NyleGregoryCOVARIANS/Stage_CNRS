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


    estConnectePICO = m_communication_PICO->connexion(m_com_PICO, m_baudRate_PICO);
    estConnecteSPECS = m_communication_SPECS->connexion(m_com_SPECS, m_baudRate_SPECS);

    if (estConnecteSPECS) {
        m_controleInstrument->initialisationPICO(m_communication_PICO);
        m_controleInstrument->initialisationSPECS(m_communication_SPECS);
        emit connexionEtablie(); // Envoie le signal que la connexion a réussis à MainWindow

    }
    else{
        qDebug() << "Echec de connection SPECS";
    }





    this->hide();
}
