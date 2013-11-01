#ifndef PARTICULA_H
#define PARTICULA_H

#include "funciones_aux.h"

class Particula
{
public:
    Particula();
    void inicializar(double min,double max,int tam);
    QVector<double> devolverPesos() {return _pesos;}
    QVector<double> devolverMejoresPesos() {return _mejores_pesos;}
    void setPesos(double peso,int pos) {_pesos[pos] = peso;}
    void setMejoresPesos(QVector<double> pesos) {_mejores_pesos = pesos;}
    void setearVelocidad(double velocidad,int j) {_velocidad[j] = velocidad;}
    QVector<double> devolverVelocidad() {return _velocidad;}
    double cantPesos() {return _pesos.size();}

private:
    QVector<double> _pesos;
    QVector<double> _mejores_pesos;
    QVector<double> _velocidad;
};

#endif // PARTICULA_H
