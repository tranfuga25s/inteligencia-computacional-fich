#ifndef CONTROLADORDIFUSO_H
#define CONTROLADORDIFUSO_H

#include <QObject>

class TrapecioDifuso {

    explicit TrapecioDifuso( double pos1, double pos2, double pos3, double pos4, QString nombre );
    double valorSalida( double valor_entrada );
    double centroide( double valor_y );


public:
    double pos1;
    double pos2;
    double pos3;
    double pos4;
    QString _nombre;
};

class ControladorDifuso : public QObject
{
    Q_OBJECT
public:
    explicit ControladorDifuso(QObject *parent = 0);
    void calcularProximoPaso();
    double getVoltaje();
    double getIntensidad();
    void setearTemperaturaInterior( double valor ) { _ultima_temp = valor; }

private:
    double _ultima_temp;

    QVector<TrapecioDifuso> _conjunto_entrada;

    QVector<TrapecioDifuso> _conjunto_salida_voltaje;
    QVector<TrapecioDifuso> _conjunto_salida_intensidad;
    
};




#endif // CONTROLADORDIFUSO_H
