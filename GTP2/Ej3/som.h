#ifndef SOM_H
#define SOM_H

#include <QVector>

class SOM
{
public:
    SOM( int tamano_x, int tamano_y, int tamano_entradas );

    void entrenar( QVector<double> patron );

    double distancia( QVector<double> patron, int fila, int columna );

    void actualizarPeso(int fila, int columna, double distancia_obtenida );

    double funcionVecindad(int fila, int columna , int fila_ganadora, int columna_ganadora);

    void setearRadioVecindad( int valor ) {_radio_vecindad = valor; }
    int radioVecindad() { return _radio_vecindad; }

    void setearClase( int fila, int col, int clase );
    int obtenerClase( int fila, int col );
    int obtenerClase( QVector<double> patron ); // Obtengo la clase evaluando el patron

private:
    QVector< QVector< QVector<double> > > _som;
    QVector< QVector<int> > _som_clasificado;
    int _radio_vecindad;
    double _tasa_aprendizaje;
};

#endif // SOM_H
