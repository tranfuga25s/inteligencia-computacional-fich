#include "redneuronal.h"

#include <cfloat>

RedNeuronal::RedNeuronal(int cantidad_capas , QVector<int> cantidad_neuronas , int cantidad_entradas)
{
    if( cantidad_capas != 0 ) {
        //capas.resize( cantidad_capas );
        for (int i = 0 ; i < cantidad_capas ; i++ ){
            if ( i == 0 ){
                //capas.insert( i, new CapaNeuronal( cantidad_neuronas[i], cantidad_entradas) );
                capas.append(new CapaNeuronal( cantidad_neuronas[i], cantidad_entradas) );
            } else {
                //capas.insert( i, new CapaNeuronal( cantidad_neuronas[i], cantidad_neuronas[i-1] ) );
                capas.append( new CapaNeuronal( cantidad_neuronas[i], cantidad_neuronas[i-1] ) );
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

///*!
// * \brief RedNeuronal::setearMomento
// * \param momento
// */
//void RedNeuronal::setearMomento(double momento)
//{
//    for( int i=0; i<capas.size(); i++ ) {
//        capas[i]->setearMomento( momento );
//    }
//}

/*!
 * \brief RedNeuronal::inicializarPesos
 */

void RedNeuronal::inicializarPesos()
{
    for( int i=0; i<capas.size(); i++ ) {
        capas[i]->inicializarPesos();
    }
}

//!
//! \brief RedNeuronal::cantidadPesos
//!Retorna la cantidad de pesos en la red
//! \return
//!
int RedNeuronal::cantidadPesos()
{
    int suma = 0;
    for( int i=0; i<cantidadCapas(); i++ ) {
        suma+=capas[i]->cantidadPesos();
    }
    return suma;
}

/*!
 * \brief RedNeuronal::setearPesos
 * Setea los pesos de la red por copia
 */
void RedNeuronal::setearPesos(QVector<double> pesos)
{
    int inicio = 0;
    int cant;

    for( int i=0; i<capas.size(); i++ ) {
        cant = capas.at(i)->cantidadPesos();

        QVector<double> pesos_aux;

        //Copio
        for(int j = 0; j<cant; j++) {
            pesos_aux.append(pesos.at(inicio + j));
        }

        inicio += (capas.at(i)->cantidadPesos() - 1);

        capas.at(i)->setearPesos(pesos_aux);
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
    if( salidas.size() == 1 ) {
        if( salidas.at(0) > 0.0 ) {
            return 1;
        } else {
            return -1;
        }
    }

    /*if( salidas.size() == 2 ) {
        if( salidas.at(0) > salidas.at(1) ) {
            return -1;
        } else {
            return 1;
        }
    }*/

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




