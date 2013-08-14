#ifndef NEURONA_H
#define NEURONA_H

#include <QObject>
#include <vector>

using namespace std;

class Neurona : public QObject
{
    Q_OBJECT
public:
    Neurona( QObject *parent = 0, int cantidadEntradas = 1 );
    void setearTasaAprendizaje( double tasa );
    double tasaAprendizaje();

    int cantidadEntradas();


private:
    int _cantidad_entradas;
    double _tasa_aprendizaje;
    vector<double> _pesos;
    
signals:
public slots:
    
};

#endif // NEURONA_H
