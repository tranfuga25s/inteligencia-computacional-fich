QT       += core
QT       -= gui
TARGET = vidrio
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../util/

SOURCES += main.cpp \
    ../../GenomaVidrio.cpp \
    ../../BarraAluminio.cpp \
    ../../FFDWDH.cpp \
    ../../templatealuminio.cpp

HEADERS += ../../evaluarVidrio.h
