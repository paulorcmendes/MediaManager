#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T15:21:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoolMedia
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    medias.c \
    dialogdeletedirect.cpp \
    adicionarmesmo.cpp \
    removermesmo.cpp

HEADERS  += mainwindow.h \
    medias.h \
    dialogdeletedirect.h \
    adicionarmesmo.h \
    removermesmo.h

FORMS    += mainwindow.ui \
    dialogdeletedirect.ui \
    adicionarmesmo.ui \
    removermesmo.ui

RESOURCES += \
    meusrecursos.qrc

DISTFILES +=
