#ifndef GENOMAVIDRIO_H
#define GENOMAVIDRIO_H

#include <QVector>
#include "TemplatePiezas.h"
#include "funciones_aux.h"
#include <QDebug>

//HARDCODING!
#define bits 12

class GenomaVidrio {
public:
    GenomaVidrio();
    GenomaVidrio( const GenomaVidrio &origin ) ;
    GenomaVidrio( GenomaVidrio &origin );
  //  void aFenotipo();
    void setearTemplates(QVector<TemplatePiezas> templates) {_fenotipo=templates;aGenotipo();}
    void aGenotipo();
    void mutar();
    int size() { return _genotipo.size(); }
    bool at( int pos ) { return this->_genotipo.at( pos ); }
    bool valido() { return true; }
    void setearGenoma( int i, bool valor) { this->_genotipo[i] = valor; }
    QVector<int> getGenotipo() const {return _genotipo;}
    QVector<TemplatePiezas> getFenotipo() const {return _fenotipo;}


    /*bool valido();
    void setMinMax( double min, double max ) { _min = min; _max = max; }
    double getMin() const { return _min; }
    double getMax() const { return _max; } */

private:
    //en fenotipo estan los tipos de piezas de vidrio sin repetir y con id = 1...n
    QVector<TemplatePiezas> _fenotipo;
    //en genotipo tenemos el orden de las piezas con su identificador de tipo
    QVector<int> _genotipo;

};

GenomaVidrio::GenomaVidrio(const GenomaVidrio &origin )
{
    this->_fenotipo = origin.getFenotipo();
    this->_genotipo = origin.getGenotipo();

}

GenomaVidrio::GenomaVidrio( GenomaVidrio &origin ) {
    this->_fenotipo = origin.getFenotipo();
    this->_genotipo = origin.getGenotipo();
}


void GenomaVidrio::aGenotipo() {
    _genotipo.clear();
    for (int i = 0; i<_fenotipo.size();i++){
        for (int p=0;p<_fenotipo.at(i).getCantidad();p++){
            _genotipo[i+p]=_fenotipo.at(i).tipo();

        }
    }
}

///!
//! \brief GenomaVidrio::mutar
//! Cada Template de piezas controla sus versiones mutadas con el indice de mutacion por lo que
//!cuando hay que mutar observamos primero si existe una version mutada. De ser asi se incrementa
//!en 1 la cantidad de esa version mutada y se decrementa la del original. Caso contrario, se crea
//!un nuevo template de pieza al final del fenotipo con las dimensiones invertidas y cantidad igual
//!a 1 y ambos quedan relacionados entre si mediante sus indices de mutacion.
//!

void GenomaVidrio::mutar()
{
    int pos = valor_random_int(0,_genotipo.size());
    int tipoPieza = _genotipo.at(pos)-1; //es -1 porq el id del fenotipo es desde 1..n
    if (_fenotipo[tipoPieza].getMutado() < 0){ //seria que no muto nunca

        //Genero el nuevo template mutado para cargar
        TemplatePiezas auxiliar = _fenotipo.at(tipoPieza);
        double ancho_auxi = auxiliar.alto();
        double alto_auxi = auxiliar.ancho();
        auxiliar.setearAlto(alto_auxi);
        auxiliar.setearAncho(ancho_auxi);
        int nuevoTipo = _fenotipo.size()+1;
        auxiliar.setearTipo(nuevoTipo);
        auxiliar.setearMutado(_fenotipo.at(tipoPieza).tipo());
        auxiliar.setearCantidad(1); //es uno nuevo, asi que es el primero de ese tipo

        //Modifico el template original
        _fenotipo[tipoPieza].setearCantidad(_fenotipo.at(tipoPieza).getCantidad()-1);
        _fenotipo[tipoPieza].setearMutado(auxiliar.tipo());

        //Modifico el numerito del genotipo
        _genotipo[pos]=auxiliar.tipo();
    } else{
        //Modificamos las cantidades de cada uno de los templates
        _fenotipo[tipoPieza].setearCantidad(_fenotipo.at(tipoPieza).getCantidad()-1);
        int indiceDelMutado = _fenotipo[tipoPieza].getMutado()-1;
        _fenotipo[indiceDelMutado].setearCantidad(_fenotipo.at(indiceDelMutado).getCantidad()+1);

        //Modifico el numerito del genotipo
        _genotipo[pos]=_fenotipo.at(indiceDelMutado).tipo();
    }
}



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
