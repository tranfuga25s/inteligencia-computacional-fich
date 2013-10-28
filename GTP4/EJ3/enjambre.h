#ifndef ENJAMBRE_H
#define ENJAMBRE_H

#include <QVector>
#include "particula.h"

class enjambre
{
public:
    enjambre(double num_part,double x_min,double x_max,double tolerancia);
    void optimizar();
    double evaluarFuncion(double posicion);
    QVector<Particula> devuelveEnjambre() {return _enjambre;}
private:
    QVector<Particula> _enjambre;
    double _mejor_y;
    double _tolerancia;
};

#endif // ENJAMBRE_H
