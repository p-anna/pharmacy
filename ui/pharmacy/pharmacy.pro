#-------------------------------------------------
#
# Project created by QtCreator 2017-12-10T20:31:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pharmacy
TEMPLATE = app


SOURCES += main.cpp\
        apoteka.cpp \
    login.cpp \
    logout.cpp \
    kupoprodaja.cpp \
    narucivanje.cpp \
    listanar.cpp

HEADERS  += apoteka.h \
    login.h \
    logout.h \
    kupoprodaja.h \
    narucivanje.h \
    listanar.h

FORMS    += apoteka.ui \
    login.ui \
    logout.ui \
    kupoprodaja.ui \
    narucivanje.ui \
    listanar.ui

RESOURCES += \
    images.qrc

DISTFILES += \
    question.jpeg
