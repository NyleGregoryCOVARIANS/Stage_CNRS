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
    void validate_button_clicked();

private slots:
    void connexion_button_clicked();

private:
    Ui::MainWindow *m_ui; //this
    FenetreConnexion *m_fenetreConnexion; // Correction du type
};

#endif // MAINWINDOW_H
