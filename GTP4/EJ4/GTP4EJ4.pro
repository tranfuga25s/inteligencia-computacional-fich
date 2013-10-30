QT       += core widgets
TARGET = GTP3
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES +=  main.cpp \
    particula.cpp \
    enjambre.cpp \
    redneuronal.cpp \
    neurona.cpp \
    capaneuronal.cpp \
    ../../util/graficador.cpp \
    ../../util/graficadormdi.cpp

OTHER_FILES += \
    parametros.cfg \
    clouds.csv

INCLUDEPATH += ../../util

HEADERS += \
    genomax.h \
    particula.h \
    ../../util/funciones_aux.h \
    enjambre.h \
    redneuronal.h \
    neurona.h \
    capaneuronal.h \
    ../../util/graficador.h \
    ../../util/graficadormdi.h
