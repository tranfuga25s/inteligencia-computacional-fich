#ifndef GENOMA_H
#define GENOMA_H

#include <QString>
#include <funciones_aux.h>

/**
 * \brief The Genoma class
 */
class GenomaX
{
public:
    void aFenotipo();
    void aGenotipo();
    int size() { return _fenotipo.size(); }
    void mutar( int pos ) { _fenotipo[pos] = !_fenotipo.at( pos ); }
    double getX() { return _x; }

private:
    double _x;
    QString _genotipo;
    QByteArray _fenotipo;
};

void GenomaX::aFenotipo() {
    // Convierte el doble en una cadena de bits
}

void GenomaX::aGenotipo() {
    // Convierte la cadena de bits en un numero doble
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
