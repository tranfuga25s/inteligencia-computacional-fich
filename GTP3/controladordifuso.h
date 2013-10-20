#ifndef CONTROLADORDIFUSO_H
#define CONTROLADORDIFUSO_H

#include <QObject>
#include <QVector>

class TrapecioDifuso {

public:
    explicit TrapecioDifuso( double p1, double p2, double p3, double p4, QString nom );
    double valorSalida( double valor_entrada );
    double centroide();
    double area( double valor_y );
    QString nombre() { return _nombre; }

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
    void setearTemperaturaDeseada( double valor ) { _ultima_deseada = valor; }

    void agregarConjuntoEntrada( QString nombre, QVector<double> posiciones );
    void agregarConjuntoSalidaVoltaje( QString nombre, QVector<double> posiciones );
    void agregarConjuntoSalidaIntensidad( QString nombre, QVector<double> posiciones );

    void agregarReglaVoltaje( int conjunto_entrada, int conjunto_salida );
    void agregarReglaIntensidad( int conjunto_entrada, int conjunto_salida );

    QVector<double> historicoVoltaje() { return _historico_voltaje; }
    QVector<double> historicoIntensidad() { return _historico_intensidad; }

private:
    double _ultima_temp;
    double _ultima_deseada;
    double _ultima_intensidad;
    double _ultimo_voltaje;

    QVector<TrapecioDifuso *> _conjunto_entrada;

    QVector<TrapecioDifuso *> _conjunto_salida_voltaje;
    QVector<TrapecioDifuso *> _conjunto_salida_intensidad;

    // El primer vector refleja el trapecio de entrada activado
    // La segunda dimension es que conjuntos de salida tenemos que activar y verificar
    QVector< QVector<int> > _reglas_voltaje;
    QVector< QVector<int> > _reglas_intensidad;

    QVector<double> _historico_voltaje;
    QVector<double> _historico_intensidad;
    
};




#endif // CONTROLADORDIFUSO_H
