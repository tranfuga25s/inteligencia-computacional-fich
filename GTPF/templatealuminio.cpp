#include "templatealuminio.h"


TemplateAluminio::TemplateAluminio()
{
    _largo = 0.0;
    _tipo = 0;
    _cantidad = 0;
}

TemplateAluminio::TemplateAluminio(const TemplateAluminio &origin)
{
    _largo = origin.largo();
    _tipo = origin.tipo();
    _cantidad = origin.getCantidad();
}

TemplateAluminio::TemplateAluminio( TemplateAluminio &origin)
{
    _largo = origin.largo();
    _tipo = origin.tipo();
    _cantidad = origin.getCantidad();
}

