#ifndef GENOMA_H
#define GENOMA_H

#define cant_entera 10
#define cant_decimal 10

#include <QVector>
#include <funciones_aux.h>

/**
 * \brief The Genoma class
 */
class GenomaX
{
public:
    GenomaX();
    GenomaX( const GenomaX &origin );
    GenomaX( GenomaX& origin );
    void aFenotipo();
    void aGenotipo();
    int size() { return _genotipo.size(); }
    void mutar( int pos ) { _genotipo[pos] = !_genotipo.at( pos ); }
    double getX() const { return _x; }
    bool at( int pos ) { return _genotipo.at( pos ); }
    bool & operator[] ( int i ) { return _genotipo[i]; }
    void setX( double valor );
    void mostrarFeneotipo();

private:
    double _x; // Fenotipo
    QVector<bool> _genotipo;
};

GenomaX::GenomaX() {
    _genotipo.clear();
    for(int i = 0; i < 20 ; i++) {
        _genotipo.append(false);
    }
    _x = 0.0;
}

GenomaX::GenomaX( const GenomaX& origin ) {
    _x = origin.getX();
    aGenotipo();
}

GenomaX::GenomaX( GenomaX &origin ) {
    this->_x = origin.getX();
    aGenotipo();
}

void GenomaX::setX(double valor) {
    this->_x = valor;
    aGenotipo();
}

void GenomaX::aGenotipo() {
    // Convierte el doble en una cadena de bits
    // Tomo la parte entera y la convierto a cadena de bits
    // Tomo la parte decimal y la convierto a cadena de bits

    int x_aux_entero = floor(_x);
    double x_aux_decimal = (_x - floor(_x) * pow(10,cant_decimal));

    //Parte Entera
    for (int i = cant_entera - 1 ; i>=0 ; i--) {
        if(floor(fmod(x_aux_entero,2.0)) == 1.0) {
            _genotipo[i] = true;
        }
        else
        {
            _genotipo[i]  = false;
        }

        x_aux_entero = x_aux_entero/2.0;
    }

    //Parte decimal
    for (int i = cant_entera ; i < cant_entera + cant_decimal ; i++) {
        if(floor(fmod(x_aux_decimal,2.0)) == 1.0) {
            _genotipo[i] = true;
        }
        else
        {
            _genotipo[i] = false;
        }

        x_aux_decimal = x_aux_decimal/2.0;
     }


}

void GenomaX::aFenotipo() {
    // Convierte la cadena de bits en un numero doble
    double temporal = 0.0;
    for( int i=cant_entera; i>=0; i-- ) {
        if (_genotipo.at(i)) {
            temporal += pow( 2.0, cant_entera - i );
        }
    }
    for( int i=cant_entera; i<_genotipo.size(); i++ ) {
        if (_genotipo.at(i)) {
            temporal += pow( 2.0, (-1)*(i - cant_entera) );
        }
    }
}


static void mutar( GenomaX &g ) {
    int pos = valor_random( 0, g.size() );
    g.mutar( pos );
    g.aFenotipo();
}

static void cruza( GenomaX &a, GenomaX &b ) {
    //Asumimos que tienen la misma profundidad de bits los genomas

    int pos = valor_random( 0, a.size() );

    GenomaX auxA = a;
    GenomaX auxB = b;

    for (int i = pos; i<a.size(); i++) {
        auxB[i] = a.at(i);
        auxA[i] = b.at(i);
    }

    a = auxA;
    b = auxB;

}

void GenomaX::mostrarFeneotipo() {
    QString salida;
    salida.append( QString( "Genotipo:%1:" ).arg( _x ) );
    foreach( bool val, _genotipo ) {
        if( val ) {
            salida.append( "1" );
        } else {
            salida.append( "0" );
        }
    }
    qDebug() << salida;
}


#endif // GENOMA_H
