#ifndef PARTICULA_PARAMETRICA_H
#define PARTICULA_PARAMETRICA_H

#include "funciones_aux.h"

class particula_parametrica
{
public:
    particula_parametrica();
    void inicializar(double minx,double maxx,double miny,double maxy);
    //X
    double devolverPosicionX() {return _posicion_x;}
    double devolverMejorPosicionX() {return _mejor_posicion_x;}
    void setPosicionX(double posicion) {_posicion_x = posicion;}
    void setMejorPosicionX(double posicion) {_mejor_posicion_x = posicion;}
    void setearVelocidadX(double velocidad) {_velocidad_x = velocidad;}
    double devolverVelocidadX() {return _velocidad_x;}
    //Y
    double devolverPosicionY() {return _posicion_y;}
    double devolverMejorPosicionY() {return _mejor_posicion_y;}
    void setPosicionY(double posicion) {_posicion_y = posicion;}
    void setMejorPosicionY(double posicion) {_mejor_posicion_y = posicion;}
    void setearVelocidadY(double velocidad) {_velocidad_y = velocidad;}
    double devolverVelocidadY() {return _velocidad_y;}

private:
    //X
    double _posicion_x;
    double _mejor_posicion_x;
    double _velocidad_x;
    //Y
    double _posicion_y;
    double _mejor_posicion_y;
    double _velocidad_y;
};

#endif // PARTICULA_PARAMETRICA_H
