#ifndef NEURONARADIAL_H
#define NEURONARADIAL_H

#include <QPoint>
#include <QList>
#include "math.h"
#include "funciones_aux.h"

class NeuronaRadial
{
public:
    NeuronaRadial( int cantidad_entradas = 2 );

    vector getMedia() { return _media; }
    double getDesviacion() { return _desviacion; }
    int getClase() { return _clase; }
    void setearClase( int c ) { _clase = c; }

    void recalcularCentroide( QList<vector> lista );
    double distanciaCentroide(vector punto);

    double getSalida(vector punto );


private:
    vector _media; // Punto del centroide
    float _desviacion;//Radio Gausseana

    int _clase;

    int _cantidad_entradas;

};

#endif // NEURONARADIAL_H
