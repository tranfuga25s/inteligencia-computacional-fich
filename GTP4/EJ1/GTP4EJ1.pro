QT       += core widgets
TARGET = GTP3
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES +=  main.cpp \
    poblacion.cpp

OTHER_FILES += parametros.cfg \
    parametros.cfg

INCLUDEPATH += ../../util

HEADERS += \
    genomax.h \
    poblacion.h