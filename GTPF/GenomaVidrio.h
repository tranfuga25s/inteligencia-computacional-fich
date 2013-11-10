#ifndef GENOMAVIDRIO_H
#define GENOMAVIDRIO_H

#include <QVector>
#include "funciones_aux.h"
#include <QDebug>
#include "TemplatePiezas.h"
#include "FFDWDH.h"

//HARDCODING!
#define bits 12

class GenomaVidrio {
public:
    GenomaVidrio();
    GenomaVidrio( const GenomaVidrio &origin ) ;
    GenomaVidrio( GenomaVidrio &origin );
  //  void aFenotipo();
    void setearTemplates( QVector<TemplatePiezas> templates ) { _fenotipo=templates; }
    void aGenotipo();
    void mutar();
    int size() { return _genotipo.size(); }
    int at( int pos ) { return this->_genotipo.at( pos ); }
    bool valido() { return true; }
    void setearGenoma( int i, bool valor) { this->_genotipo[i] = valor; }

    QVector<int> getGenotipo() const {return _genotipo;}

    QVector<TemplatePiezas> getFenotipo() const {return _fenotipo;}

    void setearEvaluador( FFDWDH *puntero ) { _evaluador = puntero; }
    FFDWDH *getEvaluador() const { return _evaluador; }

    void randomizar();


    /*bool valido();
    void setMinMax( double min, double max ) { _min = min; _max = max; }
    double getMin() const { return _min; }
    double getMax() const { return _max; } */

private:
    //en fenotipo estan los tipos de piezas de vidrio sin repetir y con id = 1...n
    QVector<TemplatePiezas> _fenotipo;
    //en genotipo tenemos el orden de las piezas con su identificador de tipo
    QVector<int> _genotipo;

    bool _inicializado;

    FFDWDH *_evaluador;

};


static void cruza( GenomaVidrio &a1, GenomaVidrio &a2 )
{
    int pos = valor_random_int( 0, bits );
    //qDebug() << pos;

    GenomaVidrio auxA = a1;
    GenomaVidrio auxB = a2;

    //Reordenar los dos genomas a partrones a partir de pos
    //Importaria pos con respecto a como codificamos el gen ancho/alto????

    //AuxA
    //Generar un vector con los nuevos indices
    QVector<int> posAuxA = generarPosicionesAleatorias(pos,a1.size());
    //Modificar los nuevos indices a partir del vector de nuevos indice
    for (int i = 0 ; i < posAuxA.size() ; i++) {
        auxA.setearGenoma(posAuxA.at(i), a1.at(posAuxA.at(i)));
    }

    //AuxB
    //Generar un vector con los nuevos indices
    QVector<int> posAuxB = generarPosicionesAleatorias(pos,a2.size());
    //Modificar los nuevos indices a partir del vector de nuevos indice
    for (int i = 0 ; i < posAuxB.size() ; i++) {
        auxB.setearGenoma(posAuxB.at(i), a2.at(posAuxB.at(i)));
    }


    a1 = auxA;
    a2 = auxB;

}



static void mutar(GenomaVidrio &a)
{
    a.mutar();
}
#endif // GENOMAVIDRIO_H
