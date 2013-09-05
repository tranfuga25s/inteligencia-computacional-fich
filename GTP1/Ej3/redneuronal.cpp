#include "redneuronal.h"

RedNeuronal::RedNeuronal(int cantidad_capas , QVector<int> cantidad_neuronas ,int cantidad_entradas,QObject *parent) :
    QObject(parent)
{
    if( cantidad_capas != 0 ) {
        for (int i = 0 ; i < cantidad_capas ; i++ ){
            if ( i == 0 ){
                CapaNeuronal Aux( cantidad_neuronas[i], cantidad_entradas);
                capas.append( Aux );
            } else {
                CapaNeuronal Aux( cantidad_neuronas[i], cantidad_neuronas[i-1] );
                capas.append( Aux );
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

/*!
 * \brief RedNeuronal::inicializarPesos
 */

void RedNeuronal::inicializarPesos()
{
    for( int i=0; i<_cantidad_capas; i++ ) {
        capas[i].inicializarPesos();
    }
}

vector RedNeuronal::forwardPass( vector entradas )
{
    capas[0].evaluar( entradas );
    for( int c=1; c<=_cantidad_capas-1; c++ ) {
        capas[c].evaluar( capas[c-1].getSalidas() );
    }
    return capas[_cantidad_capas-1].getSalidas();
}

/*!
 * \brief RedNeuronal::backwardPass
 * Metodo para hacer la correccion de los deltas para todas las capas y corregir los pesos
 * \param entradas
 * \param salidas
 */
void RedNeuronal::backwardPass( vector entradas, vector salida_deseada )
{
    vector salida = forwardPass( entradas );
    if( salida != salida_deseada ) {
       // Calculo la diferencia para cada parte del vector
       double error;


       for( int i=0; i<salida.size(); i++ ) {
           error = salida_deseada.at( i ) - salida.at( i );
           capas[_cantidad_capas-1].getNeuronas()[i].setDelta( error * capas[_cantidad_capas-1].getNeuronas()[i].getSalida()) ;
       }



       for( int c=_cantidad_capas-2; c>=0; c-- ) {
           for (int n = 0 ; n < capas[c].cantidadNeuronas() ; n++ ) {

               capas[c].corregirDeltas(n,capas[c+1].getDeltas(n));
           }

       }

       capas[0].corregirPesos( entradas );
       for( int c=1; c<_cantidad_capas-1; c++ ) {
           capas[c].corregirPesos( capas[c-1].getSalidas() );
       }
       return;
    }
}

void RedNeuronal::entrenamiento(vector entradas, vector salidas)
{
    forwardPass( entradas );
    backwardPass( entradas , salidas );
}
