#include "capaneuronal.h"
#include "neurona.h"

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

vector CapaNeuronal::getSalidas()
{
    vector temp;
    for( int n=0; n<neuronas.size(); n++ ) {
        temp.append( neuronas[n]->getSalida() );
    }
    return temp;
}
///*!
// * \brief CapaNeuronal::getDeltas
// * Devuelve la sumatoria de los deltas de todas las neuronas de la capa por el peso de la neurona pasada como parametro
// *\param num_neurona
// * \return
// */

//double CapaNeuronal::getDeltas(int num_neurona)
//{
//    double sumatoria = 0.0;

//    for (int j = 0 ; j < neuronas.size(); j++ ) {
//        double delta_anterior = neuronas[j]->getDelta();
//        double peso = neuronas[j]->devuelvePesos()[num_neurona];
//        double delta = delta_anterior*peso;
//        sumatoria += delta;
//    }
//    return sumatoria;

//}

///*!
// * \brief CapaNeuronal::corregirPesos
// * Esta seria la funcion que ajusta los pesos de las neuronas en la capa
// */

//void CapaNeuronal::corregirPesos(vector entradas)
//{
//    for (int i = 0 ; i < neuronas.size() ; i++) {
//        neuronas[i]->ajustarPesos(entradas);
//        neuronas[i]->setDelta( 0.0 );
//    }
//}

///*!
// * \brief CapaNeuronal::corregirDeltas
// * Esto seria la parte del backpropagation en donde se corrigen los deltas de cada neurona de la capa
// * \param error
// * \return
// */
//void CapaNeuronal::corregirDeltas( int num_neurona, double error )//sumatoria = error
//{
//    double salida = neuronas[num_neurona]->getSalida();
//    double derivada = Neurona::funcionActivacionDerivada( salida );
//    double nuevo_delta =  derivada * error;

//    neuronas[num_neurona]->setDelta( nuevo_delta );
//}



