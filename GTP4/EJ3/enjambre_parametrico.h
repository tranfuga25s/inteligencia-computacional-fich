#ifndef ENJAMBRE_PARAMETRICO_H
#define ENJAMBRE_PARAMETRICO_H

#include "particula_parametrica.h"

class enjambre_parametrico
{
public:
    enjambre_parametrico(double num_part,double x_min,double x_max,double y_min,double y_max,double tolerancia);
    void optimizar();
    double evaluarFuncion(double posicion_x,double posicion_y);
    QVector<particula_parametrica> devuelveEnjambre() {return _enjambre_par;}

private:
    QVector<particula_parametrica> _enjambre_par;
    QVector<double> _mejor_y_x;//Mejor posicion global en x
    QVector<double> _mejor_y_y;//Mejor posicion global en y
    double _tolerancia;
};

#endif // ENJAMBRE_PARAMETRICO_H
