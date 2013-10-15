#ifndef CONTROLADORDIFUSO_H
#define CONTROLADORDIFUSO_H

#include <QObject>
#include <QVector>

class TrapecioDifuso {

public:
    explicit TrapecioDifuso( double pos1, double pos2, double pos3, double pos4, QString nombre );
    double valorSalida( double valor_entrada );
    double centroide( double valor_y );


private:
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

    void agregarConjuntoEntrada( QString nombre, QVector<double> posiciones );
    void agregarConjuntoSalidaVoltaje( QString nombre, QVector<double> posiciones );
    void agregarConjuntoSalidaIntensidad( QString nombre, QVector<double> posiciones );

private:
    double _ultima_temp;

    QVector<TrapecioDifuso *> _conjunto_entrada;

    QVector<TrapecioDifuso *> _conjunto_salida_voltaje;
    QVector<TrapecioDifuso *> _conjunto_salida_intensidad;
    
};




#endif // CONTROLADORDIFUSO_H
