#include "GenomaAluminio.h"


GenomaAluminio::GenomaAluminio()
{
    _inicializado = false;
    _evaluador = 0;
}


GenomaAluminio::GenomaAluminio(const GenomaAluminio &origin )
{
    if( origin.getGenotipo().size() == 0 ) {
        abort();
    }
    this->_fenotipo = origin.getFenotipo();
    this->_genotipo = origin.getGenotipo();
    this->_evaluador = origin.getEvaluador();
}

GenomaAluminio::GenomaAluminio( GenomaAluminio &origin ) {
    if( origin.getGenotipo().size() == 0 ) {
        abort();
    }
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
    int nuevo_tamano = 0;
    QVector<int> temporal;
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

void GenomaAluminio::mostrarGenotipo() {
    QString temp;
    for( int i=0; i<_genotipo.size(); i++ ) {
        temp.append( QString::number( _genotipo.at( i ) ) ).append( ", " );
    }
    qDebug() << temp;
}
