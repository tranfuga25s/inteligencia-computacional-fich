#ifndef EXTERIOR_H
#define EXTERIOR_H

#include <QObject>
#include <QVector>

class Exterior : public QObject
{
    Q_OBJECT
public:
    explicit Exterior(QObject *parent = 0);
    double getTemperaturaExterior( int segundo );
    QVector<double> getHistoricoTemperatura() { return _historico; }

private:
    QVector<double> _historico;

};

#endif // EXTERIOR_H
