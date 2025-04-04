#include "mainwindow.h"
#include "Fenetres/Connexion/fenetreconnexion.h" // Inclure la bonne classe
#include "ui_mainwindow.h"
#include <string>
#include <QDebug>
#include "Classes/ReleverMesure/relevermesure.h"  // Ajoute l'inclusion de la nouvelle classe


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_communication = new Communication();
    m_fenetreConnexion = new FenetreConnexion(this, m_communication);
    m_releverMesure = new ReleverMesure(m_communication, this);

    connect(m_fenetreConnexion, &FenetreConnexion::connexionEtablie,
            m_releverMesure, &ReleverMesure::actualisationMesures); // Lance une mesure après connexion

    connect(m_releverMesure, &ReleverMesure::transmissionResultatPret,
            this, &MainWindow::transmissionResultatRecu);
    connect(m_ui->pushButtonConnexion, &QPushButton::clicked,
            this, &MainWindow::connexion_button_clicked);
    connect(m_ui->ValidatePushButton, &QPushButton::clicked,
            this, &MainWindow::validate_button_clicked);

    this->show();
}




// Règle les problèmes de conversion du manuel et affiche sur l'application les paramètres récupérés.
void MainWindow::transmissionResultatRecu(QString CurrentEnergie, QString CurrentCourantEmission, QString CurrentFocus, QString CurrentWehnelt,
                                          QString CurrentPosX, QString CurrentPosY, QString CurrentBalX, QString CurrentBalY) {

    m_ui->valeurMesurerEnergie->setText(CurrentEnergie + "eV");

    float CurrentCourantEmissionInt = CurrentCourantEmission.toFloat() / 100 ; // x100 pour mettre en % et x100 pour corriger l'erreur d'échelle du manuel
    QString CurrentCourantEmissionIntStr = QString::number(CurrentCourantEmissionInt);
    m_ui->valeurMesurerCourantEmission->setText(CurrentCourantEmissionIntStr + " µA");

    m_ui->valeurMesurerFocus->setText(CurrentFocus + " V");

    // Conversion pour calcul du pourcentage
    float CurrentFocusInt = CurrentFocus.toFloat();
    float CurrentEnergieInt = CurrentEnergie.toFloat();
    float pourcentageInt =  CurrentFocusInt / CurrentEnergieInt * 100 ; // x100 pour mettre en % et x100 pour corriger l'erreur d'échelle du manuel
    QString pourcentageStr = QString::number(pourcentageInt);
    m_ui->valeurMesurerFocusEv->setText(pourcentageStr + " %");


    float CurrentWehneltInt =  CurrentWehnelt.toFloat() / 10 ;
    QString CurrentWehneltStr = QString::number(CurrentWehneltInt);
    m_ui->valeurMesurerWehnelt->setText(CurrentWehneltStr + " V");




    float CurrentPosXInt =  CurrentPosX.toFloat() / 1000 ;
    QString CurrentPosXStr = QString::number(CurrentPosXInt);
    m_ui->valeurMesurerPositionX->setText(CurrentPosXStr + " mm");


    float CurrentPosYInt =  CurrentPosY.toFloat() / 1000 ;
    QString CurrentPosYStr = QString::number(CurrentPosYInt);
    m_ui->valeurMesurerPositionY->setText(CurrentPosYStr+  " mm");



    float CurrentBalXInt =  CurrentBalX.toFloat() / 1000 ;
    QString CurrentBalXStr = QString::number(CurrentBalXInt);
    m_ui->valeurMesurerBalayageX->setText(CurrentBalXStr +  " mm");

    float CurrentBalYInt =  CurrentBalY.toFloat() / 1000 ;
    QString CurrentBalYStr = QString::number(CurrentBalYInt);
    m_ui->valeurMesurerBalayageY->setText(CurrentBalYStr +  " mm");
}






// Récupére les valeurs des editLine et modifie les paramètres de l'alimentation
void MainWindow::validate_button_clicked()
{
    QString y;
    // =========================
    // Modification de l'énergie de l'alimentation ( attention valeur entre 0 et 5000 | eV )
    // =========================
    QString Energie = m_ui->lineEditEnergie->text().trimmed();
    if(!Energie.isEmpty()){

        qDebug() << "-------------------------------------";
        m_communication->envoyer("EN " + Energie); // N'envoie pas la commande
        y = m_communication->recevoir();
        qDebug() << "Energie : " + Energie + " Réponse du changement d'énergie : " + y;


        qDebug() << "-------------------------------------";
    } else {
        qDebug() << "Aucune valeur renseignée pour l'énergie";
    }

    // =========================
    // Modification du courant d'émission
    // =========================
    QString CourantEmission = m_ui->lineEditCourantEmission->text().trimmed();
    if(!CourantEmission.isEmpty()){

        int CourantEmissionInt = CourantEmission.toInt()*100;
        QString CourantEmissionStr = QString::number(CourantEmissionInt);

        m_communication->envoyer("EC " + CourantEmissionStr);
        qDebug() << "Courant d'émission : " + CourantEmissionStr;
    } else {
        qDebug() << "Aucune valeur renseignée pour le courant d'émission";
    }

    // =========================
    // Modification du focus ( attention valeur entre 0 et 100 | % )
    // =========================
    QString Focus = m_ui->lineEditFocus->text().trimmed();
    if(!Focus.isEmpty()){

        int FocusInt = Focus.toInt()*100;
        QString FocusStr = QString::number(FocusInt);


        m_communication->envoyer("F1 " + FocusStr);
        qDebug() << "Focus : " + FocusStr;
    } else {
        qDebug() << "Aucune valeur renseignée pour le focus";
    }

    // =========================
    // Modification du Wehnelt ( attention valeur entre 0 et 2500 | 1/10 V )
    // =========================
    QString Wehnelt = m_ui->lineEditWehnelt->text().trimmed();
    if(!Wehnelt.isEmpty()){

        int WehneltInt = Wehnelt.toInt()*10;
        QString WehneltStr = QString::number(WehneltInt);

        m_communication->envoyer("WE " + WehneltStr);
        y = m_communication->recevoir();
        qDebug() << "Changement valeur Wehnelt " + y;


        qDebug() << "Wehnelt : " + WehneltStr;
    } else {
        qDebug() << "Aucune valeur renseignée pour le Wehnelt";
    }

    // =========================
    // Modification de la position X ( attention valeur entre -5000 et 5000 | mm )
    // =========================
    QString PositionX = m_ui->lineEditPositionX->text().trimmed();
    if(!PositionX.isEmpty()){


        int PositionXInt = PositionX.toInt()*100;
        QString PositionXStr = QString::number(PositionXInt);

        m_communication->envoyer("X0 " + PositionXStr);
        qDebug() << "Position X : " + PositionXStr;
    } else {
        qDebug() << "Aucune valeur renseignée pour la position X";
    }

    // =========================
    // Modification de la position Y ( attention valeur entre -5000 et 5000 | mm )
    // =========================
    QString PositionY = m_ui->lineEditPositionY->text().trimmed();
    if(!PositionY.isEmpty()){

        int PositionYInt = PositionY.toInt()*100;
        QString PositionYStr = QString::number(PositionYInt);


        m_communication->envoyer("Y0 " + PositionYStr);
        qDebug() << "Position Y : " + PositionYStr;
    } else {
        qDebug() << "Aucune valeur renseignée pour la position Y";
    }

    // =========================
    // Modification du balayage X ( attention valeur entre 1 et 200 | V / ° )
    // =========================
    QString BalayageX = m_ui->lineEditBalayageX->text().trimmed();
    if(!BalayageX.isEmpty()){

        int BalayageXInt = BalayageX.toInt()*10;
        QString BalayageXStr = QString::number(BalayageXInt);


        m_communication->envoyer("WX " + BalayageXStr);
        qDebug() << "Balayage X : " + BalayageXStr;
    } else {
        qDebug() << "Aucune valeur renseignée pour le balayage X";
    }

    // =========================
    // Modification du balayage Y ( attention valeur entre 1 et 200 | V / ° )
    // =========================
    QString BalayageY = m_ui->lineEditBalayageY->text().trimmed();
    if(!BalayageY.isEmpty()){

        int BalayageyInt = BalayageY.toInt()*10;
        QString BalayageyStr = QString::number(BalayageyInt);


        m_communication->envoyer("WY " + BalayageyStr);
        qDebug() << "Balayage Y : " + BalayageyStr;
    } else {
        qDebug() << "Aucune valeur renseignée pour le balayage Y";
    }

    // =========================
    // Indique que le bouton a été cliqué
    // =========================
    qDebug() << "BOUTON CLIQUE";
}




// Affiche la fenetre de connexion
void MainWindow::connexion_button_clicked(){
    m_fenetreConnexion->show();
}

// Destructeur
MainWindow::~MainWindow()
{
    delete m_fenetreConnexion;
}
