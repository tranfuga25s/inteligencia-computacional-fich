#include "BarraAluminio.h"

#include <QDebug>

bool BarraAluminio::acepta( double largo ) const {
    //qDebug() << "Largo actual: " << _largo << "- buscado: "<<largo;
    if( _largo >= largo ) {
        //qDebug() << "Acepto";
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

