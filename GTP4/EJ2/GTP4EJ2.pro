QT       += core widgets
TARGET = GTP3
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES +=  main.cpp \
    ../../util/graficador.cpp \
    ../../util/graficadormdi.cpp

OTHER_FILES += parametros.cfg \
    parametros.cfg

INCLUDEPATH += ../../util

HEADERS += \
    genomax.h \
    ../EJ1/poblacion.h \
    evaluador.h \
    ../../util/graficador.h \
    ../../util/graficadormdi.h \
    ../../util/funciones_aux.h \
    genomaciudad.h