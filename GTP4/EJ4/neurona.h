#ifndef NEURONA_H
#define NEURONA_H

#include "funciones_aux.h"
#include <QObject>
#include <QVector>

class Neurona
{

public:


    Neurona( int cantidadEntradas = 0);

    void inicializarPesos();
    QVector<double> devuelvePesos();
    void seteaPesos(QVector<double> pesos);

    void setearTasaAprendizaje( double tasa ) { _tasa_aprendizaje = tasa; }
    double tasaAprendizaje() { return _tasa_aprendizaje; }

    int cantidadPesos() {return _pesos.size();}

    int cantidadEntradas() { return _cantidad_entradas; }

    double evaluar(QVector<double> entradas);

    // Entre -1 y 1
    double funcionActivacion( double valor ) { return ( 2.0 / ( 1.0 + exp( -1.0 * valor) ) ) - 1.0; }
    static double funcionActivacionDerivada( double valor ) { return ( 1.0 + valor ) * ( 1.0 - valor ) * 0.5; }

    double getSalida() { return _ultima_salida; }

private:
    int _cantidad_entradas;
    double _tasa_aprendizaje;
    QVector<double> _pesos;
    double _ultima_salida;
    
};

#endif // NEURONA_H
