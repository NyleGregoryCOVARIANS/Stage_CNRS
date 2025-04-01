#include "threadmesure.h"
#include <QDebug>

ThreadMesure::ThreadMesure(Communication *communication, QObject *parent)
    : QObject(parent), m_communication(communication) {}

void ThreadMesure::doWork()
{
    // Exemple de mesure (vous pouvez adapter)
    m_communication->envoyer("MEASURE");  // Envoi de la commande de mesure
    QString result = m_communication->recevoir();  // Lecture du résultat

    emit resultReady(result);  // Envoi du résultat au thread principal
}
