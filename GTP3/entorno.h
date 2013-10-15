#ifndef ENTORNO_H
#define ENTORNO_H

#include <QObject>

#include <QVector>

/*!
 * \brief The Entorno class
 *
 *  Clase que representa el lugar a el entorno a controlar
 */
class Entorno : public QObject
{
    Q_OBJECT
public:
    explicit Entorno( QObject *parent,
                      double k1,
                      double k2,
                      double k3,
                      double k4,
                      double prob_puerta );
    QVector<double> historicoTemperatura() { return _historico_temperaturas; }
    void calcularTemperaturaTiempo();

    double temperaturaActual();
    int tiempo() { return _historico_temperaturas.size(); }

public slots:
    void setearTemperaturaInterna( double temperatura ) { _temperatura_interna = temperatura; }
    void setearTemperaturaExterna( double temperatura ) { _temperatura_externa = temperatura; }
    void setearPotenciaEstufa( double potencia ) { _potencia = potencia; }
    void setearVoltajeRefrigeracion( double voltaje ) { _voltaje = voltaje; }
    void setearPuertaAbierta( bool estado ) { _puerta_abierta = estado; }

private:
    bool _puerta_abierta;
    double _temperatura_externa;
    double _temperatura_interna;
    double _potencia;
    double _voltaje;

    double _k1, _k2, _k3, _k4;
    double _probabilidad_puerta_abierta;

    QVector<double> _historico_temperaturas;

    void calcularNuevaTemperatura();
    void calcularPuertaAbierta();

};

#endif // ENTORNO_H
