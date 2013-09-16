#include "neuronaradial.h"

NeuronaRadial::NeuronaRadial()
{
}

void NeuronaRadial::recalcularCentroide(QList<QPointF> *lista)
{
    float sumax = 0;
    float sumay = 0;
    foreach( QPointF punto, lista ) {
        sumax+=punto.x();
        sumay+=punto.y();
    }
    _media.setX( sumax / lista->size() );
    _media.setY( sumay / lista->size() );

    float distancia = 0.0;
    foreach( QPointF punto, lista ) {
        float distancia_nueva = sqrt( pow( punto.x() - _media.x() ) + pow( punto.y() - _media.y() ) );
        if( distancia_nueva > distancia ) { distancia = distancia_nueva; }
    }
    _desviacion = distancia;
}
