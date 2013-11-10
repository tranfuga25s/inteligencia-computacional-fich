#include "Plancha.h"

Plancha::Plancha()
{
    _ancho = 0.0;
    _alto = 0.0;
}

Plancha::Plancha(const Plancha &plancha)
{
    this->_ancho = plancha.ancho();
    this->_alto = plancha.alto();
}

Plancha::Plancha(Plancha &plancha)
{
    this->_ancho = plancha.ancho();
    this->_alto = plancha.alto();
}

Plancha::Plancha(double ancho,double alto) {
    _ancho = ancho;
    _alto = alto;
}


bool Plancha::entraPieza(Pieza pieza) const
{
    if(pieza.ancho() <= _ancho && pieza.alto() <= _alto ) {
        return true;
    }
    return false;
}
