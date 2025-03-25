#include "relevemesures.h"

ReleveMesures::ReleveMesures(Communication *communication)
{
    m_communication = communication;
}

ReleveMesures::~ReleveMesures()
{
    delete m_communication;
}



QString ReleveMesures::obtenirEnergie(QString identifiant)
{
    QString pression = "";

    // Envoi de TID : premiere etape necessaire
    m_communication->envoyer("P" + identifiant);

    // Reception de "\x06" (=ACK=Acknowledge : reconnait)
    QString reponseTPG300 = m_communication->recevoir();

    // Verification de la bonne reception s'il y a "\x06"
    if(reponseTPG300.contains("\x06") == false)
    {
        return pression;
    }

    // Envoi de "\x05" (=ENQ=Enquiry : requete)
    m_communication->envoyer("\x05");

    // Reception de la valeur de pression
    pression = m_communication->recevoir();

    // On retire les caracteres en plus de la pression
    pression = pression.replace("\x0D", ""); //retour chariot
    pression = pression.replace("\x0A", ""); // line feed = saut de ligne

    // On cherche les etats
    QString status;
    status = pression[0];

    pression = pression.mid(2); // On lit la pression sans les caracteres autour

    QString reponse;

    if(status == "0") // Measurement data okay
        reponse = pression;
    else if(status == "1")
        reponse = "Underrange";
    else if(status == "2")
        reponse = "Overrange";
    else if(status == "3")
        reponse = "Measuring circuit error";
    else if(status == "4")
        reponse = "Measuring circuit switched off";
    else if(status == "5")
        reponse = "No hardware";

    return reponse;
}

