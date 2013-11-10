#include "templateventana.h"

TemplateVentana::TemplateVentana()
{
    _ancho = 0.0;
    _alto = 0.0;
    _max_ancho = 0.0;
    _min_ancho = 0.0;
    _max_alto = 0.0;
    _min_alto = 0.0;
    _tipo = 0;
    _cantidad = 0;
    _nombre = QString();
}

TemplateVentana::TemplateVentana( const TemplateVentana &origin )
{
    _ancho = origin.ancho();
    _max_ancho = origin.maxAncho();
    _min_ancho = origin.minAncho();
    _alto = origin.alto();
    _max_alto = origin.maxAlto();
    _min_alto = origin.minAlto();
    _tipo = origin.tipo();
    _cantidad = origin.getCantidad();
    _nombre = origin.nombre();
}

TemplateVentana::TemplateVentana( TemplateVentana &origin )
{
    _ancho = origin.ancho();
    _max_ancho = origin.maxAncho();
    _min_ancho = origin.minAncho();
    _alto = origin.alto();
    _max_alto = origin.maxAlto();
    _min_alto = origin.minAlto();
    _tipo = origin.tipo();
    _cantidad = origin.getCantidad();
    _nombre = origin.nombre();
}

