#pragma once

#include <QObject>
#include "Classes/Communication/communication.h"

class WorkerReleve : public QObject
{
    Q_OBJECT
public:
    WorkerReleve(Communication* comSpecs, Communication* comPico);

public slots:
    void effectuerReleve();

signals:
    void mesureTerminee(QString, QString, QString, QString,
                        QString, QString, QString, QString, QString);

private:
    Communication* m_comSpecs;
    Communication* m_comPico;
};
