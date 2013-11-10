#ifndef GENOMAALUMINIO_H
#define GENOMAALUMINIO_H

#include <QVector>
#include "funciones_aux.h"
#include <QDebug>
#include "TemplatePiezas.h"
#include "FFDWDH.h"

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


private:
    //en fenotipo estan los tipos de piezas de vidrio sin repetir y con id = 1...n
    QVector<TemplateAluminio> _fenotipo;
    //en genotipo tenemos el orden de las piezas con su identificador de tipo
    QVector<int> _genotipo;

    bool _inicializado;

    FFDW *_evaluador;

};

GenomaAluminio::GenomaAluminio()
{
    _inicializado = false;
    _evaluador = 0;
}


GenomaAluminio::GenomaAluminio(const GenomaAluminio &origin )
{
    this->_fenotipo = origin.getFenotipo();
    this->_genotipo = origin.getGenotipo();
    this->_evaluador = origin.getEvaluador();
}

GenomaAluminio::GenomaAluminio( GenomaAluminio &origin ) {
    this->_fenotipo = origin.getFenotipo();
    this->_genotipo = origin.getGenotipo();
    this->_evaluador = origin.getEvaluador();
}


void GenomaAluminio::aGenotipo() {
    /*_genotipo.clear();
    for (int i = 0; i<_fenotipo.size();i++){
        for (int p=0;p<_fenotipo.at(i).getCantidad();p++){
            _genotipo[i+p]=_fenotipo.at(i).tipo();

        }
    } */
}

void GenomaAluminio::mutar()
{
    int pos1 = valor_random_int( 0, _genotipo.size() );
    int pos2 = valor_random_int( 0, _genotipo.size() );

    while (_genotipo.at(pos1) ==  _genotipo.at(pos2)) {
        pos2 = valor_random_int( 0, a.size() );
    }
    int aux = _genotipo.at(pos1);

    _genotipo[pos1] = _genotipo.at( pos2 );
    _genotipo[pos2] = aux;

}

void GenomaAluminio::randomizar() {
    _genotipo.clear();
    QVector<int> temporal;
    for (int i = 0; i<_fenotipo.size();i++){
        for (int p=0;p<_fenotipo.at(i).getCantidad();p++){
            temporal[i+p]=_fenotipo.at(i).tipo();
        }
    }
    for( int i=0; i<temporal.size(); i++ ) {
        int pos_random = valor_random_int( 0, temporal.size() -1 );
        _genotipo[i] = temporal.at(pos_random);
    }
}

static void cruza( GenomaAluminio &a1, GenomaAluminio &a2 )
{
    int pos = valor_random_int( 0, bits );
    //qDebug() << pos;

    GenomaAluminio auxA = a1;
    GenomaAluminio auxB = a2;

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



static void mutar(GenomaAluminio &a)
{

    a.mutar( );
}

#endif // GENOMAALUMINIO_H
