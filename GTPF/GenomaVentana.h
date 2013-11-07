#ifndef GENOMAVENTANA_H
#define GENOMAVENTANA_H

#include "templateventana.h"

class GenomaVentana {
public:
    GenomaVentana();
    GenomaVentana( const GenomaVentana &origin );
    GenomaVentana( GenomaVentana& origin );
    void aFenotipo();
    void aGenotipo();
    int size() { return _genotipo.size(); }
    void mutar( int pos ) { _genotipo[pos] = !_genotipo.at( pos ); aFenotipo(); }
    bool at( int pos ) { return this->_genotipo.at( pos ); }


    /* void setearGenoma( int i, bool valor) { this->_genotipo[i] = valor; }
    void mostrarGenotipo();
    bool valido();
    void setMinMax( double min, double max ) { _min = min; _max = max; }
    double getMin() const { return _min; }
    double getMax() const { return _max; } */

private:
    QVector<TemplateVentana> _fenotipo;
    QVector<bool> _genotipo;
};

#endif // GENOMAVENTANA_H
