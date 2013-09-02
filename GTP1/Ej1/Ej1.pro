#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T09:50:35
#
#-------------------------------------------------

TARGET = Ej1
CONFIG += qwt
TEMPLATE = app

SOURCES += main.cpp \
    neurona.cpp \
    ../../util/graficador.cpp

HEADERS += neurona.h \
    funciones_aux.h \
    ../../util/graficador.h \
    ../../util/funciones_aux.h

OTHER_FILES += parametros.cfg \
    ej1-XOR.csv \
    ej1-OR.csv

INCLUDEPATH += ../../util
