#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T09:50:35
#
#-------------------------------------------------

QT       += core widgets
TARGET = GTP3
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES +=  main.cpp \
    ../util/graficador.cpp \
    ../util/graficadormdi.cpp \
    entorno.cpp \
    exterior.cpp

HEADERS += \
    ../util/funciones_aux.h \
    ../util/graficador.h \
    ../util/graficadormdi.h \
    entorno.h \
    exterior.h


OTHER_FILES += parametros.cfg \

INCLUDEPATH += ../util
