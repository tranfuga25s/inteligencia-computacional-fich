#ifndef EXTERIOR_H
#define EXTERIOR_H

#include <QObject>

class Exterior : public QObject
{
    Q_OBJECT
public:
    explicit Exterior(QObject *parent = 0);
    void getTemperaturaExterior( int segundo );
};

#endif // EXTERIOR_H
