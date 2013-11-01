#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T09:50:35
#
#-------------------------------------------------

QT       += core widgets
TARGET = Ej3
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES += main.cpp \
    neurona.cpp \
    particionador.cpp \
    ../../util/graficador.cpp \
    capaneuronal.cpp \
    redneuronal.cpp \
    ../../util/graficadormdi.cpp

HEADERS += \
    neurona.h \
    particionador.h \
    ../../util/graficador.h \
    ../../util/funciones_aux.h \
    capaneuronal.h \
    redneuronal.h \
    ../../util/graficadormdi.h

OTHER_FILES += parametros.cfg \
    iris.csv \
    concent.csv \
    XOR-extra.csv

INCLUDEPATH += ../../util
