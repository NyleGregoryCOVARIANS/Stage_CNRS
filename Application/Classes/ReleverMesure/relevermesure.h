#ifndef RELEVERMESURE_H
#define RELEVERMESURE_H

#include <QObject>
#include <QTimer>
#include "Classes/Communication/communication.h"

class ReleverMesure : public QObject
{
    Q_OBJECT

public:
    explicit ReleverMesure(Communication *m_communication_SPECS, Communication *m_communication_PICO, QObject *parent = nullptr);
    ~ReleverMesure();

    void start();
    void stop();

signals:
    void transmissionResultatSPECS(QString CurrentEnergie, QString CurrentCourantEmission, QString CurrentFocus, QString CurrentWehnelt,
                                  QString CurrentPosX, QString CurrentPosY, QString CurrentBalX, QString CurrentBalY);

public slots:
    void actualisationMesuresSPECS();

private:
    Communication *m_communication_SPECS;
    Communication *m_communication_PICO;
    QTimer *m_timer;
};

#endif // RELEVERMESURE_H
