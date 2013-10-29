#ifndef POBLACION_H
#define POBLACION_H

#include <QVector>

template<typename T> class Poblacion : public QVector<T>
{

public:
    Poblacion();
    void setearTotal( int cantidad_total ) { _cantidad_total = cantidad_total; }
    int totalPoblacion() const { return _cantidad_total; }

    void setearElitismo( bool activo ) { _elitismo = activo; }
    bool elitismo() const  { return _elitismo; }

private:
    int _cantidad_total;
    bool _elitismo;
    
};

template<typename T> Poblacion<T>::Poblacion() :
    QVector<T>()
{
    _elitismo = false;
    _cantidad_total = 0.0;
}
#endif // POBLACION_H
