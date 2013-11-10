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

#endif // PIEZA_H
