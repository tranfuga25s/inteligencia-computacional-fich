#include "GenomaVidrio.h"

GenomaVidrio::GenomaVidrio()
{
    _inicializado = false;
    _evaluador = 0;
}


GenomaVidrio::GenomaVidrio(const GenomaVidrio &origin )
{
    this->_fenotipo = origin.getFenotipo();
    this->_genotipo = origin.getGenotipo();
    this->_evaluador = origin.getEvaluador();
}

GenomaVidrio::GenomaVidrio( GenomaVidrio &origin ) {
    this->_fenotipo = origin.getFenotipo();
    this->_genotipo = origin.getGenotipo();
    this->_evaluador = origin.getEvaluador();
}


void GenomaVidrio::aGenotipo() {
    /*_genotipo.clear();
    for (int i = 0; i<_fenotipo.size();i++){
        for (int p=0;p<_fenotipo.at(i).getCantidad();p++){
            _genotipo[i+p]=_fenotipo.at(i).tipo();

        }
    } */
}

void GenomaVidrio::randomizar() {
    _genotipo.clear();
    QVector<int> temporal;
    int nuevo_tamano = 0;
    for (int i = 0; i<_fenotipo.size();i++){
        nuevo_tamano += _fenotipo.at(i).getCantidad();
        for (int p=0;p<_fenotipo.at(i).getCantidad();p++){
            temporal.append( _fenotipo.at(i).tipo() );
        }
    }
    _genotipo.resize( nuevo_tamano );
    int pos = 0;
    while( temporal.size() > 0 ) {
        if( temporal.size() == 1 ) {
            _genotipo[pos] = temporal.at(0);
            temporal.clear();
        } else {
            int pos_random = valor_random_int( 0, temporal.size() -1 );
            _genotipo[pos] = temporal.at(pos_random);
            temporal.remove(pos_random);
        }
        pos++;
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



