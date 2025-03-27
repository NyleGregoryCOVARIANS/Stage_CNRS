#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Fenetres/Connexion/fenetreconnexion.h"

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
    void transmissionResultat();


private:
    Ui::MainWindow *m_ui; //this
    FenetreConnexion *m_fenetreConnexion; // Correction du type
};

#endif // MAINWINDOW_H
