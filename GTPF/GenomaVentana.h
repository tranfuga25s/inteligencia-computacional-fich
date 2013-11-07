#ifndef GENOMAVENTANA_H
#define GENOMAVENTANA_H

#include <QVector>
#include "templateventana.h"

//HARDCODING!
#define bits 12

class GenomaVentana {
public:
    GenomaVentana();
    GenomaVentana( const GenomaVentana &origin );
    GenomaVentana( GenomaVentana& origin );
    void setearFenotipo(QVector<TemplateVentana> informacion) {_fenotipo = informacion;}
    void aFenotipo();
    void aGenotipo();
    int size() { return _genotipo.size(); }
    void mutar( int pos ) { _genotipo[pos] = !_genotipo.at( pos ); aFenotipo(); }
    bool at( int pos ) { return this->_genotipo.at( pos ); }


    /* void setearGenoma( int i, bool valor) { this->_genotipo[i] = valor; }
    void mostrarGenotipo();
    bool valido();
    void setMinMax( double min, double max ) { _min = min; _max = max; }
    double getMin() const { return _min; }
    double getMax() const { return _max; } */

private:
    QVector<TemplateVentana> _fenotipo;
    QVector<bool> _genotipo;

};

#endif // GENOMAVENTANA_H



GenomaVentana::GenomaVentana()
{
    //Reservas la cantidad de bits
    _genotipo.resize(bits * 2 * _fenotipo.size());

}

void GenomaVentana::aFenotipo()
{
    // Convierte la cadena de bits en un numero doble
    int desplazamiento = 0;

    for (int j = 0 ; j < _fenotipo.size() ; j++) {

        double temporal = 0.0;

        //Ancho
        for( int i=bits; i>=0; i-- ) {
            if (_genotipo.at(i + desplazamiento)) {
                temporal += pow( 2.0, ( bits ) - i );
            }
        }

        desplazamiento += bits;

        _fenotipo[j].setearAncho(temporal);

        temporal = 0.0;

        //Alto
        for( int i=bits; i>=0; i-- ) {
            if (_genotipo.at(i + desplazamiento)) {
                temporal += pow( 2.0, ( bits ) - i );
            }
        }

        desplazamiento += bits;

        _fenotipo[j].setearAlto(temporal);
    }
}

void GenomaVentana::aGenotipo()
{
    int desplazamiento = 0;

    //Primero recorremos el fenotipo
    for(int j = 0 ; j < _fenotipo.size() ; j++) {
        double ancho_aux = _fenotipo[j].ancho();
        double alto_aux = _fenotipo[j].alto();
        double max_alto = _fenotipo[j].maxAlto();
        double min_alto = _fenotipo[j].minAlto();
        double max_ancho = _fenotipo[j].maxAncho();
        double min_ancho = _fenotipo[j].minAncho();


        //Ancho decimales
        double ancho_decimal = (pow(2,bits) - 1.0) * (ancho_aux - min_ancho) / (max_ancho - min_ancho);

        for (int i = bits ; i >= 0 ; i--) {
            if( fmod( ancho_decimal, 2.0 ) == 1.0) {
                _genotipo[i + desplazamiento] = true;
            }
            else
            {
                _genotipo[i + desplazamiento] = false;
            }

            ancho_decimal /= 2.0;
            //Parte entera sin redondeo
            modf( ancho_decimal, &ancho_decimal );
         }

        desplazamiento += bits;

        //Alto decimal
        double alto_decimal = (pow(2,bits) - 1.0) * (alto_aux - min_alto) / (max_alto - min_alto);

        for (int i = bits ; i >= 0 ; i--) {
            if( fmod( alto_decimal, 2.0 ) == 1.0) {
                _genotipo[i + desplazamiento] = true;
            }
            else
            {
                _genotipo[i + desplazamiento] = false;
            }

            alto_decimal /= 2.0;
            //Parte entera sin redondeo
            modf( alto_decimal, &alto_decimal );
        }

        desplazamiento += bits;

        qDebug() << _genotipo;


    }
}