#ifndef ENJAMBRE_H
#define ENJAMBRE_H

#include <QVector>
#include "particula.h"

class enjambre
{
public:
    enjambre(double num_part,double x_min,double x_max,double tolerancia,int opc);
    int optimizar();
    double evaluarFuncion(double posicion);
    double devuelvePosicionMinimoGlobal() {return _mejor_y.last();}
    double devuelveValorMinimoGlobal() {return evaluarFuncion(_mejor_y.last());}
    int devuelveCantidadParticulas() {return _enjambre.size();}
private:
    QVector<Particula> _enjambre;
    QVector<double> _mejor_y;//Necesito guardar para poder calcular el error
    double _tolerancia;
    double _X_max,_X_min;

    //Para poder optar por las funciones
    int _opc;
};

#endif // ENJAMBRE_H
