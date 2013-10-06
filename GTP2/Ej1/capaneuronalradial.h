#ifndef CAPANEURONALRADIAL_H
#define CAPANEURONALRADIAL_H

#include "neuronaradial.h"
#include "graficadormdi.h"

class CapaNeuronalRadial
{
public:
    CapaNeuronalRadial( int cantidad_neuronas, int cantidad_entradas, int cantidad_clases );

    void setearTasaAprendizaje( double tasa );
    void setearMomento( double momento );
    void setearCantidadClases( int valor ) { _cantidad_clases = valor; }

    QVector<double> getSalidas(vector entrada );

    void buscarCentroides( QVector<vector> &_datos_originales );

    void graficarClusters( GraficadorMdi *graf );

private:
    QVector<NeuronaRadial> *_neuronas;
    QVector< QList<vector> > *_patrones_clase;

    int _cantidad_clases;
};

#endif // CAPANEURONALRADIAL_H
