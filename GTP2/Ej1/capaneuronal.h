#ifndef CAPANEURONAL_H
#define CAPANEURONAL_H

#include <QObject>
#include "neurona.h"
#include "funciones_aux.h"

class CapaNeuronal
{
public:
    explicit CapaNeuronal( int cant_neuronas = 0, int cant_entradas = 0 );
    int cantidadNeuronas() { return neuronas.size(); }

    void setearTasaAprendizaje( double tasa );
    void setearMomento ( double momento );
    void inicializarPesos();

    void evaluar( vector entradas );
    int evaluarCodificado( vector entradas );
    void entrenar( vector entradas, int clase );

    vector getSalidas();

    void corregirPesos( vector entradas );

    void corregirDeltas( int num_nueronas, double error );
    double getDeltas( int num_neurona );

    void setearCodificacion( QVector<int> codif );
    QVector<int> getCodificacionSalidas() { return codif_salidas; }
    int mapeadorSalidas( vector salidas );
    vector mapeadorInverso(double valor );

    QVector<Neurona *> getNeuronas() { return neuronas; }
    
private:
    QVector<Neurona *> neuronas;
    QVector<int> codif_salidas;

    
};

#endif // CAPANEURONAL_H
