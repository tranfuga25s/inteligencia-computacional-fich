#include "capaneuronal.h"
#include "neurona.h"

CapaNeuronal::CapaNeuronal(int cant_neuronas, int cant_entradas )
{
    //qDebug() << "Nueva capa neuronal";
    //neuronas.resize(cant_neuronas);
    if( cant_neuronas != 0 ) {
        for (int i = 0 ; i < cant_neuronas ; i++ ){
            neuronas.append( new Neurona( cant_entradas ) );
        }
    }
}

void CapaNeuronal::setearTasaAprendizaje( double tasa )
{
    for( int i=0; i<cantidadNeuronas(); i++ ) {
        neuronas[i]->setearTasaAprendizaje( tasa );
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

//!
//! \brief CapaNeuronal::cantidadPesos
//! Retorna la cantidad de pesos de la capa
//! \return
//!

int CapaNeuronal::cantidadPesos()
{
    int suma = 0;
    for( int i=0; i<neuronas.size(); i++ ) {
        suma+=neuronas.at(i)->cantidadPesos();
    }
    return suma;
}

/*!
 * \brief CapaNeuronal::setearPesos
 * Setea los pesos por copia
 *\param pesos
 */

void CapaNeuronal::setearPesos(QVector<double> pesos)
{
    int inicio = 0;
    int cant;

    for( int i=0; i<neuronas.size(); i++ ) {
        cant = neuronas.at(i)->cantidadPesos();

        QVector<double> pesos_aux;

        //Copio
        for(int j = 0; j<cant; j++) {
            pesos_aux.append(pesos.at(inicio + j));
        }

        inicio += (neuronas.at(i)->cantidadPesos()-1);

        neuronas.at(i)->seteaPesos(pesos_aux);
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


