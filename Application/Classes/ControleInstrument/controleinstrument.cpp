#include "controleinstrument.h"
#include <QDebug>

ControleInstrument::ControleInstrument(Communication* communicationSPECS,
                                       Communication* communicationPICO,
                                       QObject *parent)
    : QObject(parent),
    m_communicationSPECS(communicationSPECS),
    m_communicationPICO(communicationPICO)
{
}


void ControleInstrument::attenteAsynchrone(int millisecondes)
{
    if (QThread::currentThread() != qApp->thread()) {
        // Si on est dans un thread secondaire
        QThread::msleep(millisecondes);
    } else {
        // Si on est dans le thread principal (GUI)
        QEventLoop loop;
        QTimer::singleShot(millisecondes, &loop, SLOT(quit()));
        loop.exec();
    }
}



void ControleInstrument::validate_button_clickedSPECS(const QString& energie,
                                            const QString& courantEmission,
                                            const QString& focus,
                                            const QString& wehnelt,
                                            const QString& posX,
                                            const QString& posY,
                                            const QString& balayageX,
                                            const QString& balayageY)
{
    QString valTemp;

    if (!energie.isEmpty()) {
        m_communicationSPECS->envoyer("EN " + energie);
        valTemp = m_communicationSPECS->recevoir();
        qDebug() << "Energie : " + energie + " | Réponse : " + valTemp;
    }

    if (!courantEmission.isEmpty()) {
        int courantInt = courantEmission.toInt() * 100;
        m_communicationSPECS->envoyer("EC " + QString::number(courantInt));
        qDebug() << "Courant d'émission : " << courantInt;
    }

    if (!focus.isEmpty()) {
        int focusInt = focus.toInt() * 100;
        m_communicationSPECS->envoyer("F1 " + QString::number(focusInt));
        qDebug() << "Focus : " << focusInt;
    }

    if (!wehnelt.isEmpty()) {
        int wehneltInt = wehnelt.toInt() * 10;
        m_communicationSPECS->envoyer("WE " + QString::number(wehneltInt));
        valTemp = m_communicationSPECS->recevoir();
        qDebug() << "Wehnelt : " << wehneltInt << " | Réponse : " << valTemp;
    }

    if (!posX.isEmpty()) {
        int posXInt = posX.toInt() * 100;
        m_communicationSPECS->envoyer("X0 " + QString::number(posXInt));
        qDebug() << "Position X : " << posXInt;
    }

    if (!posY.isEmpty()) {
        int posYInt = posY.toInt() * 100;
        m_communicationSPECS->envoyer("Y0 " + QString::number(posYInt));
        qDebug() << "Position Y : " << posYInt;
    }

    if (!balayageX.isEmpty()) {
        int balayageXInt = balayageX.toInt() * 10;
        m_communicationSPECS->envoyer("WX " + QString::number(balayageXInt));
        qDebug() << "Balayage X : " << balayageXInt;
    }

    if (!balayageY.isEmpty()) {
        int balayageYInt = balayageY.toInt() * 10;
        m_communicationSPECS->envoyer("WY " + QString::number(balayageYInt));
        qDebug() << "Balayage Y : " << balayageYInt;
    }

    qDebug() << "Alimentation SPECS mise à jour";
}

void ControleInstrument::validate_button_clickedPICO(

    const QString& EnergieMin,
    const QString& EnergieMax,
    const QString& Pas,
    const QString& Duree)
{


    qDebug() << "[BALAYAGE] Thread ID =" << QThread::currentThread();


    if (EnergieMin.isEmpty() || EnergieMax.isEmpty() || Pas.isEmpty() || Duree.isEmpty()) {
        qDebug() << "Tous les champs doivent être remplis.";
        return;
    }

    double eMin = EnergieMin.toDouble();
    double eMax = EnergieMax.toDouble();
    double pas = Pas.toDouble();
    int duree = Duree.toInt(); // en secondes

    qDebug() << "EnergieMin :" << eMin;
    qDebug() << "EnergieMax :" << eMax;
    qDebug() << "Pas :" << pas;
    qDebug() << "Duree :" << duree;



    int i = 0;
    while(i < 10){
        m_communicationPICO->envoyer("READ?");
        qDebug() <<"AAAAAAAAAAAAAAAAAAAAAAAAAAA" << m_communicationPICO->recevoirKeithley6485();
        attenteAsynchrone(3000);
        i++;
    }



    /*
        for (double energie = eMin; energie <= eMax; energie += pas) {
            m_communicationSPECS->envoyer("EN " + QString::number(energie));
            qDebug() << "Energie appliquée :" << energie;
            attenteAsynchrone(5000);  // ← 5 secondes


            qDebug() << m_communicationPICO->obtenirPort();
            if (!m_communicationPICO) {
                qDebug() << "❌ m_communicationPICO est null !";
                return;
            }




            m_communicationPICO->envoyer("READ?");
            qDebug() <<"AAAAAAAAAAAAAAAAAAAAAAAAAAA : " << m_communicationPICO->recevoirKeithley6485();





            int i = 0;
            while(i < 10){
                m_communicationPICO->envoyer("READ?");
                qDebug() <<"Intensité mesuré : " << m_communicationPICO->recevoirKeithley6485();
                attenteAsynchrone(1000);
                i++;
            }
            */









            //m_communicationPICO->envoyer("READ?");
            //m_communicationSPECS->envoyer("EN ?");
}




// Active le mode Operate quand la case est cochée.
void ControleInstrument::on_checkBoxOperate_toggled(bool checked)
{
    if (checked) {
        qDebug() << "Activation du mode OPERATE";
        m_communicationSPECS->envoyer("OP 1");
    } else {
        m_communicationSPECS->envoyer("SB 1");
        qDebug() << "Désactivation du mode OPERATE";
    }
}

// Active le mode Haute Tension quand la case est cochée.
void ControleInstrument::on_checkBoxHV_toggled(bool checked)
{

        if (checked) {
            m_communicationSPECS->envoyer("HE 2");
            qDebug() << "Activation du mode Haute Tension";
        } else {
            m_communicationSPECS->envoyer("HA 2");
            qDebug() << "Désactivation du mode Haute Tension";
        }

}


void ControleInstrument::initialisationPICO(Communication *communicationPICO)
{

    if (this != nullptr) {
        qDebug() << "this = " << this;
    }

    qDebug() << "communicationPICO = " << communicationPICO;

    if (!communicationPICO) {
        qDebug() << "❌ ERREUR : communicationPICO est nullptr";
    }
    qDebug() << "Port : " << communicationPICO->obtenirPort();

    m_communicationPICO = communicationPICO;

    qDebug() << "--------------OPERATION PICO-----------------";
    m_communicationPICO->envoyer("*RST");
    m_communicationPICO->envoyer("SYST:ZCH ON");
    m_communicationPICO->envoyer("CURR:RANG:AUTO ON");
    m_communicationPICO->envoyer("INIT");
    m_communicationPICO->envoyer("SYST:ZCOR:ACQ");
    m_communicationPICO->envoyer("SYST:ZCOR ON");
    m_communicationPICO->envoyer("CURR:RANG:AUTO ON");
    m_communicationPICO->envoyer("SYST:ZCH OFF");


    m_communicationPICO->envoyer("CURR:NPLC 0.01");

}


void ControleInstrument::initialisationSPECS(Communication *m_communicationSPECS){
    qDebug() << "Activation du mode REMOTE";
    m_communicationSPECS->envoyer("RE");
}
