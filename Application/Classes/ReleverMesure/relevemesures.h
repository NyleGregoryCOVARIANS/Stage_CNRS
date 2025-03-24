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

    /*  PAS ENCORE IMPLEMENTER POUR LA V0 -

    // Accesseurs
    int obtenirCycleActuel() const;
    int obtenirTempsEcoule();


    PAS ENCORE IMPLEMENTER POUR LA V0 -

     A l'initialisation -
    QString initialiserDebut();
    QString initialiserNomFichier(QString nomBoitier);
    void creerFichier(QString nomFichier);


    PAS ENCORE IMPLEMENTER POUR LA V0 -


    // A chaque nouvelle mesure
    int incrementerCycleActuel();
    void ajouterLigneFichier(QVector <QString> qvNouvelleMesure, QString dateActuelle);

    */

    /*
        Brief : Permet d'obtenir la pression sur une voie de mesure pour le boitier TPG300
        Args :
            - Identifiant de la voie de mesure ("A1", "A2", "B1" ou "B2")
        Returns : Pression en QString car plus facile a manipuler
    */



    QString obtenirEnergie(QString identifiant);

    /*
        Brief : Permet d'obtenir l'énergie de l'alimentation à canon à électron SPECS
        Args :
            - Identifiant de la voie de mesure ("A1", "A2", "B1" ou "B2")
        Returns : Pression en QString car plus facile a manipuler
    */

public slots:

    /*
        Brief : Permet d'obtenir le courant electrique
        Returns : Courant en QString car plus facile a manipuler
    */
    QVector<QString> obtenirCourantKeithley6485();


signals:
    // On emet le signal quand une mesure a ete effectuee
    void mesureLue(QVector<QString> qvValeurMesure);

private:
   /* PAS ENCORE IMPLEMENTER POUR LA V0 -

    QString m_nomFichier = "";
    QDateTime m_debut; // Date et heure du debut de l'acquisition
    int m_cycleActuel = 0; // Donne le nombre de mesures effectuees
    */
    Communication *m_communication;

};

#endif // RELEVEMESURES_H
