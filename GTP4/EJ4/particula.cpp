#include "particula.h"
#include "funciones_aux.h"

Particula::Particula()
{
}

void Particula::inicializar(double min, double max)
{
    //Posicion de a particula inicial
    _posicion = valor_random(min,max);
    //Mejor posicion inicial
    _mejor_posicion = _posicion;
    //Velocidad inicial
    _velocidad = 0.0;//???
}

