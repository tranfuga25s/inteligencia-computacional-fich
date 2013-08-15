#include "neurona.h"
#include "funciones_aux.h"

Neurona::Neurona(QObject *parent, int cantidad_entradas ) :
QObject(parent)
{
    _tasa_aprendizaje = 0.25;
    _cantidad_entradas = cantidad_entradas;
    // Inicializo el vector de pesos
    for( int i = 0; i<_cantidad_entradas; i++ ) {
        _pesos.push_back( valor_random( -0.5, 0.5 ) );
    }
}

void Neurona::setearTasaAprendizaje(double tasa)
{
    if( tasa > 0.0 ) {
        this->_tasa_aprendizaje = tasa;
    }
}

double Neurona::tasaAprendizaje()
{ return _tasa_aprendizaje; }

int Neurona::cantidadEntradas()
{ return _cantidad_entradas; }
