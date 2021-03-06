#include "neuronaradial.h"

#include <math.h>

NeuronaRadial::NeuronaRadial( int cantidad_entradas )
{
    _cantidad_entradas = cantidad_entradas;
    _media.reserve( cantidad_entradas );
}

void NeuronaRadial::recalcularCentroide( QList<vector> lista )
{
    vector suma( lista.at(0).size() );
    _media.resize( lista.at(0).size() );

    //aca cambie los [] por append para suma y para _media
    foreach( vector punto, lista ) {
         for (int i = 0; i < punto.size(); i++ ) {
             suma[i] += punto.at(i);
        }
    }

    for( int i =0; i<suma.size(); i++ ) {
        _media[i] = suma.at(i) / lista.size();
    }

    float distancia = 0.0;
    foreach( vector punto, lista ) {
        float distancia_nueva = distanciaCentroide( punto );
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
    return exp( ( -1.0 * pow(distanciaCentroide(punto),2.0) ) / ( 2.0 * pow(_desviacion,2.0) ) );
}
