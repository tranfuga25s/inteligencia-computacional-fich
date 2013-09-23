#ifndef CAPANEURONALRADIAL_H
#define CAPANEURONALRADIAL_H

#include "neuronaradial.h"

class CapaNeuronalRadial
{
public:
    CapaNeuronalRadial( int cantidad_neuronas, int cantidad_entradas );

    void setearTasaAprendizaje( double tasa );
    void setearMomento( double momento );
    void setearCantidadClases( int valor ) { _cantidad_clases = valor; }

    QVector<double> getSalidas( QPointF entrada );

    void buscarCentroides( QVector<QPointF> _datos_originales );

private:
    QVector<NeuronaRadial> *_neuronas;
    QVector< QList<QPointF> > *_patrones_clase;

    int _cantidad_clases;
};

#endif // CAPANEURONALRADIAL_H
