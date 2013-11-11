#ifndef GENOMAALUMINIO_H
#define GENOMAALUMINIO_H

#include <QVector>
#include "funciones_aux.h"
#include <QDebug>
//#include "TemplatePiezas.h"
#include "FFDW.h"

//HARDCODING!
#define bits 12

class GenomaAluminio {
public:
    GenomaAluminio();
    GenomaAluminio( const GenomaAluminio &origin ) ;
    GenomaAluminio( GenomaAluminio &origin );
  //  void aFenotipo();
    void setearTemplates( QVector<TemplateAluminio> templates ) { _fenotipo=templates; }
    void aGenotipo();
    void mutar( );
    int size() { return _genotipo.size(); }
    int at( int pos ) { return this->_genotipo.at( pos ); }
    bool valido() { return true; }
    void setearGenoma( int i, bool valor) { this->_genotipo[i] = valor; }

    QVector<int> getGenotipo() const {return _genotipo;}

    QVector<TemplateAluminio> getFenotipo() const {return _fenotipo;}

    void setearEvaluador( FFDW *puntero ) { _evaluador = puntero; }
    FFDW *getEvaluador() const { return _evaluador; }

    void randomizar();

    void mostrarGenotipo();


private:
    //en fenotipo estan los tipos de piezas de vidrio sin repetir y con id = 1...n
    QVector<TemplateAluminio> _fenotipo;
    //en genotipo tenemos el orden de las piezas con su identificador de tipo
    QVector<int> _genotipo;

    bool _inicializado;

    FFDW *_evaluador;

};

static void cruza( GenomaAluminio &a1, GenomaAluminio &a2 )
{
    int pos = valor_random_int( 0, a1.size() );
    //qDebug() << pos;

    GenomaAluminio auxA = a1;
    GenomaAluminio auxB = a2;

    //Reordenar los dos genomas a partrones a partir de pos
    //Importaria pos con respecto a como codificamos el gen ancho/alto????
    a1.mostrarGenotipo();
    //AuxA
    //Generar un vector con los nuevos indices
    QVector<int> posAuxA = generarPosicionesAleatorias(pos,a1.size());
    //Modificar los nuevos indices a partir del vector de nuevos indice
    for (int i = 0 ; i < posAuxA.size() ; i++) {
        auxA.setearGenoma(posAuxA.at(i), a1.at(posAuxA.at(i)));
    }
    a1 = auxA;
    //a1.mostrarGenotipo();

    //a2.mostrarGenotipo();
    //AuxB
    //Generar un vector con los nuevos indices
    QVector<int> posAuxB = generarPosicionesAleatorias(pos,a2.size());
    //Modificar los nuevos indices a partir del vector de nuevos indice
    for (int i = 0 ; i < posAuxB.size() ; i++) {
        auxB.setearGenoma(posAuxB.at(i), a2.at(posAuxB.at(i)));
    }

    a2 = auxB;
    //a2.mostrarGenotipo();
}

static void mutar(GenomaAluminio &a)
{
    //qDebug() << "Mutacion!";
    a.mutar();
    a.mostrarGenotipo();
}

#endif // GENOMAALUMINIO_H
