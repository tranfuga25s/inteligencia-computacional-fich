#ifndef CAPANEURONALRADIAL_H
#define CAPANEURONALRADIAL_H

#include "neuronaradial.h"

class CapaNeuronalRadial
{
public:
    CapaNeuronalRadial();

private:
    QVector<NeuronaRadial> *_neuronas;
};

#endif // CAPANEURONALRADIAL_H
