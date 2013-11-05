QT       += core widgets
TARGET = GTP4Ej1b
CONFIG   += console
CONFIG   += qwt

TEMPLATE = app

SOURCES += ../../util/graficador.cpp \
    ../../util/graficadormdi.cpp \
    main.cpp

OTHER_FILES += parametros.cfg

INCLUDEPATH += ../../util \
               ../../EJ1

HEADERS += ../EJ1/genomax.h \
           ../EJ1/poblacion.h \
           ../../util/graficador.h \
           ../../util/graficadormdi.h \
    evaluadorb.h
