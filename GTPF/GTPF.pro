QT       += core widgets sql
TARGET = GTPF
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES +=  main.cpp \
            ../util/graficadormdi.cpp \
            ../util/graficador.cpp \
            FFDWDH.cpp \
    TemplatePiezas.cpp \
    Pieza.cpp \
    Plancha.cpp \
    GenomaVidrio.cpp \
    GenomaVentana.cpp \
    templateventana.cpp \
    FFDW.cpp \
    GenomaAluminio.cpp \
    BarraAluminio.cpp \
    templatealuminio.cpp

OTHER_FILES += parametros.cfg \
                aberturas.sqlite \
                parametrosVidrio.cfg \
                parametrosAluminio.cfg

INCLUDEPATH += ../util \
               ../GTP4/EJ1

HEADERS += genomax.h \
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
            poblacion.h \
            GenomaVidrio.h \
            evaluarVidrio.h \
            evaluarAluminio.h \
            GenomaAluminio.h
