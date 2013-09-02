#include "redneuronal.h"

RedNeuronal::RedNeuronal(int cantidad_capas , QVector<int> cantidad_neuronas ,int cantidad_entradas,QObject *parent) :
    QObject(parent)
{
    if( cantidad_capas != 0 ) {
        for (int i = 0 ; i < cantidad_capas ; i++ ){
            if ( i == 0 ){
                capas.append( CapaNeuronal( cantidad_neuronas.at(i), cantidad_entradas, this ) );
            } else {
                capas.append( CapaNeuronal( cantidad_neuronas.at(i), cantidad_neuronas.at(i-1), this ) );
            }
        }
    }
}

/*!
 * \brief RedNeuronal::setearTasaAprendizaje
 * \param tasa
 */
void RedNeuronal::setearTasaAprendizaje( double tasa )
{
    for( int i=0; i<_cantidad_capas; i++ ) {
        capas[i].setearTasaAprendizaje( tasa );
    }
}

void RedNeuronal::reinicializarPesos()
{
    /// @TODO LUCHOS hacete esto...
}

double RedNeuronal::evaluar( vector entradas )
{
    capa[0].evaluar( entradas );
    for( int c=1; c<=_cantidad_capas-1; c++ ) {
        capa[c].evaluar( capa[c-1].getSalidas() );
    }
    return capa[_cantidad_capas-1].getSalidas();
}

/*!
 * \brief RedNeuronal::entrenamiento
 * \param entradas
 * \param salidas
 */
void RedNeuronal::entrenamiento( vector entradas, vector salida_deseada )
{
    QVector salida = evaluar( entradas );
    if( salida != salida_deseada ) {
       // Calculo la diferencia para cada parte del vector
       vector error;
       for( int i=0; i<salida.size(); i++ ) {
           error.append( salida_deseada.at( i ) - salida.at( i ) );
       }

       capas[_cantidad_capas-1].backPropagation( error );
       for( int c=_cantidad_capas-2; c>=0; c-- ) {
           capas[c].backPropagation( capas[c+1].getDeltas() );
       }

       capas[0].corregirPesos( entradas );
       for( int c=1; c<_cantidad_capas-1; c++ ) {
           capas[c].corregirPesos( capas[c-1].getSalidas() );
       }
       return;
    }
}
