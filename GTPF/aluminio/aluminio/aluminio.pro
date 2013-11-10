#-------------------------------------------------
#
# Project created by QtCreator 2013-11-10T15:27:58
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = aluminio
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../util/

SOURCES += main.cpp \
    ../../GenomaAluminio.cpp \
    ../../BarraAluminio.cpp \
    ../../FFDW.cpp \
    ../../templatealuminio.cpp

HEADERS += ../../evaluarAluminio.h

OTHER_FILES += parametrosAluminio.cfg
