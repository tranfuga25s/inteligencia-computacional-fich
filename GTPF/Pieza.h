#ifndef PIEZA_H
#define PIEZA_H

class Pieza {
public:
    Pieza();
    Pieza(double x,double y);
    double ancho() {return _ancho;}
    double alto() {return _alto;}
    void setearAlto(double alto) {_alto = alto;}
    void setearAncho(double ancho) {_ancho = ancho;}

private:
    double _ancho;
    double _alto;
};

#endif // PIEZA_H


Pieza::Pieza(double x, double y)
{
    _ancho = x;
    _alto = y;
}
