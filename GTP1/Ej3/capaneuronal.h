#ifndef CAPANEURONAL_H
#define CAPANEURONAL_H

#include <QObject>
#include "neurona.h"
#include "funciones_aux.h"

class CapaNeuronal
{
public:
    CapaNeuronal( int cant_neuronas = 1, int cant_entradas = 1 );
    void setearCantidadNeuronas( int cantidad ) { _cantidad_neuronas = cantidad; }
    int cantidadNeuronas() { return _cantidad_neuronas; }

    void setearTasaAprendizaje( double tasa );
    void setearMomento ( double momento );
    void inicializarPesos();

    void evaluar( vector entradas );

    vector getSalidas();

    void corregirPesos(vector entradas);

    void corregirDeltas(int num_nueronas, double error );
    double getDeltas(int num_neurona);

    QVector<Neurona> getNeuronas(){ return neuronas; }
    
private:
    int _cantidad_neuronas;
    QVector<Neurona> neuronas;

    
};

#endif // CAPANEURONAL_H
