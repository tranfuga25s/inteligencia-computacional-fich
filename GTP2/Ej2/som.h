#ifndef SOM_H
#define SOM_H

#include <QVector>
#include "funciones_aux.h"
#include <QPointF>

class SOM
{
public:
    SOM( int tamano_x, int tamano_y, int tamano_entradas );

    void entrenar( QVector<double> patron );

    double distancia( QVector<double> patron, int fila, int columna );

    void actualizarPeso(int fila_ganadora, int columna_ganadora, QVector<double> distancia_obtenida );

    QVector<double> funcionVecindad( int fila, int columna , int fila_ganadora, int columna_ganadora );

    void setearRadioVecindad( int valor ) {_radio_vecindad = valor; }
    int radioVecindad() { return _radio_vecindad; }
    void setearTasaAprendizaje(double tasa){ _tasa_aprendizaje = tasa;}

    void setearLimiteVecindad( double limite ) { _limite_vecindad = limite; }
    double limiteVecindad() { return _limite_vecindad; }

    QVector<QPointF> obtenerPuntos();

    static bool menorque( const QPointF v1, const QPointF v2 ) {
        return v1.x() < v2.x() && v1.y() < v2.y();
    }

    bool cambiosSignificativos();

private:
    // Estructura:
    // fila, columna, elemento
    QVector< QVector< QVector<double> > > _som;
    QVector< QVector<double> > _ultimos_deltas;
    int _radio_vecindad;
    double _tasa_aprendizaje;
    double _limite_vecindad;

    QVector<double> diferenciaVector( QVector<double> val1, QVector<double> val2 );
};


#endif // SOM_H
