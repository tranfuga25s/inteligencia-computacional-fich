#include "neuronaradial.h"

#include <math.h>

NeuronaRadial::NeuronaRadial( int cantidad_entradas )
{
    _cantidad_entradas = cantidad_entradas;
}

void NeuronaRadial::recalcularCentroide(QList<vector> lista )
{
    vector suma;

    foreach( vector punto, lista ) {
        for (int i = 0; i < punto.size(); i++  ) {
            suma[i] += punto.at(i);
        }
    }
    for( int i =0; i<suma.size(); i++ ) {
        _media[i] = suma.at(i) / lista.size();
    }

    float distancia = 0.0;
    foreach( vector punto, lista ) {
        float distancia_nueva = distanciaCentroide(punto);
        if( distancia_nueva > distancia ) { distancia = distancia_nueva; }
    }
    _desviacion = distancia;
}

double NeuronaRadial::distanciaCentroide(vector punto)
{
    double auxiliar = 0.0;
    for (int i = 0 ; i<punto.size() ; i++) {
        auxiliar += pow( punto.at(i) - _media.at(i), 2.0 );
    }

    return sqrt( auxiliar);
}

double NeuronaRadial::getSalida( vector punto )
{
    return exp( -1 * pow(distanciaCentroide(punto),2) / 2 * pow(_desviacion,2) );
}
