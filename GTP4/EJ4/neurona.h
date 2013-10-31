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

//    void setearMomento( double momento ) { _momento = momento; }
//    double tasaMomento() { return _momento; }

    int cantidadPesos() {return _pesos.size();}

    int cantidadEntradas() { return _cantidad_entradas; }

    double evaluar(QVector<double> entradas);
//    void ajustarPesos( QVector<double> entradas );

    // Entre -1 y 1
    double funcionActivacion( double valor ) { return ( 2.0 / ( 1.0 + exp( -1.0 * valor) ) ) - 1.0; }
    static double funcionActivacionDerivada( double valor ) { return ( 1.0 + valor ) * ( 1.0 - valor ) * 0.5; }

    Neurona& operator = (Neurona const &neurona) {
        _cantidad_entradas = neurona._cantidad_entradas;
        _tasa_aprendizaje = neurona._tasa_aprendizaje;
        _pesos = neurona._pesos;
        _ultima_salida = neurona._ultima_salida;
        return *this;
    }

    // Funcion de activacion entre 0 y 1
    /*static double funcionActivacion( double valor ) { return ( 1.0 / ( 1.0 + exp( -1.0 * valor ) ) ); }
    static double funcionActivacionDerivada( double valor ) { return valor * ( 1.0 - valor ); }*/

    double getSalida() { return _ultima_salida; }
//    double getDelta() { return _delta; }
//    void setDelta( double delta ) { _delta = delta; }

private:
    int _cantidad_entradas;
    double _tasa_aprendizaje;
    //double _momento;
    QVector<double> _pesos;
    //QVector<double> _var_pesos_ant;
    double _ultima_salida;
    //double _delta;
    
};

#endif // NEURONA_H
