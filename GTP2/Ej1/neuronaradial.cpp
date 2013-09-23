#include "neuronaradial.h"

#include <math.h>

NeuronaRadial::NeuronaRadial( int cantidad_entradas )
{
    _cantidad_entradas = cantidad_entradas;
}

void NeuronaRadial::recalcularCentroide( QList<QPointF> lista )
{
    float sumax = 0;
    float sumay = 0;
    foreach( QPointF punto, lista ) {
        sumax+=punto.x();
        sumay+=punto.y();
    }
    _media.setX( sumax / lista.size() );
    _media.setY( sumay / lista.size() );

    float distancia = 0.0;
    foreach( QPointF punto, lista ) {
        float distancia_nueva = sqrt( pow( punto.x() - _media.x(), 2.0 ) + pow( punto.y() - _media.y(), 2.0 ) );
        if( distancia_nueva > distancia ) { distancia = distancia_nueva; }
    }
    _desviacion = distancia;
}

double NeuronaRadial::getSalida( QPointF punto )
{
    return exp( -1 * pow(distanciaCentroide(punto),2) / 2 * pow(_desviacion,2) );
}
