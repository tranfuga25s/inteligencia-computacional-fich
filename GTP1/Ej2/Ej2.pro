#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T09:50:35
#
#-------------------------------------------------

QT       += core
TARGET = Ej2
CONFIG   += console
CONFIG += qwt

TEMPLATE = app


SOURCES += main.cpp \
    neurona.cpp \
    particionador.cpp \
    ../../util/graficador.cpp

HEADERS += \
    neurona.h \
    funciones_aux.h \
    particionador.h \
    ../../util/graficador.h

OTHER_FILES += \
    parametros.cfg \
    ej1.csv \
    tabla2a.csv \
    tabla2b.csv
