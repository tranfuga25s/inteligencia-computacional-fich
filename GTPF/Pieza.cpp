#include "Pieza.h"


Pieza::Pieza(double x, double y)
{
    _ancho = x;
    _alto = y;
}

Pieza::Pieza()
{
    _ancho = 0.0;
    _alto = 0.0;
}


Pieza::Pieza( const Pieza &origin )
{
    _ancho = origin.ancho();
    _alto = origin.alto();
}

Pieza::Pieza( Pieza &origin )
{
    _ancho = origin.ancho();
    _alto = origin.alto();
}
