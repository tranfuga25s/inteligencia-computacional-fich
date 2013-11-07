#ifndef TEMPLATEVENTANA_H
#define TEMPLATEVENTANA_H

class TemplateVentana {

public:
    TemplateVentana();

    void setearAncho( double ancho ) { _ancho = ancho; }
    double ancho() const { return _ancho; }

    void setearAlto( double alto ) { _alto = alto; }
    double alto() const { return _alto; }

    void setearTipo( int tipo ) { _tipo = tipo; }
    int tipo() { return _tipo; }

    void setearCantidad( int cant ) { _cantidad = cant; }
    int getCantidad() { return _cantidad; }

    void setearNombre( QString nombre ) { _nombre = nombre; }
    QString nombre() const { return _nombre; }

private:
    double _ancho;
    double _alto;
    int _tipo;
    int _cantidad;
    QString _nombre;

};


#endif // TEMPLATEVENTANA_H
