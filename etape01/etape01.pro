#-------------------------------------------------
# Project created by QtCreator
# Support TP du livre "États parallèle avec QStateMachine"
# exemple : qstateparallele
#           etape 01 : version simple
# Daniel Génon - 08500 Revin - 20 mai 2021
# version : 2 : 21/11/2021 version pour QT6.2.1
#-------------------------------------------------
QT += core gui
QT += widgets
QT += statemachine

TARGET = qsparallele-etape01
TEMPLATE = app
CONFIG += c++11
#DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    ../fenetre.cpp \
    ../main.cpp \
    ../objetimage.cpp \
    ../objetmobile.cpp \
    ../sequence.cpp \
    ../vue.cpp \
    ../zoneanime.cpp \
    joueur.cpp \
    arret.cpp \
    transdemarre.cpp \
    couleurjoueur.cpp \
    positionjoueur.cpp \
    bouge.cpp \
    transchange.cpp \
    scene.cpp

HEADERS  += \
    ../fenetre.h \
    ../objetimage.h \
    ../objetmobile.h \
    ../sequence.h \
    ../vue.h \
    ../zoneanime.h \
    joueur.h \
    arret.h \
    transdemarre.h \
    couleurjoueur.h \
    positionjoueur.h \
    bouge.h \
    tranchange.h \
    scene.h
RESOURCES += \
    ../ressources.qrc
