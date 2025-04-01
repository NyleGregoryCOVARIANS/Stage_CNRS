#ifndef THREADMESURE_H
#define THREADMESURE_H

#include <QObject>
#include <QThread>
#include <QString>
#include "Classes/Communication/communication.h"

class ThreadMesure : public QObject
{
    Q_OBJECT
public:
    explicit ThreadMesure(Communication *communication, QObject *parent = nullptr);

public slots:
    void doWork();  // Fonction exécutée dans le thread

signals:
    void resultReady(const QString &result);  // Signal pour envoyer les résultats

private:
    Communication *m_communication;  // Pointeur vers l'objet de communication
};

#endif // THREADMESURE_H
