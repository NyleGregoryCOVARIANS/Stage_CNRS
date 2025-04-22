#include "controleinstrument.h"
#include <QDebug>

ControleInstrument::ControleInstrument(Communication* communicationSPECS, QObject *parent)
    : QObject(parent), m_communicationSPECS(communicationSPECS)
{

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

void ControleInstrument::validate_button_clickedPICO(        const QString& EnergieMin,
                                                const QString& EnergieMax,
                                                const QString& Pas,
                                                const QString& Duree) {
    if (!EnergieMin.isEmpty()) {
        qDebug() << "EnergieMin : " << EnergieMin;
    }

    if (!EnergieMax.isEmpty()) {
        qDebug() << "EnergieMax : " << EnergieMax;
    }

    if (!Pas.isEmpty()) {
        qDebug() << "Pas : " << Pas;
    }

    if (!Duree.isEmpty()) {
        qDebug() << "Duree : " << Duree;
    }

    qDebug() << "Alimentation PICO mise à jour";
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


void ControleInstrument::initialisationPICO(Communication *m_communicationPICO){
        qDebug() << "--------------OPERATION PICO-----------------";

        // Réinitialisation de l'appareil
        m_communicationPICO->envoyer("*RST");

        // Activer le Zero Check
        m_communicationPICO->envoyer("SYST:ZCH ON");

        // Plage fixe
        m_communicationPICO->envoyer("CURR:RANG:AUTO ON");

        // Initier la mesure pour capter l'offset
        m_communicationPICO->envoyer("INIT");

        // Acquisition de la correction de zéro
        m_communicationPICO->envoyer("SYST:ZCOR:ACQ");

        // Activer la correction de zéro
        m_communicationPICO->envoyer("SYST:ZCOR ON");

        // Remettre en auto-range
        m_communicationPICO->envoyer("CURR:RANG:AUTO ON");

        // Désactiver le Zero Check
        m_communicationPICO->envoyer("SYST:ZCH OFF");

}

void ControleInstrument::initialisationSPECS(Communication *m_communicationSPECS){
    qDebug() << "Activation du mode REMOTE";
    m_communicationSPECS->envoyer("RE");
}
