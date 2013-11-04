#ifndef GENOMACIUDAD_H
#define GENOMACIUDAD_H

#include <QVector>

#define tamano_indice 4 // 2^4 = 16

class GenomaCiudad {

public:
    GenomaCiudad();
    GenomaCiudad( int cantCiudades );
    GenomaCiudad( const GenomaCiudad &origin );
    GenomaCiudad( GenomaCiudad& origin );
    void setearMatrizDistancias( QVector< QVector<int> > *dist ) { _distancias = dist; }

    int cantidadCiudades() const { return _cant_ciudades; }

    int distanciaRecorrido() const;

    bool valido();

private:
    int _cant_ciudades;
    QVector<int> _recorrido;
    QVector< QVector<int> > *_distancias;

    void generarNuevoRecorrido();

};

GenomaCiudad::GenomaCiudad() {
    this->_cant_ciudades = 0;
    this->_recorrido.clear();
}

GenomaCiudad::GenomaCiudad( int cantCiudades ) {
    this->_cant_ciudades = cantCiudades;
    this->generarNuevoRecorrido();
}

GenomaCiudad::GenomaCiudad( const GenomaCiudad &origin ) {
    this->_cant_ciudades = origin.cantidadCiudades();
    this->generarNuevoRecorrido();
}

GenomaCiudad::GenomaCiudad( GenomaCiudad &origin ) {
    this->_cant_ciudades = origin.cantidadCiudades();
    this->generarNuevoRecorrido();
}

bool GenomaCiudad::valido() {
    return false;
}

void GenomaCiudad::generarNuevoRecorrido() {
    _recorrido.clear();
    QVector<int> temp;
    for( int i=0; i<_cant_ciudades; i++ ) {
        temp.append( i );
    }
    for( int i=0; i<_cant_ciudades; i++ ) {
        int pos = valor_random_int( 0, temp.size() );
        _recorrido.append( temp.at( pos ) );
        temp.at( pos );
    }
}

int GenomaCiudad::distanciaRecorrido() const {
    int anterior = _recorrido.at( 0 );
    int nuevo = 0;
    int distancia = 0;
    for( int i = 0; i < _recorrido.size() - 1; i++ ) {
        nuevo = _recorrido.at( i );
        distancia += _distancias->at( anterior ).at( nuevo );
        anterior = nuevo;
    }
    return distancia;
}

void cruza( GenomaCiudad &a, GenomaCiudad &b ) {
    /// @TODO: implementar
}

void mutar( GenomaCiudad &a ) {
    /// @TODO: implementar
}


#endif // GENOMACIUDAD_H
