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

    void setearDatosOriginales( QVector<QPointF> *entradas, QVector<int> *clases );

    void buscarCentroides();
    void entrenarCapaNeuronalComun();

    void setearCodificacion( QVector<int> vector ) { _capaNeuronas->setearCodificacion( vector ); }
    QVector<int> mostrarCodificacionSalida() { _capaNeuronas->getCodificacionSalidas(); }

    int probarPatron( QPointF patron );

private:
    CapaNeuronal *_capaNeuronas;
    CapaNeuronalRadial *_capaRadial;

    int _cantidad_clases; // K

    QVector<QPointF> *_datos_originales; // Guarda la posicion y la clase a la que pertenece en el momento
    QVector<int> *_clases_originales;
};

#endif // REDNEURONALRADIAL_H
