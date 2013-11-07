#ifndef TEMPLATEVENTANA_H
#define TEMPLATEVENTANA_H

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

TemplateVentana::TemplateVentana()
{
    _ancho = 0.0;
    _alto = 0.0;
    _max_ancho = 0.0;
    _min_ancho = 0.0;
    _max_alto = 0.0;
    _min_alto = 0.0;
    _tipo = 0;
    _cantidad = 0;
    _nombre = QString();
}

TemplateVentana::TemplateVentana( const TemplateVentana &origin )
{
    _ancho = origin.ancho();
    _max_ancho = origin.maxAncho();
    _min_ancho = origin.minAncho();
    _alto = origin.alto();
    _max_alto = origin.maxAlto();
    _min_alto = origin.minAlto();
    _tipo = origin.tipo();
    _cantidad = origin.getCantidad();
    _nombre = origin.nombre();
}

TemplateVentana::TemplateVentana( TemplateVentana &origin )
{
    _ancho = origin.ancho();
    _max_ancho = origin.maxAncho();
    _min_ancho = origin.minAncho();
    _alto = origin.alto();
    _max_alto = origin.maxAlto();
    _min_alto = origin.minAlto();
    _tipo = origin.tipo();
    _cantidad = origin.getCantidad();
    _nombre = origin.nombre();
}
#endif // TEMPLATEVENTANA_H
