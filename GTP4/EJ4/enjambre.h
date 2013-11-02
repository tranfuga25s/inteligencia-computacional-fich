#ifndef ENJAMBRE_H
#define ENJAMBRE_H

#include <QVector>
#include "particula.h"
#include "redneuronal.h"

class enjambre
{
public:
    enjambre(double num_part, double x_min, double x_max, double tolerancia,int max_iteraciones,RedNeuronal *red,matriz entradas,vector salidas);
    bool optimizar();
    double evaluarFuncion(QVector<double> pesos);
    QVector<double> devuelveMejoresPesos() {return _mejores_pesos_globales.last();}
    double cantidadErroresEnMinimo() {return evaluarFuncion(_mejores_pesos_globales.last());}
private:
    QVector<Particula> _enjambre;//Enjambre de particulas con posiciones como pesos
    QVector< QVector<double> > _mejores_pesos_globales;//Vector de vectores historicos de mejores posiciones (Pesos)
    double _tolerancia;
    int _max_iter;
    double _X_max,_X_min;

    RedNeuronal *_redpso;
    vector _salidas;
    matriz _entradas;

};

#endif // ENJAMBRE_H
