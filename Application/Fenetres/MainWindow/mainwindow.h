#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Fenetres/Connexion/fenetreconnexion.h"
#include "Classes/ReleverMesure/releverMesure.h"  // Ajoute l'inclusion de la nouvelle classe
#include "Classes/ControleInstrument/controleinstrument.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void connexion_button_clicked();

    void affichageResultatRecuSPECS(QString CurrentEnergie, QString CurrentCourantEmission,
                                  QString CurrentFocus, QString CurrentWehnelt,
                                  QString CurrentPosX, QString CurrentPosY,
                                  QString CurrentBalX, QString CurrentBalY);



private:
    Ui::MainWindow *m_ui; //this
    FenetreConnexion *m_fenetreConnexion; // Correction du type
    Communication *m_communication_SPECS;
    Communication *m_communication_PICO;
    ReleverMesure * m_releverMesure;
    QString Energie, CourantEmission, Focus, Wehnelt, PositionX, PositionY, BalayageX, BalayageY; // Variables de l'onglet SPECS
    QString EnergieMin, EnergieMax, Pas, Duree; // Variables de l'onglet pico configuration

    ControleInstrument *m_controleInstrument;
};

#endif // MAINWINDOW_H
