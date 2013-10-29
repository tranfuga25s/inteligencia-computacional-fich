QT       += core widgets
TARGET = GTP3
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES +=  main.cpp \
    particula.cpp \
    enjambre.cpp \
    particula_parametrica.cpp \
    enjambre_parametrico.cpp

OTHER_FILES +=

INCLUDEPATH += ../../util

HEADERS += \
    genomax.h \
    particula.h \
    ../../util/funciones_aux.h \
    enjambre.h \
    particula_parametrica.h \
    enjambre_parametrico.h