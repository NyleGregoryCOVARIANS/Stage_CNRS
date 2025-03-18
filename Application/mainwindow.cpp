#include "mainwindow.h"
#include "fenetreconnexion.h" // Inclure la bonne classe

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Ajoutez un objet Communication avant d'utiliser FenetreConnexion
    Communication *communication = new Communication();
    fenetreConnexion = new FenetreConnexion(this, communication); // Spécification explicite du constructeur
    fenetreConnexion->show();

}

MainWindow::~MainWindow()
{
    delete fenetreConnexion;
}
