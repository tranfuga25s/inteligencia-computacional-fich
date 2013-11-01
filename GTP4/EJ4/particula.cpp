#include "particula.h"
#include "funciones_aux.h"

Particula::Particula()
{
}

void Particula::inicializar(double min, double max, int tam)
{
    //Posicion de a particula inicial
    for (int i = 0 ; i < tam ; i++) {
        _pesos.append(valor_random(min,max));
        //Mejor posicion inicial (Otro random para poder comparar)
        _mejores_pesos.append(valor_random(min,max));
        //Velocidad inicial
        _velocidad.append(0.0);//???
    }

}

