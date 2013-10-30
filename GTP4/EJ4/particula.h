#ifndef PARTICULA_H
#define PARTICULA_H

#include "funciones_aux.h"

class Particula
{
public:
    Particula();
    void inicializar(double min,double max);
    double devolverPosicion() {return _posicion;}
    double devolverMejorPosicion() {return _mejor_posicion;}
    void setPosicion(double posicion) {_posicion = posicion;}
    void setMejorPosicion(double posicion) {_mejor_posicion = posicion;}
    void setearVelocidad(double velocidad) {_velocidad = velocidad;}
    double devolverVelocidad() {return _velocidad;}

private:
    double _posicion;
    double _mejor_posicion;
    double _velocidad;
};

#endif // PARTICULA_H
