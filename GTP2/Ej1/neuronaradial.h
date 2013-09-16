#ifndef NEURONARADIAL_H
#define NEURONARADIAL_H

#include <QPoint>
#include <QList>

class NeuronaRadial
{
public:
    NeuronaRadial( int cantidad_entradas = 2 );

    QPointF getMedia() { return _media; }
    double getDesviacion() { return _desviacion; }
    int getClase() { return _clase; }
    void setearClase( int c ) { _clase = c; }

    void recalcularCentroide( QList<QPointF> lista );

    double getSalida( QPointF punto );


private:
    QPointF _media; // Punto del centroide
    float _desviacion;

    int _clase;

    int _cantidad_entradas;

};

#endif // NEURONARADIAL_H
