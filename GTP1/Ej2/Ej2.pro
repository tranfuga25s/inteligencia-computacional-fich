#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T09:50:35
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Ej2
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    neurona.cpp \
    particionador.cpp

HEADERS += \
    neurona.h \
    funciones_aux.h \
    particionador.h

OTHER_FILES += \
    parametros.cfg \
    ej1.csv \
    tabla2.csv