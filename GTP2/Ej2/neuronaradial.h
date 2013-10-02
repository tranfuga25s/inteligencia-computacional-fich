#ifndef NEURONARADIAL_H
#define NEURONARADIAL_H

#include <QPoint>
#include <QList>
#include "math.h"

class NeuronaRadial
{
public:
    NeuronaRadial( int cantidad_entradas = 2 );

    QPointF getMedia() { return _media; }
    double getDesviacion() { return _desviacion; }
    int getClase() { return _clase; }
    void setearClase( int c ) { _clase = c; }

    void recalcularCentroide( QList<QPointF> lista );
    double distanciaCentroide(QPointF punto){ return sqrt( pow( punto.x() - _media.x(), 2.0 ) + pow( punto.y() - _media.y(), 2.0 ) ) ;}

    double getSalida( QPointF punto );


private:
    QPointF _media; // Punto del centroide
    float _desviacion;//Radio Gausseana

    int _clase;

    int _cantidad_entradas;

};

#endif // NEURONARADIAL_H
