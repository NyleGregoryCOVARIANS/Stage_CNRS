#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Fenetres/Connexion/fenetreconnexion.h"
#include "Classes/ReleverMesure/releverMesure.h"  // Ajoute l'inclusion de la nouvelle classe



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
    void validate_button_clicked();
    void transmissionResultatRecu(QString CurrentEnergie, QString CurrentCourantEmission,
                                  QString CurrentFocus, QString CurrentWehnelt,
                                  QString CurrentPosX, QString CurrentPosY,
                                  QString CurrentBalX, QString CurrentBalY);



private:
    Ui::MainWindow *m_ui; //this
    FenetreConnexion *m_fenetreConnexion; // Correction du type
    Communication *m_communication;
    ReleverMesure * m_releverMesure;
};

#endif // MAINWINDOW_H
