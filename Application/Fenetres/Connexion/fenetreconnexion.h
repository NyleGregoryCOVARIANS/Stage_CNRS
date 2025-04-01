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
    FenetreConnexion(QWidget *parent = nullptr, Communication *communication = nullptr);
    ~FenetreConnexion();
    void ActualisationMesures();

signals:
    void transmissionResultatPret( QString &CurrentEnergie, QString &CurrentCourantEmission, QString &CurrentFocus, QString &CurrentWehnelt,
        QString &CurrentPosX, QString &CurrentPosY, QString &CurrentBalX, QString &CurrentBalY);

private slots:
    void on_pushButton_rs232_clicked();

private:
    Ui::FenetreConnexion *m_ui;

    QString m_com;
    QString m_baudRate;
    Communication *m_communication;
    QTimer *m_timer;

};

#endif // FENETRECONNEXION_H
