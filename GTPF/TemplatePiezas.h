#ifndef TEMPLATEPIEZAS_H
#define TEMPLATEPIEZAS_H

class TemplatePiezas {

public:
    TemplatePiezas();
    TemplatePiezas( const TemplatePiezas &origin );
    TemplatePiezas( TemplatePiezas &origin );

    void setearAncho( double ancho ) { _ancho = ancho; }
    double ancho() const { return _ancho; }

    void setearAlto( double alto ) { _alto = alto; }
    double alto() const { return _alto; }

    void setearTipo( int tipo ) { _tipo = tipo; }
    int tipo() const { return _tipo; }

    void setearCantidad( int cant ) { _cantidad = cant; }
    int getCantidad() const { return _cantidad; }

    void setearMutado(int num) {_ind_mutado=num;}
    int getMutado() {return _ind_mutado;}



private:
    double _ancho;
    double _alto;
    int _tipo;
    int _cantidad;
    int _ind_mutado=-1;

};

TemplatePiezas::TemplatePiezas() {
    _ancho = 0.0;
    _alto = 0.0;
    _tipo = 0;
    _cantidad = 0;
}

TemplatePiezas::TemplatePiezas(const TemplatePiezas &origin)
{
    _ancho = origin.ancho();
    _alto = origin.alto();
    _tipo = origin.tipo();
    _cantidad = origin.getCantidad();
}

TemplatePiezas::TemplatePiezas( TemplatePiezas &origin)
{
    _ancho = origin.ancho();
    _alto = origin.alto();
    _tipo = origin.tipo();
    _cantidad = origin.getCantidad();
}



#endif // TEMPLATEPIEZAS_H
