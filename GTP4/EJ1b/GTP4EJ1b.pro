QT       += core widgets
TARGET = GTP4Ej1b
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES +=  ../EJ1/main.cpp  \
    ../../util/graficador.cpp \
    ../../util/graficadormdi.cpp

OTHER_FILES += parametros.cfg

INCLUDEPATH += ../../util

HEADERS += ../EJ1/genomax.h \
           evaluador.h \
           ../EJ1/poblacion.h \
           ../../util/graficador.h \
           ../../util/graficadormdi.h