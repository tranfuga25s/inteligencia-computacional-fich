#include "graficadormdi.h"

GraficadorMdi::GraficadorMdi( QWidget *parent ) :
    Graficador(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
}
