#ifndef PLANCHA_H
#define PLANCHA_H

#include "Pieza.h"

class Plancha {
public:
    Plancha();
    double ancho() {return _ancho;}
    double alto() {return _alto;}
    void setearAlto(double alto) {_alto = alto;}
    void setearAncho(double ancho) {_ancho = ancho;}
    bool entraPieza(Pieza pieza);
    double areaDisponible() {return _ancho*_alto;}

private:
    double _ancho = 0.0;
    double _alto = 0.0;
};


bool Plancha::entraPieza(Pieza pieza)
{
    if(pieza.ancho() <= _ancho && pieza.alto() <= _alto ) {
        return true;
    }
    return false;
}


#endif // PLANCHA_H
