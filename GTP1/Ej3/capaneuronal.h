#ifndef CAPANEURONAL_H
#define CAPANEURONAL_H

#include <QObject>
#include "neurona.h"
#include "funciones_aux.h"

class CapaNeuronal : public QObject
{
    Q_OBJECT
public:
    CapaNeuronal( int cant_neuronas, int cant_entradas ,QObject *parent = 0);
    void setearCantidadNeuronas( int cantidad ) { _cantidad_neuronas = cantidad; }
    int cantidadNeuronas() { return _cantidad_neuronas; }

    void setearTasaAprendizaje( double tasa );

    void entrenar( vector entradas );

    vector getSalidas();

    vector backPropagation( vector error );
    vector getDeltas();
    
private:
    int _cantidad_neuronas;
    QVector<Neurona> neuronas;

    
};

#endif // CAPANEURONAL_H
