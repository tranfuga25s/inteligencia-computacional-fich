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
    void setearPesos(QVector<double> pesos);
    int cantidadPesos () {return neuronas.size() * neuronas.at(0)->cantidadPesos();} //Devuelve la cantidad de pesos de la capa

    void evaluar( vector entradas );

    vector getSalidas();

//    void corregirPesos( vector entradas );

//    void corregirDeltas( int num_nueronas, double error );
//    double getDeltas( int num_neurona );

    QVector<Neurona *> getNeuronas() { return neuronas; }
    
private:
    QVector<Neurona *> neuronas;

    
};

#endif // CAPANEURONAL_H
