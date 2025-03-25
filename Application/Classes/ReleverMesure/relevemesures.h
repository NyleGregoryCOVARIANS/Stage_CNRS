#ifndef RELEVEMESURES_H
#define RELEVEMESURES_H

#include "Classes/Communication/communication.h"
#include <QtCore>

/*
    Procédure d'acquisition des données
*/
class ReleveMesures : public QObject
{
    Q_OBJECT
public:
    ReleveMesures(Communication *communication);
    ~ReleveMesures();

    /*
        Brief : Permet d'obtenir l'énergie de l'alimentation à canon à électron SPECS
    */
    QString obtenirEnergie(QString identifiant);


public slots:

signals:

private:
    Communication *m_communication;

};

#endif // RELEVEMESURES_H
