#ifndef TEMPLATEPIEZAS_H
#define TEMPLATEPIEZAS_H

class TemplatePiezas {

public:
    TemplatePiezas();

    void setearAncho( double ancho ) { _ancho = ancho; }
    double ancho() const { return _ancho; }

    void setearAlto( double alto ) { _alto = alto; }
    double alto() const { return _alto; }

    void setearTipo( int tipo ) { _tipo = tipo; }
    int tipo() { return _tipo; }

    void setearCantidad( int cant ) { _cantidad = cant; }
    int getCantidad() { return _cantidad; }

private:
    double _ancho;
    double _alto;
    int _tipo;
    int _cantidad;

};

#endif // TEMPLATEPIEZAS_H
