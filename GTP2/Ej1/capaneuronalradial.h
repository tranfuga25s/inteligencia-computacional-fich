#ifndef CAPANEURONALRADIAL_H
#define CAPANEURONALRADIAL_H

#include "neuronaradial.h"

class CapaNeuronalRadial
{
public:
    CapaNeuronalRadial( int cantidad_neuronas, int cantidad_entradas );

    void setearTasaAprendizaje( double tasa );
    void setearMomento( double momento );

    QVector<double> getSalidas( QPointF entrada );

private:
    QVector<NeuronaRadial> *_neuronas;
};

#endif // CAPANEURONALRADIAL_H
