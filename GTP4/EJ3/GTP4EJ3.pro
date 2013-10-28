QT       += core widgets
TARGET = GTP3
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES +=  main.cpp \
    particula.cpp \
    enjambre.cpp

OTHER_FILES += parametros.cfg \
    parametros.cfg \
    parametros.cfg

INCLUDEPATH += ../../util

HEADERS += \
    genomax.h \
    particula.h \
    ../../util/funciones_aux.h \
    enjambre.h