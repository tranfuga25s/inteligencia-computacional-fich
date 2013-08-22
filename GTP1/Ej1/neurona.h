#ifndef NEURONA_H
#define NEURONA_H

#include "funciones_aux.h"
#include <QObject>
#include <QVector>

class Neurona : public QObject
{
    Q_OBJECT
public:

    enum tipoFuncionActivacion {
        signo = 1,
        diagonal = 2,
        sigmoidea = 3
    };

    Neurona( QObject *parent = 0, int cantidadEntradas = 1 );

    void inicializarPesos();
    QVector<double> devuelvePesos();
    void seteaPesos(QVector<double> pesos);

    void setearTasaAprendizaje( double tasa ) { _tasa_aprendizaje = tasa; }
    double tasaAprendizaje() { return _tasa_aprendizaje; }

    int cantidadEntradas() { return _cantidad_entradas; }

    double evaluar(QVector<double> entradas);
    bool entrenamiento( QVector<double> entradas, double salidaDeseada );

    void setearFuncionActivacion( tipoFuncionActivacion tipo, double alfa ) { _tipo_funcion_activacion=tipo; _alfa_activacion=alfa; }
    double funcionActivacion( double valor );


private:
    int _cantidad_entradas;
    double _tasa_aprendizaje;
    double _alfa_activacion;
    QVector<double> _pesos;
    Neurona::tipoFuncionActivacion _tipo_funcion_activacion;
    
};

#endif // NEURONA_H
