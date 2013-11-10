#include "GenomaAluminio.h"


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
        pos2 = valor_random_int( 0, _genotipo.size() );
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

