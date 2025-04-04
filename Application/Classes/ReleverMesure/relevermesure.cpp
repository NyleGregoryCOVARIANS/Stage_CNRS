#include "ReleverMesure.h"
#include <QDebug>

ReleverMesure::ReleverMesure(Communication *communication, QObject *parent)
    : QObject(parent), m_communication(communication)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ReleverMesure::actualisationMesures);
}

ReleverMesure::~ReleverMesure()
{
    delete m_timer;
}

void ReleverMesure::start()
{
    m_timer->start(5000);  // Lancer toutes les 5 secondes
}

void ReleverMesure::stop()
{
    m_timer->stop();
}

void ReleverMesure::actualisationMesures()
{
    qDebug() << "ACTUALISATION: Début de la mise à jour des mesures.";

    QString resultatRequeteEnergie, resultatRequeteCourantEmission, resultatRequeteFocus, resultatRequeteWehnelt;
    QString resultatRequetePosX, resultatRequetePosY, resultatRequeteBalX, resultatRequeteBalY;

    // Envoi des commandes et réception des valeurs
    m_communication->envoyer("EN ?");resultatRequeteEnergie = m_communication->recevoir();
    m_communication->envoyer("EC ?");resultatRequeteCourantEmission = m_communication->recevoir();
    m_communication->envoyer("F1 ?");resultatRequeteFocus = m_communication->recevoir();
    m_communication->envoyer("WE ?");resultatRequeteWehnelt = m_communication->recevoir();
    m_communication->envoyer("X0 ?");resultatRequetePosX = m_communication->recevoir();
    m_communication->envoyer("Y0 ?");resultatRequetePosY = m_communication->recevoir();
    m_communication->envoyer("WX ?");resultatRequeteBalX = m_communication->recevoir();
    m_communication->envoyer("WY ?"); resultatRequeteBalY = m_communication->recevoir();

    // Affichage des résultats dans le débogage pour toutes les valeurs
    qDebug() << "Résultat énergie : " << resultatRequeteEnergie;
    qDebug() << "Résultat courant émission : " << resultatRequeteCourantEmission;
    qDebug() << "Résultat focus : " << resultatRequeteFocus;
    qDebug() << "Résultat Wehnelt : " << resultatRequeteWehnelt;
    qDebug() << "Résultat position X : " << resultatRequetePosX;
    qDebug() << "Résultat position Y : " << resultatRequetePosY;
    qDebug() << "Résultat balayage X : " << resultatRequeteBalX;
    qDebug() << "Résultat balayage Y : " << resultatRequeteBalY;

    // Émission du signal avec les résultats obtenus
    emit transmissionResultatPret(resultatRequeteEnergie, resultatRequeteCourantEmission,
                                  resultatRequeteFocus, resultatRequeteWehnelt,
                                  resultatRequetePosX, resultatRequetePosY,
                                  resultatRequeteBalX, resultatRequeteBalY);

    // Démarre le timer pour la mise à jour continue
    this->start();
}

