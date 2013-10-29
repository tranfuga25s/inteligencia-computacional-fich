#ifndef ENJAMBRE_H
#define ENJAMBRE_H

#include <QVector>
#include "particula.h"

class enjambre
{
public:
    enjambre(double num_part,double x_min,double x_max,double tolerancia);
    void optimizar(int opc);
    double evaluarFuncion(double posicion,int opc);
    QVector<Particula> devuelveEnjambre() {return _enjambre;}
private:
    QVector<Particula> _enjambre;
    QVector<double> _mejor_y;//Necesito guardar para poder calcular el error
    double _tolerancia;
};

#endif // ENJAMBRE_H
