#ifndef REDNEURONALRADIAL_H
#define REDNEURONALRADIAL_H

#include "capaneuronal.h"
#include "capaneuronalradial.h"

class RedNeuronalRadial
{
public:
    RedNeuronalRadial( int cantidad_neuronas_radiales, int cantidad_neuronas_normales, int cantidad_entradas, int cant_clases );

    int cantidadCapas() { return 2; }

    void setearTasaAprendizaje( double tasa );
    void setearMomento(double momento);
    double getMomento() { return _capaNeuronas->getNeuronas()[0]->tasaMomento(); }

    void setearDatosOriginales( matriz entradas, QVector<int> *clases );

    void buscarCentroides();
    void entrenarCapaNeuronalComun( QVector<double> entrada, int clase );

    void setearCodificacion( QVector<int> vector ) { _capaNeuronas->setearCodificacion( vector ); }
    QVector<int> mostrarCodificacionSalida() { return _capaNeuronas->getCodificacionSalidas(); }

    int probarPatron( vector patron );
    int mapeadorSalidas(vector salidas);

    void inicializarPesos() { _capaNeuronas->inicializarPesos(); }

    void graficarClusters( GraficadorMdi *graf );


private:
    CapaNeuronal *_capaNeuronas;
    CapaNeuronalRadial *_capaRadial;

    int _cantidad_clases; // K

    QVector<vector> *_datos_originales; // Guarda la posicion y la clase a la que pertenece en el momento
    QVector<int> *_clases_originales;

};

#endif // REDNEURONALRADIAL_H
