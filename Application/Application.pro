QT       += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Classes/Alimentation/alimentation.cpp \
    Classes/Communication/communication.cpp \
    Classes/ControleInstrument/controleinstrument.cpp \
    Classes/ReleverMesure/relevermesure.cpp \
    Classes/Worker/worker.cpp \
    Fenetres/Connexion/fenetreconnexion.cpp \
    main.cpp \
    Fenetres/MainWindow/mainwindow.cpp \

HEADERS += \
    Classes/Alimentation/alimentation.h \
    Classes/Communication/communication.h \
    Classes/ControleInstrument/controleinstrument.h \
    Classes/ReleverMesure/relevermesure.h \
    Classes/Worker/worker.h \
    Fenetres/Connexion/fenetreconnexion.h \
    Fenetres/MainWindow/mainwindow.h #\

FORMS += \
    Fenetres/Connexion/fenetreconnexion.ui \
    Fenetres/MainWindow/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
