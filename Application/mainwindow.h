#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fenetreconnexion.h" // Ajout de l'inclusion correcte

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    FenetreConnexion *fenetreConnexion; // Correction du type
};

#endif // MAINWINDOW_H
