#ifndef ENJAMBRE_H
#define ENJAMBRE_H

#include <QVector>
#include "particula.h"

class enjambre
{
public:
    enjambre(double num_part,double x_min,double x_max,double tolerancia);
    int optimizar();
    double evaluarFuncion(double posicion);
    double devuelvePosicionMinimoGlobal() {return _mejor_y.last();}
    double devuelveValorMinimoGlobal() {return evaluarFuncion(_mejor_y.last());}
private:
    QVector<Particula> _enjambre;
    QVector<double> _mejor_y;//Necesito guardar para poder calcular el error
    double _tolerancia;
    double _X_max,_X_min;

};

#endif // ENJAMBRE_H
