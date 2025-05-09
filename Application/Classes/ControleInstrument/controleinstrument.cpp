#include "controleinstrument.h"
#include <QDebug>
#include <QElapsedTimer>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMessageBox>

ControleInstrument::ControleInstrument(Communication* communicationSPECS,
                                       Communication* communicationPICO,
                                       QObject *parent)
    : QObject(parent),
    m_communicationSPECS(communicationSPECS),
    m_communicationPICO(communicationPICO)
{
}


void ControleInstrument::attenteAsynchrone(int millisecondes)
{
    if (QThread::currentThread() != qApp->thread()) {
        // Si on est dans un thread secondaire
        QThread::msleep(millisecondes);
    } else {
        // Si on est dans le thread principal (GUI)
        QEventLoop loop;
        QTimer::singleShot(millisecondes, &loop, SLOT(quit()));
        loop.exec();
    }
}



void ControleInstrument::validate_button_clickedSPECS(const QString& energie,
                                            const QString& courantEmission,
                                            const QString& focus,
                                            const QString& wehnelt,
                                            const QString& posX,
                                            const QString& posY,
                                            const QString& balayageX,
                                            const QString& balayageY)
{
    QString valTemp;

    if (!energie.isEmpty()) {
        m_communicationSPECS->envoyer("EN " + energie);
        valTemp = m_communicationSPECS->recevoir();
        qDebug() << "Energie : " + energie + " | Réponse : " + valTemp;
    }

    if (!courantEmission.isEmpty()) {
        int courantInt = courantEmission.toInt() * 100;
        m_communicationSPECS->envoyer("EC " + QString::number(courantInt));
        qDebug() << "Courant d'émission : " << courantInt;
    }

    if (!focus.isEmpty()) {
        int focusInt = focus.toInt() * 100;
        m_communicationSPECS->envoyer("F1 " + QString::number(focusInt));
        qDebug() << "Focus : " << focusInt;
    }

    if (!wehnelt.isEmpty()) {
        int wehneltInt = wehnelt.toInt() * 10;
        m_communicationSPECS->envoyer("WE " + QString::number(wehneltInt));
        valTemp = m_communicationSPECS->recevoir();
        qDebug() << "Wehnelt : " << wehneltInt << " | Réponse : " << valTemp;
    }

    if (!posX.isEmpty()) {
        int posXInt = posX.toInt() * 100;
        m_communicationSPECS->envoyer("X0 " + QString::number(posXInt));
        qDebug() << "Position X : " << posXInt;
    }

    if (!posY.isEmpty()) {
        int posYInt = posY.toInt() * 100;
        m_communicationSPECS->envoyer("Y0 " + QString::number(posYInt));
        qDebug() << "Position Y : " << posYInt;
    }

    if (!balayageX.isEmpty()) {
        int balayageXInt = balayageX.toInt() * 10;
        m_communicationSPECS->envoyer("WX " + QString::number(balayageXInt));
        qDebug() << "Balayage X : " << balayageXInt;
    }

    if (!balayageY.isEmpty()) {
        int balayageYInt = balayageY.toInt() * 10;
        m_communicationSPECS->envoyer("WY " + QString::number(balayageYInt));
        qDebug() << "Balayage Y : " << balayageYInt;
    }

    qDebug() << "Alimentation SPECS mise à jour";
}


void ControleInstrument::changerPolarisation() {
    if(polarisation == "+50V"){
        polarisation = "-50V";
    }
    else{
        polarisation = "+50V";
    }
}




void ControleInstrument::validate_button_clickedPICO(
    const QString& EnergieMin,
    const QString& EnergieMax,
    const QString& Pas,
    const QString& Duree)
{
    QMap<double, QVector<double>> mesuresParEnergie;

    if (polarisation == "+50V") {
        // Afficher un message pour avertir l’utilisateur avant le 1er balayage
        QMessageBox::information(nullptr, "Polarisation requise",
                                 QString("Merci de bien vouloir polariser à %1 avant de commencer.").arg(polarisation));
    }

    if (EnergieMin.isEmpty() || EnergieMax.isEmpty() || Pas.isEmpty() || Duree.isEmpty()) {
        qDebug() << "Tous les champs doivent être remplis.";
        return;
    }

    if (!m_communicationPICO) {
        qDebug() << "❌ m_communicationPICO est null !";
        return;
    }

    double eMin = EnergieMin.toDouble();
    double eMax = EnergieMax.toDouble();
    double pas = Pas.toDouble();
    int duree = Duree.toInt();

    // Structures pour stocker les données des deux tableaux
    QStringList tableau1Lignes; // Pour le tableau des mesures brutes
    QMap<double, QMap<QString, double>> moyennes; // Pour le tableau des moyennes

    // Premier balayage
    for (double energie = eMin; energie <= eMax; energie += pas) {
        m_communicationSPECS->envoyer("EN " + QString::number(energie));
        qDebug() << "Energie appliquée :" << energie;

        attenteAsynchrone(5000);

        QElapsedTimer timer;
        timer.start();

        while (timer.elapsed() < duree * 1000) {
            m_communicationPICO->envoyer("READ?");
            QString intensite = m_communicationPICO->recevoirKeithley6485();

            bool ok;
            double intensiteNum = intensite.trimmed().toDouble(&ok);
            if (ok) {
                mesuresParEnergie[energie].append(intensiteNum);
            }

            QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
            double tempsEcoule = timer.elapsed() / 1000.0;

            // Ajouter la ligne au tableau 1
            QString ligne = QString("%1;%2;%3;%4;%5")
                                .arg(timestamp)
                                .arg(QString::number(tempsEcoule, 'f', 2))
                                .arg(QString::number(energie, 'f', 2))
                                .arg(polarisation)
                                .arg(intensite.trimmed());
            tableau1Lignes.append(ligne);

            qDebug() << "⏱ Mesure :" << timestamp << " | " << tempsEcoule << "s | "
                     << energie << "eV | " << polarisation << " | " << intensite;
        }

        // Calculer la moyenne pour cette énergie
        const QVector<double>& valeurs = mesuresParEnergie[energie];
        double somme = std::accumulate(valeurs.begin(), valeurs.end(), 0.0);
        double moyenne = valeurs.isEmpty() ? 0.0 : somme / valeurs.size();
        moyennes[energie][polarisation] = moyenne;
    }

    // Écriture dans le fichier pour le premier balayage
    QFile fichier("C:/Users/Mesure/Documents/Nyle/mesures_pico.csv");
    if (!fichier.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "❌ Impossible d'ouvrir le fichier.";
        return;
    }

    QTextStream out(&fichier);
    QStringList lignesExistantes = out.readAll().split('\n');
    fichier.seek(0); // Retour au début pour écrire

    // Si le fichier est vide, écrire les en-têtes
    if (fichier.size() == 0) {
        out << "Date et heure;Temps ecoule (s);Energie (eV);Polarisation;Intensite brute;;" // Tableau 1
            << "Energie (eV);Intensite moyenne (+50V);Intensite moyenne (-50V);SEY\n"; // Tableau 2 avec Energie (eV)
    }

    // Aller à la fin pour ajouter les nouvelles données
    fichier.seek(fichier.size());

    // Écrire les données du tableau 1 et du tableau 2 côte à côte pour le premier balayage
    int maxLignes = tableau1Lignes.size();
    QStringList tableau2Lignes;

    // Générer les lignes du tableau 2 pour le premier balayage
    for (auto it = moyennes.begin(); it != moyennes.end(); ++it) {
        double energie = it.key();
        double imPlus = it.value().value("+50V", std::numeric_limits<double>::quiet_NaN());
        double imMoins = it.value().value("-50V", std::numeric_limits<double>::quiet_NaN());
        QString sey;

        if (!std::isnan(imPlus) && !std::isnan(imMoins) && imPlus != 0) {
            double seyVal = 1 - (imMoins / imPlus);
            sey = QString::number(seyVal, 'f', 6);
        }

        // Générer la ligne avec Energie (eV) inclus
        QString ligne = QString("%1;%2;%3;%4")
                            .arg(QString::number(energie, 'f', 2))
                            .arg(std::isnan(imPlus) ? "" : QString::number(imPlus, 'e', 10))
                            .arg(std::isnan(imMoins) ? "" : QString::number(imMoins, 'e', 10))
                            .arg(sey);
        tableau2Lignes.append(ligne);
    }

    // Écrire les lignes des deux tableaux côte à côte pour le premier balayage
    for (int i = 0; i < maxLignes; ++i) {
        QString ligneTableau1 = tableau1Lignes.value(i, ";;;;");
        QString ligneTableau2 = (i < tableau2Lignes.size()) ? tableau2Lignes[i] : ";;;";
        out << ligneTableau1 << ";;" << ligneTableau2 << "\n";
    }

    // Ajouter les lignes restantes du tableau 2 si nécessaire
    for (int i = maxLignes; i < tableau2Lignes.size(); ++i) {
        out << ";;;;;;" << tableau2Lignes[i] << "\n";
    }

    fichier.flush();

    // Afficher un message avant le 2ème balayage si nécessaire
    if (polarisation == "+50V") {
        QMessageBox::information(nullptr, "Polarisation requise",
                                 QString("Merci de bien vouloir polariser à -50V avant de commencer."));
    }

    // Changer la polarisation et effectuer le second balayage
    changerPolarisation();
    mesuresParEnergie.clear();
    tableau1Lignes.clear();
    tableau2Lignes.clear();

    // Second balayage
    for (double energie = eMin; energie <= eMax; energie += pas) {
        m_communicationSPECS->envoyer("EN " + QString::number(energie));
        qDebug() << "Energie appliquée :" << energie;

        attenteAsynchrone(5000);

        QElapsedTimer timer;
        timer.start();

        while (timer.elapsed() < duree * 1000) {
            m_communicationPICO->envoyer("READ?");
            QString intensite = m_communicationPICO->recevoirKeithley6485();

            bool ok;
            double intensiteNum = intensite.trimmed().toDouble(&ok);
            if (ok) {
                mesuresParEnergie[energie].append(intensiteNum);
            }

            QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
            double tempsEcoule = timer.elapsed() / 1000.0;

            // Ajouter la ligne au tableau 1
            QString ligne = QString("%1;%2;%3;%4;%5")
                                .arg(timestamp)
                                .arg(QString::number(tempsEcoule, 'f', 2))
                                .arg(QString::number(energie, 'f', 2))
                                .arg(polarisation)
                                .arg(intensite.trimmed());
            tableau1Lignes.append(ligne);

            qDebug() << "⏱ Mesure :" << timestamp << " | " << tempsEcoule << "s | "
                     << energie << "eV | " << polarisation << " | " << intensite;
        }

        // Calculer la moyenne pour cette énergie
        const QVector<double>& valeurs = mesuresParEnergie[energie];
        double somme = std::accumulate(valeurs.begin(), valeurs.end(), 0.0);
        double moyenne = valeurs.isEmpty() ? 0.0 : somme / valeurs.size();
        moyennes[energie][polarisation] = moyenne;
    }

    // Écrire les données du second balayage
    fichier.seek(fichier.size());
    maxLignes = tableau1Lignes.size();

    // Générer les lignes du tableau 2 pour le second balayage
    tableau2Lignes.clear();
    for (auto it = moyennes.begin(); it != moyennes.end(); ++it) {
        double energie = it.key();
        double imPlus = it.value().value("+50V", std::numeric_limits<double>::quiet_NaN());
        double imMoins = it.value().value("-50V", std::numeric_limits<double>::quiet_NaN());
        QString sey;

        if (!std::isnan(imPlus) && !std::isnan(imMoins) && imPlus != 0) {
            double seyVal = 1 - (imMoins / imPlus);
            sey = QString::number(seyVal, 'f', 6);
        }

        // Générer la ligne avec Energie (eV) inclus
        QString ligne = QString("%1;%2;%3;%4")
                            .arg(QString::number(energie, 'f', 2))
                            .arg(std::isnan(imPlus) ? "" : QString::number(imPlus, 'e', 10))
                            .arg(std::isnan(imMoins) ? "" : QString::number(imMoins, 'e', 10))
                            .arg(sey);
        tableau2Lignes.append(ligne);
    }

    // Écrire les lignes des deux tableaux côte à côte pour le second balayage
    for (int i = 0; i < maxLignes; ++i) {
        QString ligneTableau1 = tableau1Lignes.value(i, ";;;;");
        QString ligneTableau2 = (i < tableau2Lignes.size()) ? tableau2Lignes[i] : ";;;";
        out << ligneTableau1 << ";;" << ligneTableau2 << "\n";
    }

    // Ajouter les lignes restantes du tableau 2 si nécessaire
    for (int i = maxLignes; i < tableau2Lignes.size(); ++i) {
        out << ";;;;;;" << tableau2Lignes[i] << "\n";
    }

    // Ajouter 3 lignes vides après le 2ème balayage
    for (int i = 0; i < 3; ++i) {
        out << "\n";
    }

    fichier.close();

    changerPolarisation();

    qDebug() << "✅ Fichier mis à jour avec tableaux côte à côte et espacement.";
}



// Active le mode Operate quand la case est cochée.
void ControleInstrument::on_checkBoxOperate_toggled(bool checked)
{
    if (checked) {
        qDebug() << "Activation du mode OPERATE";
        m_communicationSPECS->envoyer("OP 1");
    } else {
        m_communicationSPECS->envoyer("SB 1");
        qDebug() << "Désactivation du mode OPERATE";
    }
}

// Active le mode Haute Tension quand la case est cochée.
void ControleInstrument::on_checkBoxHV_toggled(bool checked)
{

        if (checked) {
            m_communicationSPECS->envoyer("HE 2");
            qDebug() << "Activation du mode Haute Tension";
        } else {
            m_communicationSPECS->envoyer("HA 2");
            qDebug() << "Désactivation du mode Haute Tension";
        }

}


void ControleInstrument::initialisationPICO(Communication *communicationPICO)
{

    if (this != nullptr) {
        qDebug() << "this = " << this;
    }

    qDebug() << "communicationPICO = " << communicationPICO;

    if (!communicationPICO) {
        qDebug() << "❌ ERREUR : communicationPICO est nullptr";
    }
    qDebug() << "Port : " << communicationPICO->obtenirPort();

    m_communicationPICO = communicationPICO;

    qDebug() << "--------------OPERATION PICO-----------------";
    m_communicationPICO->envoyer("*RST");
    m_communicationPICO->envoyer("SYST:ZCH ON");
    m_communicationPICO->envoyer("CURR:RANG:AUTO ON");
    m_communicationPICO->envoyer("INIT");
    m_communicationPICO->envoyer("SYST:ZCOR:ACQ");
    m_communicationPICO->envoyer("SYST:ZCOR ON");
    m_communicationPICO->envoyer("CURR:RANG:AUTO ON");
    m_communicationPICO->envoyer("SYST:ZCH OFF");


    m_communicationPICO->envoyer("CURR:NPLC 0.01");

}


void ControleInstrument::initialisationSPECS(Communication *m_communicationSPECS){
    qDebug() << "Activation du mode REMOTE";
    m_communicationSPECS->envoyer("RE");
}

