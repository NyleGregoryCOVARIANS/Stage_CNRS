#include "mainwindow.h"
#include "Fenetres/Connexion/fenetreconnexion.h" // Inclure la bonne classe
#include "ui_mainwindow.h"

// Constructeur
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this); // Charge l'interface graphique
    Communication *communication = new Communication(); // Crée une instance de communication
    m_fenetreConnexion = new FenetreConnexion(this, communication); // Crée une instance d'une fenêtre de connexion

    connect(m_ui->pushButtonConnexion, &QPushButton::clicked, this, &MainWindow::connexion_button_clicked); // Si le bouton connexion est cliqué, alors lance la fonction connexion_button_clicked() qui affiche la fenêtre de connexion

    this->show();
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
