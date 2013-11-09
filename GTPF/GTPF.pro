QT       += core widgets sql
TARGET = GTP3
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES +=  main.cpp \
    ../util/graficadormdi.cpp \
    ../util/graficador.cpp

OTHER_FILES += parametros.cfg \
    parametros.cfg \
    aberturas.sqlite

INCLUDEPATH += ../util \
               ../GTP4/EJ1

HEADERS += \
    genomax.h \
    ../../GTP4/EJ1/poblacion.h \
    ../util/graficadormdi.h \
    ../util/graficador.h \
    ../util/funciones_aux.h \
    FFDWDH.h \
    Pieza.h \
    Plancha.h \
    BarraAluminio.h \
    FFDW.h \
    evaluarVentana.h \
    templatealuminio.h \
    GenomaVentana.h \
    templateventana.h \
    TemplatePiezas.h \
    poblacion.h
