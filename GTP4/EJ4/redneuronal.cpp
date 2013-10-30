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

/*!
 * \brief RedNeuronal::setearPesos
 * Setea los pesos de la red por copia
 */
void RedNeuronal::setearPesos(QVector<double> pesos)
{
    for( int i=0; i<capas.size(); i++ ) {
        //Sera indistinto el a que neurona le asigno a cada peso???
        int cant_a_borrar = capas.at(i)->cantidadPesos();
        QVector<double> pesos_aux;

        //Copio
        for(int j = 0; j<cant_a_borrar; j++) {
            pesos_aux.append(pesos.at(i));
        }

        //Elimino
        for(int j = 0; j<cant_a_borrar; j++) {
            pesos.remove(i);
        }

        capas[i]->setearPesos(pesos_aux);
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

///*!
// * \brief RedNeuronal::backwardPass
// * Metodo para hacer la correccion de los deltas para todas las capas y corregir los pesos
// * \param entradas
// * \param salidas
// */
//void RedNeuronal::backwardPass( vector entradas, double salida_deseada )
//{
//    vector salida = forwardPass( entradas );

//    vector salida_deseada_vector = mapeadorInverso( salida_deseada );

//    // CORRECCION DELTAS ULTIMA CAPA
//    for( int i=0; i<salida_deseada_vector.size(); i++ ) {

//        double error = salida_deseada_vector.at( i ) - salida.at( i );
//        double derivada = Neurona::funcionActivacionDerivada( salida.at(i) );
//        double delta = error * derivada;
//        capas[capas.size()-1]->getNeuronas()[i]->setDelta( delta );

//    }

//    // CORRECCION DELTAS RESTANTES CAPAS
//    //Recorro desde la penultima capa hasta la primera
//    for( int c = capas.size()-2 ; c >= 0 ; c-- ) {
//        //Recorro todas las neuronas de la capa
//        for (int n = 0 ; n < capas[c]->cantidadNeuronas() ; n++ ) {

//            capas[c]->corregirDeltas( n, capas[c+1]->getDeltas(n) );
//        }

//    }
//    //UNA VEZ QUE CORREGI LOS DELTAS DE LA RED CORRIJO LOS PESOS
//    capas[0]->corregirPesos( entradas );
//    for( int c=1; c<capas.size(); c++ ) {
//        capas[c]->corregirPesos( capas[c-1]->getSalidas() );
//        //qDebug() << capas[c]->getNeuronas()[0]->devuelvePesos();
//    }
//    return;

//}

///*!
// * \brief RedNeuronal::entrenamiento
// * \param entradas
// * \param salidas
// */
//void RedNeuronal::entrenamiento( vector entradas, double salidas )
//{
//    forwardPass( entradas );
//    backwardPass( entradas , salidas );
//}

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

/*!
 * \brief RedNeuronal::mapeadorInverso
 * \param valor
 * \return
 */
vector RedNeuronal::mapeadorInverso( double valor )
{
    vector retorno;
    if( codif_salidas.size() == 1 ) {
        retorno.append( valor );
        return retorno;
    }
    // Los valores que tiene que contener los vectores de
    // comparación para las neuronas tienen que ser acordes a la funcion
    // de activación que se esté uilizando
    for( int i=0; i<codif_salidas.size(); i++ ) {
        if( valor == codif_salidas.at( i ) ) {
            retorno.insert( i, 1.0  );
        } else {
            retorno.insert( i, -1.0 );
        }
    }
    return retorno;
}

void RedNeuronal::mostrarPesos( QTextStream &pesos )
{
//    for (int c = 0 ; c < capas.size() ; c++) {
//        for (int n = 0 ; n < capas[c]->getNeuronas().size() ; n++) {
//            for (int p = 0 ; p < capas[c]->getNeuronas()[n]->devuelvePesos().size() ; p++ ) {
//                qDebug() << c << n << p << capas[c]->getNeuronas()[n]->devuelvePesos().at(p);
//            }
//        }
//    }
    pesos <<
     capas[0]->getNeuronas()[0]->devuelvePesos().at(0) << ", " <<
     capas[0]->getNeuronas()[0]->devuelvePesos().at(1) << ", " <<
     capas[0]->getNeuronas()[0]->devuelvePesos().at(2) << ", " <<
     capas[0]->getNeuronas()[1]->devuelvePesos().at(0) << ", " <<
     capas[0]->getNeuronas()[1]->devuelvePesos().at(1) << ", " <<
     capas[0]->getNeuronas()[1]->devuelvePesos().at(2) << ", " <<
     capas[1]->getNeuronas()[0]->devuelvePesos().at(0) << ", " <<
     capas[1]->getNeuronas()[0]->devuelvePesos().at(1) << ", " <<
     capas[1]->getNeuronas()[0]->devuelvePesos().at(2) << "\n";
}
