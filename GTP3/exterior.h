#ifndef EXTERIOR_H
#define EXTERIOR_H

#include <QObject>
#include "funciones_aux.h"

class Exterior : public QObject
{
    Q_OBJECT
public:
    explicit Exterior(QObject *parent = 0);
    double getTemperaturaExterior( int segundo );
};

#endif // EXTERIOR_H
