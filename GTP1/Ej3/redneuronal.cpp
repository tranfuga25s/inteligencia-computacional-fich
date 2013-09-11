#include "redneuronal.h"

#include <cfloat>

RedNeuronal::RedNeuronal(int cantidad_capas , QVector<int> cantidad_neuronas ,int cantidad_entradas,QObject *parent) :
QObject(parent)
{
    if( cantidad_capas != 0 ) {
        capas.reserve( cantidad_capas );
        for (int i = 0 ; i < cantidad_capas ; i++ ){
            if ( i == 0 ){
                capas.insert( i, new CapaNeuronal( cantidad_neuronas[i], cantidad_entradas) );
            } else {
                capas.insert( i, new CapaNeuronal( cantidad_neuronas[i], cantidad_neuronas[i-1] ) );
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
    for( int i=0; i<capas.size(); i++ ) {
        capas[i]->setearTasaAprendizaje( tasa );
    }
}

/*!
 * \brief RedNeuronal::setearMomento
 * \param momento
 */
void RedNeuronal::setearMomento(double momento)
{
    for( int i=0; i<capas.size(); i++ ) {
        capas[i]->setearMomento( momento );
    }
}

/*!
 * \brief RedNeuronal::inicializarPesos
 */

void RedNeuronal::inicializarPesos()
{
    for( int i=0; i<capas.size(); i++ ) {
        capas[i]->inicializarPesos();
    }
}

/*!
 * \brief RedNeuronal::forwardPass
 * \param entradas
 * \return
 */
vector RedNeuronal::forwardPass( vector entradas )
{
    capas[0]->evaluar( entradas );
    for( int c=1; c<capas.size(); c++ ) {
        capas[c]->evaluar( capas[c-1]->getSalidas() );
    }
    return capas[capas.size()-1]->getSalidas();
}

/*!
 * \brief RedNeuronal::backwardPass
 * Metodo para hacer la correccion de los deltas para todas las capas y corregir los pesos
 * \param entradas
 * \param salidas
 */
void RedNeuronal::backwardPass( vector entradas, double salida_deseada )
{
    vector salida = forwardPass( entradas );

    int sal_codif = mapeadorSalidas(salida);

    // Tanto la salida codificada como la salida deseada están codificadas
    // El vector de la salida deseada tiene un solo elemento
    if( sal_codif != salida_deseada ) {
        vector salida_deseada_vector = mapeadorInverso( salida_deseada );

        // CORRECCION DELTAS ULTIMA CAPA
        for( int i=0; i<salida_deseada_vector.size(); i++ ) {

            double error = salida.at( i ) - salida_deseada_vector.at( i );
            double derivada = Neurona::funcionActivacionDerivada( salida.at(i) );
            double delta = error * derivada;
            capas[capas.size()-1]->getNeuronas()[i]->setDelta( delta );

        }

        // CORRECCION DELTAS RESTANTES CAPAS
        for( int c = capas.size()-2 ; c >= 0 ; c-- ) {

            for (int n = 0 ; n < capas[c]->cantidadNeuronas() ; n++ ) {

                capas[c]->corregirDeltas( n, capas[c+1]->getDeltas(n) );
            }

        }
        //UNA VEZ QUE CORREGI LOS DELTAS DE LA RED CORRIJO LOS PESOS
        capas[0]->corregirPesos( entradas );
        for( int c=1; c<capas.size(); c++ ) {
            capas[c]->corregirPesos( capas[c-1]->getSalidas() );
        }
    }
    return;

}

/*!
 * \brief RedNeuronal::entrenamiento
 * \param entradas
 * \param salidas
 */
void RedNeuronal::entrenamiento( vector entradas, double salidas )
{
    forwardPass( entradas );
    backwardPass( entradas , salidas );
}

/*!
 * \brief RedNeuronal::setearCodificacion
 * \param codif
 */
void RedNeuronal::setearCodificacion( QVector<int> codif )
{ codif_salidas = codif; }

/*!
 * \brief RedNeuronal::mapeadorSalidas
 * \param salidas
 * \return
 */
int RedNeuronal::mapeadorSalidas(vector salidas)
{
    //Esto es el caso de que haya una sola neurona en la ultima capa
    if( salidas.size() == 1 ) {return salidas.at(0);}

    if( salidas.size() == 2 ) {
        if( salidas.at(0) > salidas.at(1) ) {
            return 0;
        } else {
            return 1;
        }
    }

    double max = (-1.0)*DBL_MAX;
    int mayor = 0;

    for(int i = 0 ; i < salidas.size() ; i++) {
        //La comparacion implica que me quedo con el primer maximo encontrado
        if (salidas.at(i) > max) {
            max = salidas.at(i);
            mayor = i;
        }
    }

    return codif_salidas.at(mayor);

}

/*!
 * \brief RedNeuronal::mapeadorInverso
 * \param valor
 * \return
 */
vector RedNeuronal::mapeadorInverso( int valor )
{
    //Deberia devolver cualquier vector salida que me genere el valor
    vector retorno;
    // Los valores que tiene que contener los vectores de
    // comparación para las neuronas tienen que ser acordes a la funcion
    // de activación que se esté tuilizando
    for( int i=0; i<codif_salidas.size(); i++ ) {
        if( valor == codif_salidas.at( i ) ) {
            retorno.insert( i, 1.0  );
        } else {
            retorno.insert( i, -1.0 );
        }
    }
    return retorno;
}
