#include "entorno.h"

Entorno::Entorno(QObject *parent) :
    QObject(parent)
{
    _temperatura_externa = 0.0;
    _temperatura_interna = 0.0;
    _potencia = 0.0;
    _voltaje = 0.0;
    _puerta_abierta = false;
}

void Entorno::calcularTemperaturaTiempo()
{
    // Agrega un nuevo elemento al historial
}

double Entorno::temperaturaActual()
{
    // devuleve la temperatura del momento actual
}


void Entorno::calcularNuevaTemperatura()
{
    // Calcula la temperatura nueva
    if( _puerta_abierta ) {

    } else {

    }
}
