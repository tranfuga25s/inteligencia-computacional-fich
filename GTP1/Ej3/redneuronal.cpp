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
        _cantidad_capas = cantidad_capas;
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
 * \brief RedNeuronal::setearMomento
 * \param momento
 */
void RedNeuronal::setearMomento(double momento)
{
    for( int i=0; i<_cantidad_capas; i++ ) {
        capas[i].setearMomento( momento );
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

/*!
 * \brief RedNeuronal::forwardPass
 * \param entradas
 * \return
 */
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

    int sal_codif = mapeadorSalidas(salida);
    double error = 0.0;

    // Tanto la salida codificada como la salida deseada están codificadas
    // El vector de la salida deseada tiene un solo elemento
    if( salida_deseada.size() == 1 ) {
        if( sal_codif != salida_deseada.at(0) ) {
            vector salida_deseada_vector = mapeadorInverso( salida_deseada.at( 0 ) );

            for( int i=0; i<salida_deseada_vector.size(); i++ ) {

                error = salida_deseada_vector.at( i ) - salida.at( i );

                capas[capas.size()-1].getNeuronas()[i].setDelta( error * capas[capas.size()-1].getNeuronas()[i].getSalida()) ;
            }

        }

    } else {
        /// @TODO ver en caso de que el tamaño de las salidas sean mas grandes
    }

    for( int c=capas.size()-2; c>=0; c-- ) {
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

/*!
 * \brief RedNeuronal::entrenamiento
 * \param entradas
 * \param salidas
 */
void RedNeuronal::entrenamiento(vector entradas, vector salidas)
{
    forwardPass( entradas );
    backwardPass( entradas , salidas );
}

/*!
 * \brief RedNeuronal::setearCodificacion
 * \param codif
 */
void RedNeuronal::setearCodificacion(QVector<int> codif)
{
    for (int i = 0 ; i < codif.size() ; i++) {
        codif_salidas.push_back(codif.at(i));
    }
}

/*!
 * \brief RedNeuronal::mapeadorSalidas
 * \param salidas
 * \return
 */
int RedNeuronal::mapeadorSalidas(vector salidas)
{
    int max = 0;
    int mayor;

    if (salidas.size() == 1) {return salidas.at(0);}

    for(int i = 0 ; i < salidas.size() ; i++) {
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
    for( int i=0; i<codif_salidas.size(); i++ ) {
        if( valor == codif_salidas.at( i ) ) {
            retorno.insert( i, 1 );
        } else {
            retorno.insert( i, 0 );
        }
    }
    return retorno;
}
