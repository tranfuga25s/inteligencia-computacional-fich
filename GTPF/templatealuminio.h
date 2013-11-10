#ifndef TEMPLATEALUMINIO_H
#define TEMPLATEALUMINIO_H

class TemplateAluminio {

public:
    TemplateAluminio();
    TemplateAluminio( const TemplateAluminio &origin );
    TemplateAluminio( TemplateAluminio &origin );

    void setearLargo( double largo ) { _largo = largo; }
    double largo() const { return _largo; }

    void setearTipo( int tipo ) { _tipo = tipo; }
    int tipo() const { return _tipo; }

    void setearCantidad( int cant ) { _cantidad = cant; }
    int getCantidad() const { return _cantidad; }

private:
    double _largo;
    int _tipo;
    int _cantidad;

};

#endif // TEMPLATEALUMINIO_H
