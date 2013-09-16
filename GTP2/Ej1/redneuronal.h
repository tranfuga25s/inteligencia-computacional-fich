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
    int cantidadCapas() { return capas.size(); }

    void setearTasaAprendizaje( double tasa );
    void setearMomento(double momento);
    double getMomento() { return capas[0]->getNeuronas()[0]->tasaMomento(); }

    void inicializarPesos();

    vector forwardPass( vector entradas );//forward pass
    void backwardPass(vector entradas, double salida );//backward pass

    void entrenamiento(vector entradas, double salidas );

    void setearCodificacion( QVector<int> codif );
    QVector<int> mostrarCodificacionSalida() { return codif_salidas; }

    int mapeadorSalidas( vector salidas );
    vector mapeadorInverso(double valor );

    void mostrarPesos( QTextStream &pesos );
    
private:
    QVector<CapaNeuronal *> capas;
    QVector<int> codif_salidas;
    
};

#endif // REDNEURONAL_H
