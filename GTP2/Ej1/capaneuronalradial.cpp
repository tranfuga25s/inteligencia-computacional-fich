#include <QVector>
#include "capaneuronalradial.h"

CapaNeuronalRadial::CapaNeuronalRadial( int cantidad_neuronas, int cantidad_entradas )
{
    if( cantidad_neuronas != 0 ) {
        _neuronas = new QVector<NeuronaRadial>();
        _neuronas->reserve( cantidad_neuronas );
        for( int i=0; i<cantidad_neuronas; i++ ) {
            _neuronas->insert( i, NeuronaRadial( cantidad_entradas ) );
        }
    }
}

void CapaNeuronalRadial::setearTasaAprendizaje( double )
{
    return;
}

void CapaNeuronalRadial::setearMomento( double )
{
    return;
}

QVector<double> CapaNeuronalRadial::getSalidas( QPointF entrada )
{
    QVector<double> temp;
    for( int i=0; i<_neuronas->size(); i++ ) {
        temp.append( _neuronas->operator []( i ).getSalida( entrada ) );
    }
    return temp;
}
