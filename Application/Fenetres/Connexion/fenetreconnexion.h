#ifndef FENETRECONNEXION_H
#define FENETRECONNEXION_H

#include "Classes/Communication/communication.h"
#include <QDialog>


namespace Ui {
class FenetreConnexion;
}

class FenetreConnexion : public QDialog
{
    Q_OBJECT



public:
    // Le constructeur est surcharge pour pouvoir créer un objet de la classe FenetreConnexion de 2 manieres
    FenetreConnexion(QWidget *parent = nullptr); // Constructeur par defaut au cas ou
    explicit FenetreConnexion(QWidget *parent, Communication *comSPECS, Communication *comPICO);
    ~FenetreConnexion();

private slots:
    void on_pushButton_rs232_clicked();


signals:
    void connexionEtablie(); //  Signal émis après une connexion réussie

private:
    Ui::FenetreConnexion *m_ui;

    Communication *m_communication_SPECS;
    Communication *m_communication_PICO;

public:
    bool estConnecteSPECS, estConnectePICO;
    QString m_com_SPECS, m_com_PICO;
    QString m_baudRate_SPECS, m_baudRate_PICO;

};

#endif // FENETRECONNEXION_H
