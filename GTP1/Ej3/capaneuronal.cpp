#include "capaneuronal.h"
#include "neurona.h"

CapaNeuronal::CapaNeuronal( int cant_neuronas, int cant_entradas , QObject *parent ) :
    QObject(parent)
{
    if( cant_neuronas != 0 ) {
        for (int i = 0 ; i < cant_neuronas ; i++ ){
            neuronas.append( Neurona( this, cant_entradas ) );
        }
    }
}

void CapaNeuronal::setearTasaAprendizaje(double tasa)
{
    for( int i=0; i<_cantidad_neuronas; i++ ) {
        neuronas[i].setearTasaAprendizaje( tasa );
    }
}

void CapaNeuronal::entrenar( vector entradas )
{
    for( int n=0; n<_cantidad_neuronas; n++ ) {
        neuronas[n].evaluar( entradas );
    }
}

vector CapaNeuronal::getSalidas()
{
    vector temp;
    for( int n=0; n<_cantidad_neuronas; n++ ) {
        temp.append( n.getSalida() );
    }
    return temp;
}


vector CapaNeuronal::getDeltas()
{

}
