#include "exterior.h"

Exterior::Exterior(QObject *parent) :
    QObject(parent)
{
}

double Exterior::getTemperaturaExterior( int segundo )
{
    /// @TODO: Agregar volatilidad de temperatura, esto queda de ejemplo
    if( ( segundo % 600 ) > 0 ) {
        _historico.append( 18.0 );
        return 18.0;
    } else {
        _historico.append( 22.0 );
        return 22.0;
    }
}
