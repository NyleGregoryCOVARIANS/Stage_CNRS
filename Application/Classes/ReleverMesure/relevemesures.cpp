#include "relevemesures.h"

ReleveMesures::ReleveMesures(Communication *communication)
{
    m_communication = communication;
}

ReleveMesures::~ReleveMesures()
{
    delete m_communication;
}

// Accesseurs
int ReleveMesures::obtenirCycleActuel() const
{
    return m_cycleActuel;
}

int ReleveMesures::obtenirTempsEcoule()
{
    int tempsEcoule = m_debut.secsTo(QDateTime::currentDateTime());
    return tempsEcoule;
}

// A l'initialisation
QString ReleveMesures::initialiserDebut()
{
    m_debut = QDateTime::currentDateTime();
    return m_debut.toString("yyyy-MM-dd_HH-mm-ss");
}

QString ReleveMesures::initialiserNomFichier(QString nomBoitier)
{
    m_nomFichier = "data/data_" + nomBoitier+ "_" + m_debut.toString("yyyy-MM-dd_HH-mm-ss") + ".txt";
    return m_nomFichier;
}

void ReleveMesures::creerFichier(QString nomFichier)
{
    // Creation du dossier data
    if(!QDir("data").exists())
    {
        QDir().mkdir("data");
    }

    QFile file = QFile(nomFichier);
    file.open(QIODevice::Append | QIODevice::Text);

    QTextStream out(&file);

    // Ecrire dans le fichier
    out << "Date et heure de depart : " << m_debut.toString( "dd/MM/yyyy - HH:mm:ss") << Qt::endl <<Qt::endl <<Qt::endl;
    out << "Date et heure actuelles" << "\x09" << "Temps ecoule" << "\x09" << "Canal A1" << "\x09" << "Canal A2" << "\x09" <<
        "Canal B1" << "\x09" << "Canal B2" << Qt::endl;

    file.close();
}

// A chaque nouvelle mesure
int ReleveMesures::incrementerCycleActuel()
{
    m_cycleActuel++;
    return m_cycleActuel;
}

void ReleveMesures::ajouterLigneFichier(QVector<QString> qvNouvelleMesure, QString dateActuelle)
{
    QFile file = QFile(m_nomFichier);
    file.open(QIODevice::Append | QIODevice::Text);

    // Temps relatif
    int tempsEcoule = m_debut.secsTo(QDateTime::currentDateTime());

    QTextStream out(&file);

    // Ecrire dans le fichier
    out << dateActuelle << "\x09" << tempsEcoule << "\x09" << qvNouvelleMesure[0] << "\x09" << qvNouvelleMesure[1] << "\x09" << qvNouvelleMesure[2]
        << "\x09" << qvNouvelleMesure[3] << Qt::endl;
    file.close();
}

QString ReleveMesures::obtenirPressionTPG300(QString identifiant)
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

QString ReleveMesures::obtenirPressionMKS937B(QString identifiant)
{
    QString pression = "";

    // envoi de VAL
    QString adresse = "253"; // Adresse du boitier toujours a 253
    m_communication->envoyer("@" + adresse + identifiant + "?;FF");

    // reception de la valeur
    pression = m_communication->recevoir();

    // on retire ;FF à la fin
    pression = pression.replace(";FF", ""); // on supprime les caracteres de fin

    // on vire le nom de la commande
    QString debut_reception = pression.left(7);
    pression = pression.replace(debut_reception, ""); // @<aaa>ACK == 7 caracteres
    pression = pression.left(8);

    return pression;
}

// Public slots
QVector<QString> ReleveMesures::mesurerTPG300()
{
    QVector<QString> qvPressionsTPG300(4);

    qvPressionsTPG300[0] = obtenirPressionTPG300("A1");
    qvPressionsTPG300[1] = obtenirPressionTPG300("A2");
    qvPressionsTPG300[2] = obtenirPressionTPG300("B1");
    qvPressionsTPG300[3] = obtenirPressionTPG300("B2");

    emit mesureLue(qvPressionsTPG300);

    return qvPressionsTPG300;
}

QVector<QString> ReleveMesures::mesurerMKS937B()
{
    QVector<QString> qvPressionsMKS937B(4);

    qvPressionsMKS937B[0] = obtenirPressionMKS937B("PR1");
    qvPressionsMKS937B[1] = obtenirPressionMKS937B("PR2");
    qvPressionsMKS937B[2] = obtenirPressionMKS937B("PR3");
    qvPressionsMKS937B[3] = obtenirPressionMKS937B("PR4");

    emit mesureLue(qvPressionsMKS937B);

    return qvPressionsMKS937B;
}

QVector<QString> ReleveMesures::obtenirCourantKeithley6485()
{
    QVector<QString> qvCourant(4);
    qvCourant[0] = "";
    qvCourant[1] = "";
    qvCourant[2] = "";
    qvCourant[3] = "";

    //On fait un reset de l'instrument aux paramètres par défaut
    m_communication->envoyer("*RST");

    //On active la correction du zero
    m_communication->envoyer("SYST:ZCH ON");

    //On effectue la mesure
    m_communication->envoyer("READ?");

    //On reçoit la valeur
    qvCourant[0] = m_communication->recevoirKeithley6485();

    //Permet de virer l'unité "A" et les 2 autres valeurs données après le courant
    QChar targetChar = 'A';
    int index = qvCourant[0].indexOf(targetChar);
    if (index != -1) {
        qvCourant[0].truncate(index);}

    emit mesureLue(qvCourant);

    return qvCourant;
}

QVector<QString> ReleveMesures::obtenirPressionLeyboldIM540()
{
    QVector<QString> qvPressionsLeyboldIM540(4);
    qvPressionsLeyboldIM540[0] = "";
    qvPressionsLeyboldIM540[1] = "";
    qvPressionsLeyboldIM540[2] = "";
    qvPressionsLeyboldIM540[3] = "";

    m_communication->envoyer("PRS,1");

    QString reponseLeyboldIM540 = m_communication->recevoir();

    // Reception de "\x06" (=ACK=Acknowledge : reconnait)
    reponseLeyboldIM540 = m_communication->recevoir();


    // Verification de la bonne reception s'il y a "\x06" -> Ne fonctionne pas pour LeyboldIM540...
    /*
    if(reponseLeyboldIM540.contains("\x06") == false)
    {
        return qvPressionsLeyboldIM540;
    }
    */

    // Envoi de "\x05" (=ENQ=Enquiry : requete)
    m_communication->envoyer("\x05");

    qvPressionsLeyboldIM540[0] = m_communication->recevoir();

    qvPressionsLeyboldIM540[0] = qvPressionsLeyboldIM540[0].remove(QChar('\x0D')); // suppression de <CR>
    qvPressionsLeyboldIM540[0] = qvPressionsLeyboldIM540[0].remove(QChar('\x0A')); // suppression de <LF>
    qvPressionsLeyboldIM540[0] = qvPressionsLeyboldIM540[0].remove("A1,");

    emit mesureLue(qvPressionsLeyboldIM540);

    return qvPressionsLeyboldIM540;
}


