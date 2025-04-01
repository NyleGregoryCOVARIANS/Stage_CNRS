/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame2;
    QGridLayout *gridLayout;
    QFrame *frameBalayageY;
    QGridLayout *_2;
    QLineEdit *lineEditBalayageY;
    QLabel *label_9;
    QLabel *valeurMesurer_8;
    QLabel *valeurMesurerBalayageY;
    QFrame *framePositionY;
    QGridLayout *_3;
    QLineEdit *lineEditPositionY;
    QLabel *labelPositionY;
    QLabel *valeurMesurer_6;
    QLabel *valeurMesurerPositionY;
    QFrame *frameBalayageX;
    QGridLayout *_4;
    QLineEdit *lineEditBalayageX;
    QLabel *labelBalayageX;
    QLabel *valeurMesurer_7;
    QLabel *valeurMesurerBalayageX;
    QFrame *framePositionX;
    QGridLayout *_5;
    QLabel *labelPositionX;
    QLineEdit *lineEditPositionX;
    QLabel *valeurMesurer_5;
    QLabel *valeurMesurerPositionX;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *Header;
    QLabel *label_1;
    QPushButton *pushButtonConnexion;
    QFrame *frame1;
    QVBoxLayout *verticalLayout_2;
    QFrame *frameEnergie;
    QGridLayout *_10;
    QLabel *labelEnergie;
    QLineEdit *lineEditEnergie;
    QLabel *valeurMesurer;
    QLabel *valeurMesurerEnergie;
    QFrame *frameCourantEmission;
    QGridLayout *_8;
    QLineEdit *lineEditCourantEmission;
    QLabel *labelCourantEmission;
    QLabel *valeurMesurerCourantEmission;
    QLabel *valeurMesurer_3;
    QFrame *frameFocus;
    QGridLayout *_9;
    QLineEdit *lineEditFocus;
    QLabel *valeurMesurer_2;
    QLabel *valeurMesurerFocus;
    QLabel *labelFocus;
    QLabel *valeurMesurer_9;
    QLabel *valeurMesurerFocusEv;
    QFrame *frameWehnelt;
    QGridLayout *_7;
    QLabel *labelWehnelt;
    QLineEdit *lineEditWehnelt;
    QLabel *valeurMesurer_4;
    QLabel *valeurMesurerWehnelt;
    QPushButton *ValidatePushButton;
    QMenuBar *menubar;
    QToolBar *toolBar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(850, 830);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame2 = new QFrame(centralwidget);
        frame2->setObjectName("frame2");
        frame2->setGeometry(QRect(10, 490, 821, 241));
        frame2->setMinimumSize(QSize(16, 196));
        QPalette palette;
        frame2->setPalette(palette);
        frame2->setAutoFillBackground(false);
        frame2->setFrameShape(QFrame::Shape::WinPanel);
        frame2->setFrameShadow(QFrame::Shadow::Plain);
        frame2->setLineWidth(1);
        frame2->setMidLineWidth(0);
        gridLayout = new QGridLayout(frame2);
        gridLayout->setSpacing(3);
        gridLayout->setContentsMargins(3, 3, 3, 3);
        gridLayout->setObjectName("gridLayout");
        frameBalayageY = new QFrame(frame2);
        frameBalayageY->setObjectName("frameBalayageY");
        QPalette palette1;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(240, 236, 227, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        frameBalayageY->setPalette(palette1);
        frameBalayageY->setAutoFillBackground(true);
        frameBalayageY->setFrameShape(QFrame::Shape::WinPanel);
        frameBalayageY->setFrameShadow(QFrame::Shadow::Plain);
        frameBalayageY->setLineWidth(1);
        _2 = new QGridLayout(frameBalayageY);
        _2->setSpacing(6);
        _2->setObjectName("_2");
        lineEditBalayageY = new QLineEdit(frameBalayageY);
        lineEditBalayageY->setObjectName("lineEditBalayageY");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setStrikeOut(false);
        font.setKerning(false);
        lineEditBalayageY->setFont(font);

        _2->addWidget(lineEditBalayageY, 1, 0, 1, 1);

        label_9 = new QLabel(frameBalayageY);
        label_9->setObjectName("label_9");
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setStrikeOut(false);
        font1.setKerning(false);
        label_9->setFont(font1);
        label_9->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _2->addWidget(label_9, 0, 0, 1, 1);

        valeurMesurer_8 = new QLabel(frameBalayageY);
        valeurMesurer_8->setObjectName("valeurMesurer_8");
        valeurMesurer_8->setFont(font1);
        valeurMesurer_8->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _2->addWidget(valeurMesurer_8, 0, 1, 1, 1);

        valeurMesurerBalayageY = new QLabel(frameBalayageY);
        valeurMesurerBalayageY->setObjectName("valeurMesurerBalayageY");
        valeurMesurerBalayageY->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";"));

        _2->addWidget(valeurMesurerBalayageY, 1, 1, 1, 1);


        gridLayout->addWidget(frameBalayageY, 1, 1, 1, 1);

        framePositionY = new QFrame(frame2);
        framePositionY->setObjectName("framePositionY");
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        framePositionY->setPalette(palette2);
        framePositionY->setAutoFillBackground(true);
        framePositionY->setFrameShape(QFrame::Shape::WinPanel);
        framePositionY->setFrameShadow(QFrame::Shadow::Plain);
        framePositionY->setLineWidth(1);
        _3 = new QGridLayout(framePositionY);
        _3->setSpacing(6);
        _3->setObjectName("_3");
        lineEditPositionY = new QLineEdit(framePositionY);
        lineEditPositionY->setObjectName("lineEditPositionY");
        lineEditPositionY->setFont(font);

        _3->addWidget(lineEditPositionY, 1, 0, 1, 1);

        labelPositionY = new QLabel(framePositionY);
        labelPositionY->setObjectName("labelPositionY");
        labelPositionY->setFont(font1);
        labelPositionY->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _3->addWidget(labelPositionY, 0, 0, 1, 1);

        valeurMesurer_6 = new QLabel(framePositionY);
        valeurMesurer_6->setObjectName("valeurMesurer_6");
        valeurMesurer_6->setFont(font1);
        valeurMesurer_6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _3->addWidget(valeurMesurer_6, 0, 1, 1, 1);

        valeurMesurerPositionY = new QLabel(framePositionY);
        valeurMesurerPositionY->setObjectName("valeurMesurerPositionY");
        valeurMesurerPositionY->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";"));

        _3->addWidget(valeurMesurerPositionY, 1, 1, 1, 1);


        gridLayout->addWidget(framePositionY, 0, 1, 1, 1);

        frameBalayageX = new QFrame(frame2);
        frameBalayageX->setObjectName("frameBalayageX");
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        frameBalayageX->setPalette(palette3);
        frameBalayageX->setAutoFillBackground(true);
        frameBalayageX->setFrameShape(QFrame::Shape::WinPanel);
        frameBalayageX->setFrameShadow(QFrame::Shadow::Plain);
        frameBalayageX->setLineWidth(1);
        _4 = new QGridLayout(frameBalayageX);
        _4->setSpacing(6);
        _4->setObjectName("_4");
        lineEditBalayageX = new QLineEdit(frameBalayageX);
        lineEditBalayageX->setObjectName("lineEditBalayageX");
        lineEditBalayageX->setFont(font);

        _4->addWidget(lineEditBalayageX, 1, 0, 1, 1);

        labelBalayageX = new QLabel(frameBalayageX);
        labelBalayageX->setObjectName("labelBalayageX");
        labelBalayageX->setFont(font1);
        labelBalayageX->setMouseTracking(false);
        labelBalayageX->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _4->addWidget(labelBalayageX, 0, 0, 1, 1);

        valeurMesurer_7 = new QLabel(frameBalayageX);
        valeurMesurer_7->setObjectName("valeurMesurer_7");
        valeurMesurer_7->setFont(font1);
        valeurMesurer_7->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _4->addWidget(valeurMesurer_7, 0, 1, 1, 1);

        valeurMesurerBalayageX = new QLabel(frameBalayageX);
        valeurMesurerBalayageX->setObjectName("valeurMesurerBalayageX");
        valeurMesurerBalayageX->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";"));

        _4->addWidget(valeurMesurerBalayageX, 1, 1, 1, 1);


        gridLayout->addWidget(frameBalayageX, 1, 0, 1, 1);

        framePositionX = new QFrame(frame2);
        framePositionX->setObjectName("framePositionX");
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        framePositionX->setPalette(palette4);
        framePositionX->setAutoFillBackground(true);
        framePositionX->setFrameShape(QFrame::Shape::WinPanel);
        framePositionX->setFrameShadow(QFrame::Shadow::Plain);
        framePositionX->setLineWidth(1);
        _5 = new QGridLayout(framePositionX);
        _5->setSpacing(6);
        _5->setObjectName("_5");
        labelPositionX = new QLabel(framePositionX);
        labelPositionX->setObjectName("labelPositionX");
        labelPositionX->setFont(font1);
        labelPositionX->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _5->addWidget(labelPositionX, 0, 0, 1, 1);

        lineEditPositionX = new QLineEdit(framePositionX);
        lineEditPositionX->setObjectName("lineEditPositionX");
        lineEditPositionX->setFont(font);

        _5->addWidget(lineEditPositionX, 1, 0, 1, 1);

        valeurMesurer_5 = new QLabel(framePositionX);
        valeurMesurer_5->setObjectName("valeurMesurer_5");
        valeurMesurer_5->setFont(font1);
        valeurMesurer_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _5->addWidget(valeurMesurer_5, 0, 1, 1, 1);

        valeurMesurerPositionX = new QLabel(framePositionX);
        valeurMesurerPositionX->setObjectName("valeurMesurerPositionX");
        valeurMesurerPositionX->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";"));

        _5->addWidget(valeurMesurerPositionX, 1, 1, 1, 1);


        gridLayout->addWidget(framePositionX, 0, 0, 1, 1);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 821, 87));
        Header = new QVBoxLayout(verticalLayoutWidget);
        Header->setObjectName("Header");
        Header->setContentsMargins(0, 0, 0, 0);
        label_1 = new QLabel(verticalLayoutWidget);
        label_1->setObjectName("label_1");
        label_1->setStyleSheet(QString::fromUtf8("color: rgb(170, 0, 0);\n"
"border-color: rgb(0, 0, 255);"));

        Header->addWidget(label_1);

        pushButtonConnexion = new QPushButton(verticalLayoutWidget);
        pushButtonConnexion->setObjectName("pushButtonConnexion");
        pushButtonConnexion->setStyleSheet(QString::fromUtf8("font: 15pt \"Segoe UI\";"));

        Header->addWidget(pushButtonConnexion);

        frame1 = new QFrame(centralwidget);
        frame1->setObjectName("frame1");
        frame1->setGeometry(QRect(80, 90, 691, 391));
        frame1->setMinimumSize(QSize(16, 196));
        QPalette palette5;
        frame1->setPalette(palette5);
        frame1->setAutoFillBackground(false);
        frame1->setStyleSheet(QString::fromUtf8("\n"
"border-color: rgb(0, 0, 255);"));
        frame1->setFrameShape(QFrame::Shape::WinPanel);
        frame1->setFrameShadow(QFrame::Shadow::Plain);
        frame1->setLineWidth(1);
        frame1->setMidLineWidth(0);
        verticalLayout_2 = new QVBoxLayout(frame1);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frameEnergie = new QFrame(frame1);
        frameEnergie->setObjectName("frameEnergie");
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Base, brush);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        frameEnergie->setPalette(palette6);
        frameEnergie->setAutoFillBackground(true);
        frameEnergie->setFrameShape(QFrame::Shape::WinPanel);
        frameEnergie->setFrameShadow(QFrame::Shadow::Plain);
        frameEnergie->setLineWidth(1);
        _10 = new QGridLayout(frameEnergie);
        _10->setSpacing(6);
        _10->setObjectName("_10");
        labelEnergie = new QLabel(frameEnergie);
        labelEnergie->setObjectName("labelEnergie");
        labelEnergie->setFont(font1);
        labelEnergie->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _10->addWidget(labelEnergie, 0, 0, 1, 1);

        lineEditEnergie = new QLineEdit(frameEnergie);
        lineEditEnergie->setObjectName("lineEditEnergie");
        lineEditEnergie->setFont(font);

        _10->addWidget(lineEditEnergie, 1, 0, 1, 1);

        valeurMesurer = new QLabel(frameEnergie);
        valeurMesurer->setObjectName("valeurMesurer");
        valeurMesurer->setFont(font1);
        valeurMesurer->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _10->addWidget(valeurMesurer, 0, 1, 1, 1);

        valeurMesurerEnergie = new QLabel(frameEnergie);
        valeurMesurerEnergie->setObjectName("valeurMesurerEnergie");
        valeurMesurerEnergie->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";"));

        _10->addWidget(valeurMesurerEnergie, 1, 1, 1, 1);


        verticalLayout_2->addWidget(frameEnergie);

        frameCourantEmission = new QFrame(frame1);
        frameCourantEmission->setObjectName("frameCourantEmission");
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Base, brush);
        palette7.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette7.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        frameCourantEmission->setPalette(palette7);
        frameCourantEmission->setAutoFillBackground(true);
        frameCourantEmission->setFrameShape(QFrame::Shape::WinPanel);
        frameCourantEmission->setFrameShadow(QFrame::Shadow::Plain);
        frameCourantEmission->setLineWidth(1);
        _8 = new QGridLayout(frameCourantEmission);
        _8->setSpacing(6);
        _8->setObjectName("_8");
        lineEditCourantEmission = new QLineEdit(frameCourantEmission);
        lineEditCourantEmission->setObjectName("lineEditCourantEmission");
        lineEditCourantEmission->setFont(font);

        _8->addWidget(lineEditCourantEmission, 1, 0, 1, 1);

        labelCourantEmission = new QLabel(frameCourantEmission);
        labelCourantEmission->setObjectName("labelCourantEmission");
        labelCourantEmission->setFont(font1);
        labelCourantEmission->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _8->addWidget(labelCourantEmission, 0, 0, 1, 1);

        valeurMesurerCourantEmission = new QLabel(frameCourantEmission);
        valeurMesurerCourantEmission->setObjectName("valeurMesurerCourantEmission");
        valeurMesurerCourantEmission->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";"));

        _8->addWidget(valeurMesurerCourantEmission, 1, 1, 1, 1);

        valeurMesurer_3 = new QLabel(frameCourantEmission);
        valeurMesurer_3->setObjectName("valeurMesurer_3");
        valeurMesurer_3->setFont(font1);
        valeurMesurer_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _8->addWidget(valeurMesurer_3, 0, 1, 1, 1);


        verticalLayout_2->addWidget(frameCourantEmission);

        frameFocus = new QFrame(frame1);
        frameFocus->setObjectName("frameFocus");
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::Base, brush);
        palette8.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        frameFocus->setPalette(palette8);
        frameFocus->setAutoFillBackground(true);
        frameFocus->setFrameShape(QFrame::Shape::WinPanel);
        frameFocus->setFrameShadow(QFrame::Shadow::Plain);
        frameFocus->setLineWidth(1);
        _9 = new QGridLayout(frameFocus);
        _9->setSpacing(6);
        _9->setObjectName("_9");
        lineEditFocus = new QLineEdit(frameFocus);
        lineEditFocus->setObjectName("lineEditFocus");
        lineEditFocus->setFont(font);

        _9->addWidget(lineEditFocus, 1, 0, 1, 1);

        valeurMesurer_2 = new QLabel(frameFocus);
        valeurMesurer_2->setObjectName("valeurMesurer_2");
        valeurMesurer_2->setFont(font1);
        valeurMesurer_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _9->addWidget(valeurMesurer_2, 0, 1, 1, 1);

        valeurMesurerFocus = new QLabel(frameFocus);
        valeurMesurerFocus->setObjectName("valeurMesurerFocus");
        valeurMesurerFocus->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";"));

        _9->addWidget(valeurMesurerFocus, 1, 1, 1, 1);

        labelFocus = new QLabel(frameFocus);
        labelFocus->setObjectName("labelFocus");
        labelFocus->setFont(font1);
        labelFocus->setMouseTracking(false);
        labelFocus->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _9->addWidget(labelFocus, 0, 0, 1, 1);

        valeurMesurer_9 = new QLabel(frameFocus);
        valeurMesurer_9->setObjectName("valeurMesurer_9");
        valeurMesurer_9->setFont(font1);
        valeurMesurer_9->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _9->addWidget(valeurMesurer_9, 0, 2, 1, 1);

        valeurMesurerFocusEv = new QLabel(frameFocus);
        valeurMesurerFocusEv->setObjectName("valeurMesurerFocusEv");
        valeurMesurerFocusEv->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";"));

        _9->addWidget(valeurMesurerFocusEv, 1, 2, 1, 1);


        verticalLayout_2->addWidget(frameFocus);

        frameWehnelt = new QFrame(frame1);
        frameWehnelt->setObjectName("frameWehnelt");
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::Base, brush);
        palette9.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette9.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette9.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette9.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        frameWehnelt->setPalette(palette9);
        frameWehnelt->setAutoFillBackground(true);
        frameWehnelt->setFrameShape(QFrame::Shape::WinPanel);
        frameWehnelt->setFrameShadow(QFrame::Shadow::Plain);
        frameWehnelt->setLineWidth(1);
        _7 = new QGridLayout(frameWehnelt);
        _7->setSpacing(6);
        _7->setObjectName("_7");
        labelWehnelt = new QLabel(frameWehnelt);
        labelWehnelt->setObjectName("labelWehnelt");
        labelWehnelt->setFont(font1);
        labelWehnelt->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _7->addWidget(labelWehnelt, 1, 0, 1, 1);

        lineEditWehnelt = new QLineEdit(frameWehnelt);
        lineEditWehnelt->setObjectName("lineEditWehnelt");
        lineEditWehnelt->setFont(font);

        _7->addWidget(lineEditWehnelt, 2, 0, 1, 1);

        valeurMesurer_4 = new QLabel(frameWehnelt);
        valeurMesurer_4->setObjectName("valeurMesurer_4");
        valeurMesurer_4->setFont(font1);
        valeurMesurer_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _7->addWidget(valeurMesurer_4, 1, 1, 1, 1);

        valeurMesurerWehnelt = new QLabel(frameWehnelt);
        valeurMesurerWehnelt->setObjectName("valeurMesurerWehnelt");
        valeurMesurerWehnelt->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";"));

        _7->addWidget(valeurMesurerWehnelt, 2, 1, 1, 1);


        verticalLayout_2->addWidget(frameWehnelt);

        ValidatePushButton = new QPushButton(centralwidget);
        ValidatePushButton->setObjectName("ValidatePushButton");
        ValidatePushButton->setGeometry(QRect(-10, 740, 831, 41));
        ValidatePushButton->setStyleSheet(QString::fromUtf8("font: 15pt \"Segoe UI\";"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 850, 26));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::RightToolBarArea, toolBar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Balayage Y ( mm )", nullptr));
        valeurMesurer_8->setText(QCoreApplication::translate("MainWindow", "Valeur mesur\303\251e", nullptr));
        valeurMesurerBalayageY->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        labelPositionY->setText(QCoreApplication::translate("MainWindow", "Position Y ( mm )", nullptr));
        valeurMesurer_6->setText(QCoreApplication::translate("MainWindow", "Valeur mesur\303\251e", nullptr));
        valeurMesurerPositionY->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        labelBalayageX->setText(QCoreApplication::translate("MainWindow", "Balayage X ( mm )", nullptr));
        valeurMesurer_7->setText(QCoreApplication::translate("MainWindow", "Valeur mesur\303\251e", nullptr));
        valeurMesurerBalayageX->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        labelPositionX->setText(QCoreApplication::translate("MainWindow", "Position X ( mm )", nullptr));
        valeurMesurer_5->setText(QCoreApplication::translate("MainWindow", "Valeur mesur\303\251e", nullptr));
        valeurMesurerPositionX->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_1->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">CONFIGURATION</span></p></body></html>", nullptr));
        pushButtonConnexion->setText(QCoreApplication::translate("MainWindow", "Connexion", nullptr));
        labelEnergie->setText(QCoreApplication::translate("MainWindow", "Energie ( eV )", nullptr));
        valeurMesurer->setText(QCoreApplication::translate("MainWindow", "Valeur mesur\303\251e", nullptr));
        valeurMesurerEnergie->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        labelCourantEmission->setText(QCoreApplication::translate("MainWindow", "Courant d'\303\251mission ( \302\265A )", nullptr));
        valeurMesurerCourantEmission->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        valeurMesurer_3->setText(QCoreApplication::translate("MainWindow", "Valeur mesur\303\251e", nullptr));
        valeurMesurer_2->setText(QCoreApplication::translate("MainWindow", "Valeur mesur\303\251e", nullptr));
        valeurMesurerFocus->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        labelFocus->setText(QCoreApplication::translate("MainWindow", "Focus ( % )", nullptr));
        valeurMesurer_9->setText(QCoreApplication::translate("MainWindow", "Valeur mesur\303\251e", nullptr));
        valeurMesurerFocusEv->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        labelWehnelt->setText(QCoreApplication::translate("MainWindow", "Wehnelt ( V )", nullptr));
        valeurMesurer_4->setText(QCoreApplication::translate("MainWindow", "Valeur mesur\303\251e", nullptr));
        valeurMesurerWehnelt->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        ValidatePushButton->setText(QCoreApplication::translate("MainWindow", "Valider", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
