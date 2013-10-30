QT       += core widgets
TARGET = GTP4Ej1b
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES +=  main.cpp

OTHER_FILES += parametros.cfg

INCLUDEPATH += ../../util

HEADERS += genomax.h \
           poblacion.h \
           evaluador.h