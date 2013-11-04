#ifndef GENOMAXY_H
#define GENOMAXY_H

#define cant_entera 10 // 2^10 = 1024
#define cant_decimal 5 // Hasta 5 elementos de la posicion decimal

#include <QVector>
#include <funciones_aux.h>

/**
 * \brief The Genoma class
 */
class GenomaXY
{
public:
    GenomaXY();
    GenomaXY( const GenomaXY &origin );
    GenomaXY( GenomaXY& origin );
    void aFenotipo();
    void aGenotipo();
    int size() { return _genotipo.size(); }
    void mutar( int pos ) { _genotipo[pos] = !_genotipo.at( pos ); aFenotipo(); }
    double getX() const { return _x; }
    double getY() const { return _y; }
    bool at( int pos ) { return this->_genotipo.at( pos ); }
    void setearGenoma( int i, bool valor) { this->_genotipo[i] = valor; }
    void setX( double valor );
    void setY( double valor );
    void mostrarGenotipo();
    void setMinMax( double min, double max ) { _min = min; _max = max; }
    double getMin() const { return _min; }
    double getMax() const { return _max; }

private:
    double _x; // Fenotipo x
    double _y; // Fenotipo y
    double _min, _max;
    QVector<bool> _genotipo;
};

GenomaXY::GenomaXY() {
    _genotipo.clear();
    for(int i = 0; i < ( cant_decimal + cant_entera + 1 ) * 2; i++) {
        _genotipo.append(false);
    }
    _x = 0.0;
    _y = 0.0;
    _min = 0.0;
    _max = 0.0;
}

GenomaXY::GenomaXY( const GenomaXY& origin ) {
    this->_x = origin.getX();
    this->_y = origin.getY();
    this->_min = origin.getMin();
    this->_max = origin.getMax();
    aGenotipo();
}

GenomaXY::GenomaXY( GenomaXY &origin ) {
    this->_x = origin.getX();
    this->_y = origin.getY();
    this->_min = origin.getMin();
    this->_max = origin.getMax();
    aGenotipo();
}

void GenomaXY::setX( double valor ) {
    _x = valor;
    aGenotipo();
}

void GenomaXY::setY( double valor ) {
    _y = valor;
    aGenotipo();
}

void GenomaXY::aGenotipo() {
    // Convierte el doble en una cadena de bits
    // Tomo la parte entera y la convierto a cadena de bits
    // Tomo la parte decimal y la convierto a cadena de bits

    if( _genotipo.size() == 0 ) {
        for(int i = 0; i < ( cant_decimal + cant_entera + 1 ) * 2; i++) {
            _genotipo.append(false);
        }
    }

    double x_aux_decimal = 0.0;
    double x_aux_entero = 0.0;
    x_aux_decimal = modf( _x, &x_aux_entero );
    x_aux_decimal *= pow( 10, cant_decimal );
    modf( x_aux_decimal, &x_aux_decimal );

    // Positivo o negativo
    if( _x > 0.0 ) {
        _genotipo[cant_decimal + cant_entera + 1] = true;
    } else {
        _genotipo[cant_decimal + cant_entera + 1] = false;
    }

    //Parte Entera
    for (int i = cant_entera - 1 ; i>=0 ; i--) {
        if( fmod( x_aux_entero, 2.0 ) == 1.0) {
            _genotipo[i] = true;
        }
        else
        {
            _genotipo[i]  = false;
        }

        x_aux_entero = x_aux_entero/2.0;
        modf( x_aux_entero, &x_aux_entero );
    }

    //Parte decimal
    for (int i = cant_entera ; i < cant_entera + cant_decimal ; i++) {
        if( fmod( x_aux_decimal, 2.0 ) == 1.0) {
            _genotipo[i] = true;
        }
        else
        {
            _genotipo[i] = false;
        }

        x_aux_decimal /= 2.0;
        modf( x_aux_decimal, &x_aux_decimal );
     }


    // Parte del y
    int desplazamiento = cant_entera + cant_decimal + 1;
    double y_aux_decimal = 0.0;
    double y_aux_entero = 0.0;
    y_aux_decimal = modf( _y, &y_aux_entero );
    y_aux_decimal *= pow( 10, cant_decimal );
    modf( y_aux_decimal, &y_aux_decimal );

    // Positivo o negativo
    if( _y > 0.0 ) {
        _genotipo[_genotipo.size()-1] = true;
    } else {
        _genotipo[_genotipo.size()-1] = false;
    }

    //Parte Entera
    for (int i = cant_entera - 1 ; i >=0; i--) {
        if( fmod( y_aux_entero, 2.0 ) == 1.0) {
            _genotipo[desplazamiento+i] = true;
        }
        else
        {
            _genotipo[desplazamiento+i]  = false;
        }

        y_aux_entero = y_aux_entero/2.0;
        modf( y_aux_entero, &y_aux_entero );
    }

    //Parte decimal
    for (int i = cant_entera ; i < cant_entera + cant_decimal ; i++) {
        if( fmod( y_aux_decimal, 2.0 ) == 1.0) {
            _genotipo[desplazamiento+i] = true;
        }
        else
        {
            _genotipo[desplazamiento+i] = false;
        }

        y_aux_decimal /= 2.0;
        modf( y_aux_decimal, &y_aux_decimal );
     }


}

void GenomaXY::aFenotipo() {
    // Convierte la cadena de bits en un numero doble
    double temporal = 0.0;
    for( int i=cant_entera; i>=0; i-- ) {
        if (_genotipo.at(i)) {
            temporal += pow( 2.0, (cant_entera-1) - i );
        }
    }
    for( int i=cant_entera; i<cant_entera + cant_decimal; i++ ) {
        if (_genotipo.at(i)) {
            temporal += pow( 2.0, (-1)*( i - ( cant_entera - 1 ) ) );
        }
    }
    if( _genotipo.at( cant_entera + cant_decimal ) == false ) {
        temporal *= (-1.0);
    }
    _x = temporal;

    int desplazamiento = cant_entera + cant_decimal + 1;
    temporal = 0.0;
    for( int i=cant_entera; i>=0; i-- ) {
        if (_genotipo.at(desplazamiento+i)) {
            temporal += pow( 2.0, desplazamiento+ ( cant_entera - 1 ) - i );
        }
    }
    for( int i=cant_entera; i<cant_entera + cant_decimal; i++ ) {
        if (_genotipo.at(desplazamiento+i)) {
            temporal += pow( 2.0, (-1)*(i - desplazamiento+( cant_entera - 1 )) );
        }
    }
    if( _genotipo.at( _genotipo.size() -1 ) == false ) {
        temporal *= (-1.0);
    }
    _x = temporal;
}


static void mutar( GenomaXY &g ) {
    int pos = valor_random_int( 0, g.size() );
    g.mutar( pos );
    g.aFenotipo();
}

static void cruza( GenomaXY &a, GenomaXY &b ) {
    //Asumimos que tienen la misma profundidad de bits los genomas

    int pos = valor_random_int( 0, a.size() );
    //qDebug() << pos;

    GenomaXY auxA = a;
    GenomaXY auxB = b;

    for (int i = pos; i<a.size(); i++) {
        auxB.setearGenoma( i, a.at(i) );
        auxA.setearGenoma( i, b.at(i) );
    }
    a.aFenotipo();
    b.aFenotipo();

    a = auxA;
    b = auxB;

    a.aFenotipo();
    b.aFenotipo();
}

void GenomaXY::mostrarGenotipo() {
    QString salida;
    salida.append( QString( "Genotipo:%1,%2:" ).arg( _x ).arg( _y ) );
    foreach( bool val, _genotipo ) {
        if( val ) {
            salida.append( "1" );
        } else {
            salida.append( "0" );
        }
    }
    qDebug() << salida;
}


#endif // GENOMAXY_H
