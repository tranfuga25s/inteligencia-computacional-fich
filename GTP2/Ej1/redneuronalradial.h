#ifndef REDNEURONALRADIAL_H
#define REDNEURONALRADIAL_H

#include "capaneuronal.h"
#include "capaneuronalradial.h"

class RedNeuronalRadial
{
public:
    RedNeuronalRadial( int cantidad_neuronas_radiales, int cantidad_neuronas_normales, int cantidad_entradas );

    int cantidadCapas() { return 2; }

    void setearTasaAprendizaje( double tasa );
    void setearMomento(double momento);
    double getMomento() { return _capaNeuronas->getNeuronas()[0]->tasaMomento(); }

    void inicializarPesos();

    void setearDatosOriginales( QVector<QPointF> entradas, QVector<int> clases );

private:
    CapaNeuronal *_capaNeuronas;
    CapaNeuronalRadial *_capaRadial;

    QPair<int, QPointF> *_datos_originales; // Guarda la posicion y la clase a la que pertenece en el momento

};

#endif // REDNEURONALRADIAL_H
