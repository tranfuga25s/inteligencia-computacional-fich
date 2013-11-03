QT       += core widgets
TARGET = GTP4EJ1c
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES +=  main.cpp \
           ../../util/graficador.cpp \
           ../../util/graficadormdi.cpp

OTHER_FILES += parametros.cfg

INCLUDEPATH += ../../util \
               ../EJ1

HEADERS += evaluador.h \
           genomaxy.h \
           ../EJ1/poblacion.h \
           ../../util/graficador.h \
           ../../util/graficadormdi.h