#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T09:50:35
#
#-------------------------------------------------

QT       += core
TARGET = GTP2EJ3
CONFIG   += console
CONFIG += qwt

TEMPLATE = app

SOURCES +=  \
            ../../util/graficador.cpp \
            ../../util/graficadormdi.cpp \
            som.cpp \
    main.cpp

HEADERS +=  ../../util/graficador.h \
            ../../util/funciones_aux.h \
            ../../util/graficadormdi.h \
            som.h

OTHER_FILES += parametros.cfg \
               clouds.csv \
               clouds.txt \
               phoneme.csv \
               phoneme.txt

INCLUDEPATH += ../../util
