#ifndef POBLACION_H
#define POBLACION_H

#include <QVector>

template<typename T> class Poblacion : public QVector<T>
{

public:
    Poblacion();
    void setearTotal( int cantidad_total ) { _cantidad_total = cantidad_total; }
    int totalPoblacion() const { return _cantidad_total; }

private:
    int _cantidad_total;
    
};

template<typename T> Poblacion<T>::Poblacion() :
    QVector<T>()
{
}
#endif // POBLACION_H
