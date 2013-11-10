#include "BarraAluminio.h"

bool BarraAluminio::acepta( double largo ) const {
    if( _largo < largo ) {
        return false;
    } else if( _largo - largo > 0 ) {
        return true;
    }
    return false;
}

void BarraAluminio::hacerCorte( double largo ) {
    _largo -= largo;
}

BarraAluminio::BarraAluminio(const BarraAluminio &b)
{
    this->_largo = b.largoActual();
}

BarraAluminio::BarraAluminio(BarraAluminio &b)
{
    this->_largo = b.largoActual();
}

BarraAluminio::BarraAluminio()
{
    _largo = 0.0;
}

