#ifndef PARTICIONADOR_H
#define PARTICIONADOR_H

#include <QObject>
#include "funciones_aux.h"

class Particionador : public QObject
{
    Q_OBJECT
public:

    class particion {
    public:
        QVector<int> entrenamiento;
        QVector<int> validacion;
        QVector<int> prueba;
    };

    Particionador( QObject *parent = 0 );

    void setearCantidadDatos( int cantidad_datos ) { _cantidad_datos = cantidad_datos; }
    int cantidadDeDatos() { return _cantidad_datos; }
    void particionarDatos();

    void setearCantidadDeParticiones( const int cant ) { _cant_particiones = cant; }
    int cantidadDeParticiones() { return _cant_particiones; }
    void setearK(int k) { _k = k; }
    int devolverk() { return _k; }

    void setearPorcentajeEntrenamiento( const double cant ) { _porcentaje_entrenamiento = cant; }
    void setearPorcentajeValidacion( const double cant ) { _porcentaje_validacion = cant; }
    double porcentajeEntrenamiento() { return _porcentaje_entrenamiento; }
    double porcentajeValidacion() { return _porcentaje_validacion; }
    double porcentajePrueba() { return 1.0-_porcentaje_entrenamiento; }

    particion getParticion( const int num );

private:
    int _cant_particiones;
    double _porcentaje_entrenamiento;
    double _porcentaje_validacion;
    int _cantidad_datos;
    int _k;

    QVector<particion> _particiones;
    
};

#endif // PARTICIONADOR_H
