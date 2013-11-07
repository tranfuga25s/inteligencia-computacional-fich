QT       += core widgets
TARGET = GTP3
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES +=  main.cpp \
    ../../util/graficador.cpp \
    ../../util/graficadormdi.cpp \
    ../util/graficadormdi.cpp \
    ../util/graficador.cpp

OTHER_FILES += parametros.cfg \
    parametros.cfg

INCLUDEPATH += ../../util

HEADERS += \
    genomax.h \
    poblacion.h \
    ../../util/graficador.h \
    ../../util/graficadormdi.h \
    ../../util/funciones_aux.h \
    ../util/graficadormdi.h \
    ../util/graficador.h \
    ../util/funciones_aux.h \
    FFDWDH.h \
    Pieza.h \
    Plancha.h