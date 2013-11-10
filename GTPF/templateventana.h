#ifndef TEMPLATEVENTANA_H
#define TEMPLATEVENTANA_H

#include <QString>

class TemplateVentana {

public:
    TemplateVentana();
    TemplateVentana( const TemplateVentana &origin );
    TemplateVentana( TemplateVentana &origin );

    void setearAncho( double ancho ) { _ancho = ancho; }
    double ancho() const { return _ancho; }
    void setearMaxAncho( double max_ancho ) { _max_ancho = max_ancho; }
    double maxAncho() const { return _max_ancho; }
    void setearMinAncho( double min_ancho ) { _min_ancho = min_ancho; }
    double minAncho() const { return _min_ancho; }

    void setearAlto( double alto ) { _alto = alto; }
    double alto() const { return _alto; }
    void setearMaxAlto( double max_alto ) { _max_alto = max_alto; }
    double maxAlto() const { return _max_alto; }
    void setearMinAlto( double min_alto ) { _min_alto = min_alto; }
    double minAlto() const { return _min_alto; }

    void setearTipo( int tipo ) { _tipo = tipo; }
    int tipo() const { return _tipo; }

    void setearCantidad( int cant ) { _cantidad = cant; }
    int getCantidad() const { return _cantidad; }

    void setearNombre( QString nombre ) { _nombre = nombre; }
    QString nombre() const { return _nombre; }

private:
    double _ancho;
    double _max_ancho;
    double _min_ancho;
    double _alto;
    double _max_alto;
    double _min_alto;
    int _tipo;
    int _cantidad;
    QString _nombre;

};

#endif // TEMPLATEVENTANA_H
