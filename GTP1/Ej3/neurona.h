#ifndef NEURONA_H
#define NEURONA_H

#include "funciones_aux.h"
#include <QObject>
#include <QVector>

class Neurona
{

public:


    Neurona( int cantidadEntradas = 1 );

    void inicializarPesos();
    QVector<double> devuelvePesos();
    void seteaPesos(QVector<double> pesos);

    void setearTasaAprendizaje( double tasa ) { _tasa_aprendizaje = tasa; }
    double tasaAprendizaje() { return _tasa_aprendizaje; }

    void setearMomento( double momento ) { _momento = momento; }
    double tasaAprendizaje() { return _momento; }


    int cantidadEntradas() { return _cantidad_entradas; }

    double evaluar(QVector<double> entradas);
    void ajustarPesos( QVector<double> entradas );

    double funcionActivacion( double valor ){return ( 2 / ( 1 + exp( -1 * valor) ) - 1 );} //faltaria el valor de b?

    double getSalida() { return _ultima_salida; }
    double getDelta() { return _delta; }
    void setDelta( double delta ) { _delta = delta; }


private:
    int _cantidad_entradas;
    double _tasa_aprendizaje;
    double _momento;
    QVector<double> _pesos;
    QVector<double> _var_pesos_ant;
    double _ultima_salida;
    double _delta;
    
};

#endif // NEURONA_H
