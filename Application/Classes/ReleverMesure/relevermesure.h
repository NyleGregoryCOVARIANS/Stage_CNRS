#ifndef RELEVERMESURE_H
#define RELEVERMESURE_H

#include <QObject>
#include <QTimer>
#include "Classes/Communication/communication.h"

class ReleverMesure : public QObject
{
    Q_OBJECT

public:
    explicit ReleverMesure(Communication *communication, QObject *parent = nullptr);
    ~ReleverMesure();

    void start();
    void stop();

signals:
    void transmissionResultatPret(QString CurrentEnergie, QString CurrentCourantEmission, QString CurrentFocus, QString CurrentWehnelt,
                                  QString CurrentPosX, QString CurrentPosY, QString CurrentBalX, QString CurrentBalY);

public slots:
    void actualisationMesures();

private:
    Communication *m_communication;
    QTimer *m_timer;
};

#endif // RELEVERMESURE_H
