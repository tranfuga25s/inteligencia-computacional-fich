#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T09:50:35
#
#-------------------------------------------------

QT       += core
TARGET = Ej3
CONFIG   += console
CONFIG += qwt

TEMPLATE = app

SOURCES += main.cpp \
    neurona.cpp \
    particionador.cpp \
    ../../util/graficador.cpp \
    capaneuronal.cpp \
    redneuronal.cpp \
    ../../util/graficadormdi.cpp \
    redneuronalradial.cpp \
    capaneuronalradial.cpp \
    neuronaradial.cpp

HEADERS += \
    neurona.h \
    particionador.h \
    ../../util/graficador.h \
    ../../util/funciones_aux.h \
    capaneuronal.h \
    redneuronal.h \
    ../../util/graficadormdi.h \
    redneuronalradial.h \
    capaneuronalradial.h \
    neuronaradial.h

OTHER_FILES += parametros.cfg \
    iris.csv \
    concent.csv \
    XOR-etra.csv

INCLUDEPATH += ../../util
