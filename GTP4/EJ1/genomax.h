#ifndef GENOMA_H
#define GENOMA_H

#include <QVector>
#include <funciones_aux.h>

/**
 * \brief The Genoma class
 */
class GenomaX
{
public:
    GenomaX();
    void aFenotipo();
    void aGenotipo();
    int size() { return _fenotipo.size(); }
    void mutar( int pos ) { _fenotipo[pos] = !_fenotipo.at( pos ); }
    double getX() { return _x; }

private:
    double _x; // Genotipo
    QVector<bool> _fenotipo;
};

GenomaX::GenomaX() {
    _fenotipo = QVector( 20 );
    _x = 0.0;
}

void GenomaX::aFenotipo() {
    // Convierte el doble en una cadena de bits
    // Tomo la parte entera y la convierto a cadena de bits
    // Tomo la parte decimal y la convierto a cadena de bits
}

void GenomaX::aGenotipo() {
    // Convierte la cadena de bits en un numero doble
    double temporal = 0.0;
    for( int i=0; i<10; i++ ) {
        temporal += pow( 2, i );
    }
    for( int i=10; i<_fenotipo.size(); i++ ) {

    }
}


void mutar( GenomaX &g ) {
    int pos = valor_random( 0, g.size() );
    g.mutar( pos );
    g.aGenotipo();
}

void cruza( GenomaX &a, GenomaX &b ) {
    int pos = valor_random( 0, a.size() );
}


#endif // GENOMA_H
