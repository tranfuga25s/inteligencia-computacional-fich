#include "GenomaVentana.h"


GenomaVentana::GenomaVentana()
{
    //Reservas la cantidad de bits
    _genotipo.resize(bits * 2 * _fenotipo.size());

}

GenomaVentana::GenomaVentana(GenomaVentana& origin) {
    _genotipo.resize(origin._genotipo.size());
    _fenotipo.resize(origin._fenotipo.size());
    this->_fenotipo = origin.getFenotipo();
    this->_genotipo = origin.getGenotipo();
}

//Genera TODOS 0
void GenomaVentana::iniciarRandomizado()
{
    _genotipo.clear();
    for( int i=0; i<_fenotipo.size(); i++ ) {
        for( int k=0; k<bits+bits; k++ ) {
            _genotipo.append(valor_random_cerouno());
        }
    }
}

GenomaVentana::GenomaVentana( const GenomaVentana& origin ) {
    _genotipo.resize(origin._genotipo.size());
    _fenotipo.resize(origin._fenotipo.size());
    this->_fenotipo = origin.getFenotipo();
    this->_genotipo = origin.getGenotipo();
}


void GenomaVentana::aFenotipo()
{
    // Convierte la cadena de bits en un numero doble
    int desplazamiento = 0;

    for (int j = 0 ; j < _fenotipo.size() ; j++) {

        double temporal = 0.0;

        //Ancho
        for( int i=bits-1; i>=0; i-- ) {
            if (_genotipo.at(i + desplazamiento)) {
                temporal += pow( 2.0, ( bits - 1) - i );
            }
        }

        desplazamiento += bits;

        //Tendria que mapear el valor de temporal a un rango valido para el problema

        temporal = temporal/ (pow(2,bits) -1);
        double rangoAncho = _fenotipo.at(j).maxAncho() - _fenotipo.at(j).minAncho();


        _fenotipo[j].setearAncho(temporal*rangoAncho + _fenotipo.at(j).minAncho());

        temporal = 0.0;

        //Alto
        for( int i=bits-1; i>=0; i-- ) {
            if (_genotipo.at(i + desplazamiento)) {
                temporal += pow( 2.0, ( bits - 1 ) - i );
            }
        }

        desplazamiento += bits;

        //Tendria que mapear el valor de temporal a un rango valido para el problema

        temporal = temporal/ (pow(2,bits) -1);
        double rangoAlto = _fenotipo.at(j).maxAlto() - _fenotipo.at(j).minAlto();

        _fenotipo[j].setearAlto(temporal*rangoAlto + _fenotipo.at(j).minAlto());
    }
}

//No se usa

void GenomaVentana::aGenotipo()
{
    int desplazamiento = 0;

    _genotipo.resize(bits*_fenotipo.size());

    //Primero recorremos el fenotipo
    for(int j = 0 ; j < _fenotipo.size() ; j++) {
        double ancho_aux = _fenotipo[j].ancho();
        double alto_aux = _fenotipo[j].alto();
        double max_alto = _fenotipo[j].maxAlto();
        double min_alto = _fenotipo[j].minAlto();
        double max_ancho = _fenotipo[j].maxAncho();
        double min_ancho = _fenotipo[j].minAncho();


        //Ancho decimales
        double ancho_decimal = (pow(2,bits -1) - 1.0) * (ancho_aux - min_ancho) / (max_ancho - min_ancho);

        for (int i = bits -1 ; i >= 0 ; i--) {
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
        double alto_decimal = (pow(2,bits -1) - 1.0) * (alto_aux - min_alto) / (max_alto - min_alto);

        for (int i = bits -1 ; i >= 0 ; i--) {
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

        //qDebug() << _genotipo;


    }
}

/*!
 * \brief GenomaVentana::costoTotal
 * \return
 */
double GenomaVentana::costoTotal( double costo_vidrio, double costo_aluminio )
{
    // Recorro la ventana y reconvierto a costo
    double costo_total = 0.0;

    foreach( TemplateVentana templ, _fenotipo ) {

        costo_total += 2.0 * costo_aluminio * templ.alto() * templ.getCantidad();
        costo_total += 2.0 * costo_aluminio * templ.ancho() * templ.getCantidad();

        costo_total += costo_vidrio * ( templ.ancho() * templ.alto() ) * templ.getCantidad();
    }

    return costo_total;
}
