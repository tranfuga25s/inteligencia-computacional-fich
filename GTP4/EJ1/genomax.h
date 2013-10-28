#ifndef GENOMA_H
#define GENOMA_H

#define cant_entera 10
#define cant_decimal 10


#include <QVector>
#include <funciones_aux.h>

/**
 * \brief The Genoma class
 */
class GenomaX
{
public:
    GenomaX();
    void aFenotipo();
    void aGenotipo();
    int size() { return _fenotipo.size(); }
    void mutar( int pos ) { _fenotipo[pos] = !_fenotipo.at( pos ); }
    double getX() { return _x; }
    bool at( int pos ) { return _fenotipo.at( pos ); }
    bool & operator[] ( int i ) { return _fenotipo[i]; }
    void setX( double valor ) { _x = valor; aFenotipo();}
    void mostrasFeneotipo();

private:
    double _x; // Genotipo
    QVector<bool> _fenotipo;
};

GenomaX::GenomaX() {
    _fenotipo.reserve(20);

    for(int i = 0; i < 20 ; i++) {
        _fenotipo.append(false);
    }
    _x = 0.0;
}

void GenomaX::aFenotipo() {
    // Convierte el doble en una cadena de bits
    // Tomo la parte entera y la convierto a cadena de bits
    // Tomo la parte decimal y la convierto a cadena de bits

    int x_aux_entero = floor(_x);
    double x_aux_decimal = (_x - floor(_x) * pow(10,cant_decimal));

    qDebug() << floor(fmod(x_aux_entero,2.0));


    //Parte Entera
    for (int i = cant_entera - 1 ; i>=0 ; i--) {
        if(floor(fmod(x_aux_entero,2.0)) == 1.0) {
            _fenotipo[i] = true;
        }
        else
        {
            _fenotipo[i]  = false;
        }

        x_aux_entero = x_aux_entero/2.0;
    }

    //Parte decimal
    for (int i = cant_entera ; i < cant_entera + cant_decimal ; i++) {
        if(floor(fmod(x_aux_decimal,2.0)) == 1.0) {
            _fenotipo[i] = true;
        }
        else
        {
            _fenotipo[i] = false;
        }

        x_aux_decimal = x_aux_decimal/2.0;
     }


}

void GenomaX::aGenotipo() {
    // Convierte la cadena de bits en un numero doble
    double temporal = 0.0;
    for( int i=cant_entera; i>=0; i-- ) {
        if (_fenotipo.at(i)) {
            temporal += pow( 2.0, cant_entera - i );
        }
    }
    for( int i=cant_entera; i<_fenotipo.size(); i++ ) {
        if (_fenotipo.at(i)) {
            temporal += pow( 2.0, (-1)*(i - cant_entera) );
        }
    }
}


void mutar( GenomaX &g ) {
    int pos = valor_random( 0, g.size() );
    g.mutar( pos );
    g.aGenotipo();
}

void cruza( GenomaX &a, GenomaX &b ) {
    //Asumimos que tienen la misma profundidad de bits los genomas

    int pos = valor_random( 0, a.size() );

    GenomaX auxA = a;
    GenomaX auxB = b;

    for (int i = pos; i<a.size(); i++) {
        auxB[i] = a.at(i);
        auxA[i] = b.at(i);
    }

    a = auxA;
    b = auxB;

}

void GenomaX::mostrasFeneotipo() {
    qDebug() << "Fenotipo:" << _fenotipo;
}


#endif // GENOMA_H
