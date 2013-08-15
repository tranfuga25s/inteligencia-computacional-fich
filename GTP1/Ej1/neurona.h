#ifndef NEURONA_H
#define NEURONA_H

#include "funciones_aux.h"
#include <QObject>
#include <QVector>

using namespace std;

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
    void setearTasaAprendizaje( double tasa );
    double tasaAprendizaje();

    int cantidadEntradas();
    double evaluar(QVector<double> entradas);
    void setearFuncionActivacion(tipoFuncionActivacion tipo){_tipo_funcion_activacion=tipo;}
    int funcionActivacion( double valor );
    bool entrenamiento( QVector<double> entradas, double salidaDeseada );



private:
    int _cantidad_entradas;
    double _tasa_aprendizaje;
    QVector<double> _pesos;
    Neurona::tipoFuncionActivacion _tipo_funcion_activacion;


signals:
public slots:
    
};

#endif // NEURONA_H
