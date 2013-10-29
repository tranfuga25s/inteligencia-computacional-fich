#include "poblacion.h"

template<typename T> Poblacion<T>::Poblacion() :
    QVector<T>()
{
    _elitismo = false;
    _cantidad_total = 0.0;
    _metodo_seleccion = Ruleta;
}

void Poblacion::evaluar()
{
}

double Poblacion::mejorIndividuo() const
{
}