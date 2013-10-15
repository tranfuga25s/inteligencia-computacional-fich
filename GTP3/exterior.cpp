#include "exterior.h"

Exterior::Exterior(QObject *parent) :
    QObject(parent)
{
}

double Exterior::getTemperaturaExterior( int segundo )
{
    /// @TODO: Agregar volatilidad de temperatura, esto queda de ejemplo
    if( floor( segundo % 600 ) ) {
        return 18.0;
    } else {
        return 22.0;
    }
}
