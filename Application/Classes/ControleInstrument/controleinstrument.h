#ifndef CONTROLEINSTRUMENT_H
#define CONTROLEINSTRUMENT_H

#include <QObject>
#include <QString>
#include "Classes/Communication/communication.h"

class ControleInstrument : public QObject
{
    Q_OBJECT

public:
    explicit ControleInstrument(Communication* communicationSPECS, QObject *parent = nullptr);

    void initialisationSPECS(Communication *m_communicationSPECS);
    void initialisationPICO(Communication *m_communicationPICO);

    void validate_button_clickedSPECS(
        const QString& Energie,
        const QString& CourantEmission,
        const QString& Focus,
        const QString& Wehnelt,
        const QString& PositionX,
        const QString& PositionY,
        const QString& BalayageX,
        const QString& BalayageY
        );


    void validate_button_clickedPICO(
        const QString& EnergieMin,
        const QString& EnergieMax,
        const QString& Pas,
        const QString& Duree
        );


    void on_checkBoxHV_toggled(bool checked);
    void on_checkBoxOperate_toggled(bool checked);


private:
    Communication* m_communicationSPECS;
    Communication* m_communicationPICO;


};

#endif // CONTROLEINSTRUMENT_H
