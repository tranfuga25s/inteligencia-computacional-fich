#ifndef CONTROLADORDIFUSO_H
#define CONTROLADORDIFUSO_H

#include <QObject>

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
    
};

#endif // CONTROLADORDIFUSO_H
