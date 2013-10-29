#include "particula_parametrica.h"

particula_parametrica::particula_parametrica()
{
}

void particula_parametrica::inicializar(double xmin, double xmax, double ymin, double ymax)
{
    //Posicion de a particula inicial

    //X
    _posicion_x = valor_random(xmin,xmax);
    //Mejor posicion inicial
    _mejor_posicion_x = -1.0;
    //Velocidad inicial
    _velocidad_x = 0.0;//???

    //Y
    _posicion_y = valor_random(ymin,ymax);
    //Mejor posicion inicial
    _mejor_posicion_y = -1.0;
    //Velocidad inicial
    _velocidad_y = 0.0;//???
}
