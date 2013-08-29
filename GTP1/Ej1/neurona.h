#ifndef NEURONA_H
#define NEURONA_H

#include "funciones_aux.h"
#include <QObject>
#include <QVector>

class Neurona : public QObject
{
    Q_OBJECT
public:


    Neurona( QObject *parent = 0, int cantidadEntradas = 1 );

    void inicializarPesos();
    QVector<double> devuelvePesos();
    void seteaPesos(QVector<double> pesos);

    void setearTasaAprendizaje( double tasa ) { _tasa_aprendizaje = tasa; }
    double tasaAprendizaje() { return _tasa_aprendizaje; }

    int cantidadEntradas() { return _cantidad_entradas; }

    double evaluar(QVector<double> entradas);
    double entrenamiento( QVector<double> entradas, double salidaDeseada );

    double funcionActivacion( double valor );


private:
    int _cantidad_entradas;
    double _tasa_aprendizaje;
    QVector<double> _pesos;

    
};

#endif // NEURONA_H
