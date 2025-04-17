#include "ReleverMesure.h"
#include <QDebug>

// Constructeur
ReleverMesure::ReleverMesure(Communication *communicationSPECS, Communication *communicationPICO , QObject *parent)
    : QObject(parent), m_communication_SPECS(communicationSPECS), m_communication_PICO(communicationPICO)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ReleverMesure::actualisationMesuresSPECS);
}

// Destructeur
ReleverMesure::~ReleverMesure()
{
    delete m_timer;
}

// Lance le timer avec un intervalle de 5 secondes pour rafraîchir les mesures périodiquement
void ReleverMesure::start()
{
    if (!m_timer->isActive()) {
        m_timer->start(5000);  // Lance uniquement si le timer est inactif
        qDebug() << "Timer lancé.";
    } else {
        qDebug() << "Timer déjà actif, lancement ignoré.";
    }
}

// Stop le timer
void ReleverMesure::stop()
{
    m_timer->stop();
}


// Envoie des requêtes pour récupérer les paramètres de l'alimentation, émet un signal contenant les valeurs reçues, puis démarre un timer pour répéter ce processus toutes les 5 secondes.
void ReleverMesure::actualisationMesuresSPECS()
{
    qDebug() << "ACTUALISATION: Début de la mise à jour des mesures.";

    QString resultatRequeteEnergie, resultatRequeteCourantEmission, resultatRequeteFocus, resultatRequeteWehnelt;
    QString resultatRequetePosX, resultatRequetePosY, resultatRequeteBalX, resultatRequeteBalY;

    // Envoi des commandes et réception des valeurs
    m_communication_SPECS->envoyer("EN ?");resultatRequeteEnergie = m_communication_SPECS->recevoir();
    m_communication_SPECS->envoyer("EC ?");resultatRequeteCourantEmission = m_communication_SPECS->recevoir();
    m_communication_SPECS->envoyer("F1 ?");resultatRequeteFocus = m_communication_SPECS->recevoir();
    m_communication_SPECS->envoyer("WE ?");resultatRequeteWehnelt = m_communication_SPECS->recevoir();
    m_communication_SPECS->envoyer("X0 ?");resultatRequetePosX = m_communication_SPECS->recevoir();
    m_communication_SPECS->envoyer("Y0 ?");resultatRequetePosY = m_communication_SPECS->recevoir();
    m_communication_SPECS->envoyer("WX ?");resultatRequeteBalX = m_communication_SPECS->recevoir();
    m_communication_SPECS->envoyer("WY ?"); resultatRequeteBalY = m_communication_SPECS->recevoir();

    /*
    // Affichage des résultats dans le débogage pour toutes les valeurs
    qDebug() << "Résultat énergie : " << resultatRequeteEnergie;
    qDebug() << "Résultat courant émission : " << resultatRequeteCourantEmission;
    qDebug() << "Résultat focus : " << resultatRequeteFocus;
    qDebug() << "Résultat Wehnelt : " << resultatRequeteWehnelt;
    qDebug() << "Résultat position X : " << resultatRequetePosX;
    qDebug() << "Résultat position Y : " << resultatRequetePosY;
    qDebug() << "Résultat balayage X : " << resultatRequeteBalX;
    qDebug() << "Résultat balayage Y : " << resultatRequeteBalY;
    */

    // Émission du signal avec les résultats obtenus
    emit transmissionResultatSPECS(resultatRequeteEnergie, resultatRequeteCourantEmission,
                                  resultatRequeteFocus, resultatRequeteWehnelt,
                                  resultatRequetePosX, resultatRequetePosY,
                                  resultatRequeteBalX, resultatRequeteBalY);

    // Redémarre le timer pour maintenir la mise à jour périodique
    this->start();
}


