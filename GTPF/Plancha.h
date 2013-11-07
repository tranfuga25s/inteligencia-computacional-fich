#ifndef PLANCHA_H
#define PLANCHA_H

#include "Pieza.h"

class Plancha {
public:
    Plancha();
    Plancha(const Plancha & plancha);
    Plancha(Plancha & plancha);
    Plancha(double ancho,double alto);
    double ancho() const { return _ancho; }
    double alto() const { return _alto; }
    void setearAlto (double alto) { _alto = alto; }
    void setearAncho( double ancho ) { _ancho = ancho; }
    bool entraPieza( Pieza pieza );
    double areaDisponible() const { return _ancho * _alto; }

private:
    double _ancho;
    double _alto;
};

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


bool Plancha::entraPieza(Pieza pieza)
{
    if(pieza.ancho() <= _ancho && pieza.alto() <= _alto ) {
        return true;
    }
    return false;
}


#endif // PLANCHA_H
