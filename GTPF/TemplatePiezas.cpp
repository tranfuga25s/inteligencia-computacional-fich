#include "TemplatePiezas.h"

TemplatePiezas::TemplatePiezas() {
    _ancho = 0.0;
    _alto = 0.0;
    _tipo = 0;
    _cantidad = 0;
    _ind_mutado = -1;
}

TemplatePiezas::TemplatePiezas(const TemplatePiezas &origin)
{
    _ancho = origin.ancho();
    _alto = origin.alto();
    _tipo = origin.tipo();
    _cantidad = origin.getCantidad();
    _ind_mutado = origin.getMutado();
}

TemplatePiezas::TemplatePiezas( TemplatePiezas &origin)
{
    _ancho = origin.ancho();
    _alto = origin.alto();
    _tipo = origin.tipo();
    _cantidad = origin.getCantidad();
    _ind_mutado = origin.getMutado();
}

