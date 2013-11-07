#ifndef PIEZA_H
#define PIEZA_H

class Pieza {
public:
    Pieza();
    Pieza(double x,double y);
    Pieza( const Pieza &origin );
    Pieza( Pieza &origin );
    double ancho() const { return _ancho; }
    double alto() const { return _alto; }
    void setearAlto(double alto) {_alto = alto;}
    void setearAncho(double ancho) {_ancho = ancho;}

private:
    double _ancho;
    double _alto;
};

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

#endif // PIEZA_H
