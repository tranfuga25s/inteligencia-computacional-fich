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



#endif // PLANCHA_H
