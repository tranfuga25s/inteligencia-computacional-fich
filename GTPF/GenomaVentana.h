#ifndef GENOMAVENTANA_H
#define GENOMAVENTANA_H

#include <QVector>
#include "templateventana.h"
#include "funciones_aux.h"
#include <QDebug>

//HARDCODING!
#define bits 12

class GenomaVentana {
public:
    GenomaVentana();
    GenomaVentana( const GenomaVentana& origin );
    GenomaVentana( GenomaVentana& origin );
    void iniciarRandomizado();
    void setearTemplates(QVector<TemplateVentana> informacion) {_fenotipo = informacion;}
    void aFenotipo();
    void aGenotipo();
    int size() { return _genotipo.size(); }
    void mutar( int pos ) { _genotipo[pos] = !_genotipo.at( pos ); aFenotipo(); }
    bool at( int pos ) { return this->_genotipo.at( pos ); }
    bool valido() { return true; }
    void setearGenoma( int i, bool valor) { this->_genotipo[i] = valor; }
    QVector<bool> getGenotipo() const { return _genotipo; }
    QVector<TemplateVentana> getFenotipo() const { return _fenotipo; }

    double largo();

private:
    QVector<TemplateVentana> _fenotipo;
    QVector<bool> _genotipo;

};

//Son funciones reutilizables
static void cruza( GenomaVentana &a1, GenomaVentana &a2 )
{
    int pos = valor_random_int( 0, bits );
    //qDebug() << pos;

    GenomaVentana auxA = a1;
    GenomaVentana auxB = a2;


    for(int i = pos ; i<a1.size();i++ ) {
        auxA.setearGenoma(i,a2.at(i));
        auxB.setearGenoma(i,a1.at(i));
    }

    //Para poder igualar los objetos ???
    a1.aFenotipo();
    a2.aFenotipo();

    a1 = auxA;
    a2 = auxB;

    //para actualizar los valores de los objetos
    a1.aFenotipo();
    a2.aFenotipo();
}

static void mutar( GenomaVentana &a )
{
    int pos = valor_random_int( 0, a.size() );
    a.mutar( pos );
    //a.aFenotipo();
}

#endif // GENOMAVENTANA_H
