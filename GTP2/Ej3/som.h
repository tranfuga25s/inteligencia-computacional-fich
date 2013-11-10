#ifndef SOM_H
#define SOM_H

#include <QVector>
#include "funciones_aux.h"
#include <QPointF>

class SOM
{
public:
    SOM( int tamano_x, int tamano_y, int tamano_entradas );

    void entrenar( QVector<double> patron);

    double distancia( QVector<double> patron, int fila, int columna );

    void actualizarPeso(int fila_ganadora, int columna_ganadora, vector distancia_obtenida);

    void setearRadioVecindad( int valor ) {_radio_vecindad = valor; }
    int radioVecindad() { return _radio_vecindad; }
    void setearTasaAprendizaje(double tasa){ _tasa_aprendizaje = tasa;}

    QVector<QPointF> obtenerPuntos();

    static bool menorqueX( const QPointF v1, const QPointF v2 ) {
        return ( ( v1.x() <= v2.x() ) );
    }
    static bool menorqueY( const QPointF v1, const QPointF v2 ) {
        return ( ( v1.y() <= v2.y() ) );
    }

    bool cambiosSignificativos();

    QPair<int,int> getNeuronaGanadora(QVector<double> patron);
    void setearClase(int fila,int columna, int clase);
    int devolverClasesSalida(int fila,int columna);

private:
    // Estructura:
    // fila, columna, elemento
    QVector< QVector< QVector<double> > > _som;
    QVector< QVector<double> > _ultimos_deltas;
    QVector< QVector<int> > _clases;
    int _radio_vecindad;
    double _tasa_aprendizaje;

    QVector<double> diferenciaVector( QVector<double> val1, QVector<double> val2 );

};


#endif // SOM_H
