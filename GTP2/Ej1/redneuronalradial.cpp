#include "redneuronalradial.h"

RedNeuronalRadial::RedNeuronalRadial( int cantidad_neuronas_radiales, int cantidad_neuronas_normales, int cantidad_entradas )
{
    if( cantidad_neuronas_radiales != 0 ) {
        _capaRadial = new CapaNeuronalRadial( cantidad_neuronas_radiales, cantidad_entradas );
    }
    if( cantidad_neuronas_normales != 0 ) {
        _capaNeuronas = new CapaNeuronal( cantidad_neuronas_normales, cantidad_neuronas_radiales );
    }
}

void RedNeuronalRadial::setearTasaAprendizaje( double tasa )
{
    _capaNeuronas->setearTasaAprendizaje( tasa );
    _capaRadial->setearTasaAprendizaje( tasa );
}

void RedNeuronalRadial::setearMomento(double momento)
{
    _capaNeuronas->setearMomento( momento );
    _capaRadial->setearMomento( momento );
}
