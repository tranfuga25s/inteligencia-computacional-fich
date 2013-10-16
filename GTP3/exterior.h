#ifndef EXTERIOR_H
#define EXTERIOR_H

#include <QObject>
#include <QVector>
#include "funciones_aux.h"

class Exterior : public QObject
{
    Q_OBJECT
public:
    explicit Exterior(QObject *parent = 0);
    double getTemperatura( int segundo );
    QVector<double> getHistoricoTemperatura() { return _historico; }

    void setearTemperaturaSuperior( double temp ) { _max = temp; }
    void setearTemperaturaInferior( double temp ) { _min = temp; }
    void setearTiempoCambio( int cantidad_seg ) { _cant_seg = cantidad_seg; }

private:
    QVector<double> _historico;
    double _max;
    double _min;
    double _ultima_temp;
    int _cant_seg;
    int _ultimo_cambio;

};

#endif // EXTERIOR_H
