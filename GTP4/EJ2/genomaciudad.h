#ifndef GENOMACIUDAD_H
#define GENOMACIUDAD_H

#include <QVector>

class GenomaCiudad {

public:
    GenomaCiudad();
    GenomaCiudad( int cantCiudades );
    GenomaCiudad( const GenomaCiudad &origin );
    GenomaCiudad( GenomaCiudad& origin );

    void setearMatrizDistancias( QVector< QVector<int> > *dist ) { _distancias = dist; }
    QVector< QVector<int> > *getMatrizDistancias() const { return _distancias; }

    QVector<int> getRecorrido() const { return _recorrido; }

    int cantidadCiudades() const { return _cant_ciudades; }

    int distanciaRecorrido() const;

    bool valido();

    void mostrarRecorrido();

    int ciudad( int i ) { return _recorrido.at( i ); }
    void setearCiudad( int i, int ciudad ) { _recorrido[i] = ciudad; }

    void mutar( int pos ) { _recorrido[pos] = _cant_ciudades - _recorrido.at( pos ); }

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
    this->_recorrido = origin.getRecorrido();
    this->_distancias = origin.getMatrizDistancias();
}

GenomaCiudad::GenomaCiudad( GenomaCiudad &origin ) {
    this->_cant_ciudades = origin.cantidadCiudades();
    this->_recorrido = origin.getRecorrido();
    this->_distancias = origin.getMatrizDistancias();
}

bool GenomaCiudad::valido() {
    // Verifico que la ciudad inicial y final sean la mismas
    if( _recorrido.at(0) != _recorrido.at( _recorrido.size() -1 ) ) {
        return false;
    }
    // Veo que no existan ciudades repetidas en el recorrido
    for( int i=1; i<_recorrido.size()-1; i++ ) {
        for( int j=1; j<_recorrido.size()-1; j++ ) {
            if( _recorrido.at( i ) == _recorrido.at( j ) ) {
                return false;
            }
        }
    }
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
    _recorrido.append( _recorrido.at(0) );
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

void GenomaCiudad::mostrarRecorrido() {
    QString salida;
    salida.append( "Recorrido: " );
    for( int i=0; i<_recorrido.size(); i++ ) {
        salida.append( QString::number( _recorrido.at(i) ) ).append( "," );
    }
    qDebug() << salida;
    return;
}

void cruza( GenomaCiudad &a, GenomaCiudad &b ) {
    // Evito cambiar la primera y ultima ciudad?
    int posa = valor_random_int( 1, a.getRecorrido().size() -1 );

    QVector<int> ciudades;
    ciudades.clear();
    for( int i=posa; i<a.getRecorrido().size()-1; i++ ) {
        ciudades.append( a.ciudad( i ) );
        a.setearCiudad( i, b.ciudad( i ) );
    }
    for( int i=0; i<ciudades.size(); i++ ) {
        b.setearCiudad( posa+i, ciudades.at( i ) );
    }
}

void mutar( GenomaCiudad &a ) {
    int pos = valor_random_int( 0, a.getRecorrido().size() - 1 );

    a.mutar( pos );
}


#endif // GENOMACIUDAD_H
