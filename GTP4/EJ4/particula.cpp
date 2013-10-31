#include "particula.h"
#include "funciones_aux.h"

Particula::Particula()
{
}

void Particula::inicializar(double min, double max)
{
    //Posicion de a particula inicial
    _posicion = valor_random(min,max);
    //Mejor posicion inicial (Otro random para poder comparar)
    _mejor_posicion = valor_random(min,max);
    //Velocidad inicial
    _velocidad = 0.0;//???
}

