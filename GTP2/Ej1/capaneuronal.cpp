#include "capaneuronal.h"
#include "neurona.h"
#include <cfloat>

CapaNeuronal::CapaNeuronal(int cant_neuronas, int cant_entradas )
{
    //qDebug() << "Nueva capa neuronal";
    if( cant_neuronas != 0 ) {
        for (int i = 0 ; i < cant_neuronas ; i++ ){
            neuronas.append( new Neurona( cant_entradas ) );
        }
    }
}

void CapaNeuronal::setearTasaAprendizaje( double tasa )
{
    for( int i=0; i<neuronas.size(); i++ ) {
        neuronas[i]->setearTasaAprendizaje( tasa );
    }
}

void CapaNeuronal::setearMomento(double momento)
{
    for( int i=0; i<neuronas.size(); i++ ) {
        neuronas[i]->setearMomento( momento );
    }
}

/*!
 * \brief CapaNeuronal::inicializarPesos
 */

void CapaNeuronal::inicializarPesos()
{
    for( int i=0; i<neuronas.size(); i++ ) {
        neuronas[i]->inicializarPesos();
    }
}

void CapaNeuronal::evaluar( vector entradas )
{
    for( int n=0; n<neuronas.size(); n++ ) {
        neuronas[n]->evaluar( entradas );
    }
}

int CapaNeuronal::evaluarCodificado(vector entradas)
{
    vector temporal;
    for( int n=0; n<neuronas.size(); n++ ) {
        temporal.append( neuronas[n]->evaluar( entradas ) );
    }
    return mapeadorSalidas( temporal );
}

void CapaNeuronal::entrenar( vector entradas, int clase )
{

    // corrijo los errores
    vector vector_deseado = this->mapeadorInverso( clase );

    for( int i=0; i<neuronas.size(); i++ ) {
        neuronas[i]->entrenamiento( entradas, vector_deseado.at( i ) );
    }

}

vector CapaNeuronal::getSalidas()
{
    vector temp;
    for( int n=0; n<neuronas.size(); n++ ) {
        temp.append( neuronas[n]->getSalida() );
    }
    return temp;
}

/*!
 * \brief CapaNeuronal::getDeltas
 * Devuelve la sumatoria de los deltas de todas las neuronas de la capa por el peso de la neurona pasada como parametro
 *\param num_neurona
 * \return
 */
double CapaNeuronal::getDeltas(int num_neurona)
{
    double sumatoria = 0.0;

    for (int j = 0 ; j < neuronas.size(); j++ ) {
        double delta_anterior = neuronas[j]->getDelta();
        double peso = neuronas[j]->devuelvePesos()[num_neurona];
        double delta = delta_anterior*peso;
        sumatoria += delta;
    }
    return sumatoria;

}

/*!
 * \brief CapaNeuronal::corregirPesos
 * Esta seria la funcion que ajusta los pesos de las neuronas en la capa
 */

void CapaNeuronal::corregirPesos(vector entradas)
{
    for (int i = 0 ; i < neuronas.size() ; i++) {
        neuronas[i]->ajustarPesos(entradas);
        neuronas[i]->setDelta( 0.0 );
    }
}

/*!
 * \brief CapaNeuronal::corregirDeltas
 * Esto seria la parte del backpropagation en donde se corrigen los deltas de cada neurona de la capa
 * \param error
 * \return
 */
void CapaNeuronal::corregirDeltas( int num_neurona, double error )//sumatoria = error
{
    double salida = neuronas[num_neurona]->getSalida();
    double derivada = Neurona::funcionActivacionDerivada( salida );
    double nuevo_delta =  derivada * error;

    neuronas[num_neurona]->setDelta( nuevo_delta );
}

/*!
 * \brief RedNeuronal::setearCodificacion
 * \param codif
 */
void CapaNeuronal::setearCodificacion( QVector<int> codif )
{ codif_salidas = codif; }

/*!
 * \brief RedNeuronal::mapeadorSalidas
 * \param salidas
 * \return
 */
int CapaNeuronal::mapeadorSalidas(vector salidas)
{
    //Esto es el caso de que haya una sola neurona en la ultima capa
    if( salidas.size() == 1 ) {
        if( salidas.at(0) > 0.0 ) {
            return 1;
        } else {
            return -1;
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

    return codif_salidas.at( mayor );

}

/*!
 * \brief RedNeuronal::mapeadorInverso
 * \param valor
 * \return
 */
vector CapaNeuronal::mapeadorInverso( double valor )
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

