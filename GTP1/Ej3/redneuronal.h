#ifndef REDNEURONAL_H
#define REDNEURONAL_H

#include <QObject>
#include <capaneuronal.h>
#include "funciones_aux.h"

class RedNeuronal : public QObject
{
    Q_OBJECT
public:
    RedNeuronal( int cant_capas, QVector<int> cantidad_neuronas, int cant_entradas, QObject *parent = 0);
    void setearCantidadCapas( int cantidad ) { _cantidad_capas = cantidad; }
    int cantidadCapas() { return _cantidad_capas; }

    void setearTasaAprendizaje( double tasa );
    void setearMomento(double momento);

    void inicializarPesos();

    vector forwardPass( vector entradas );//forward pass
    void backwardPass( vector entradas, vector salidas );//backward pass

    void entrenamiento( vector entradas, vector salidas );
    
private:
    QVector<CapaNeuronal> capas;
    int _cantidad_capas;
    
};

#endif // REDNEURONAL_H
