#include "entorno.h"

Entorno::Entorno( QObject *parent, double k1, double k2, double k3, double k4, double prob_puerta ) :
QObject(parent), _k1( k1 ), _k2( k2 ), _k3( k3 ), _k4( k4 )
{
    _temperatura_externa = 0.0;
    _temperatura_interna = 0.0;
    _potencia = 0.0;
    _voltaje = 0.0;
    _puerta_abierta = false;
    _probabilidad_puerta_abierta = prob_puerta;
}

void Entorno::calcularTemperaturaTiempo()
{
    // Agrega un nuevo elemento al historial
    calcularNuevaTemperatura();
}

double Entorno::temperaturaActual()
{
    // devuleve la temperatura del momento actual
    return _historico_temperaturas.at( _historico_temperaturas.size() - 1 );
}


void Entorno::calcularNuevaTemperatura()
{
    // Calcula la temperatura nueva
    calcularPuertaAbierta(); // Verifica si la puerta está abierta o no según la probabilidad
    double nueva_temp = 0.0;
    if( _puerta_abierta ) {
        /// @TODO: Agregar formula segun guía
    } else {
        /// @TODO: Agregar formula segun guía
    }
    _historico_temperaturas.append( nueva_temp );
}

void Entorno::calcularPuertaAbierta()
{
    /// @TODO: Hacer!
}
