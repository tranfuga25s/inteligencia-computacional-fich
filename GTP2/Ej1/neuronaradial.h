#ifndef NEURONARADIAL_H
#define NEURONARADIAL_H

#include <QPointF>

class NeuronaRadial
{
public:
    NeuronaRadial();

    QPointF getMedia() { return _media; }
    double getDesviacion() { return _desviacion; }

    void recalcularCentroide( QList<QPointF> *lista );


private:
    QPointF _media;
    float _desviacion;

    int _clase;


};

#endif // NEURONARADIAL_H
