#ifndef GRAFICADORMDI_H
#define GRAFICADORMDI_H

#include "graficador.h"

class GraficadorMdi : public Graficador
{
    Q_OBJECT
public:
    explicit GraficadorMdi( QWidget *parent = 0 );
    
};

#endif // GRAFICADORMDI_H
