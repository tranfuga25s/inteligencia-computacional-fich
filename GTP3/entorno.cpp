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
    double temp_ant = 0.0;
    if( _historico_temperaturas.size() > 2 ) {
        temp_ant = _historico_temperaturas.at( _historico_temperaturas.size() - 2 );
    } else {
        temp_ant = _temperatura_interna;
    }
    if( _puerta_abierta ) {
        nueva_temp = 0.912*temp_ant + 0.088*_temperatura_externa;
    } else {
        nueva_temp = 0.169*temp_ant + 0.831*_temperatura_externa;
    }
    _historico_temperaturas.append( nueva_temp );
}

void Entorno::calcularPuertaAbierta()
{
   double a = valor_random(1,_probabilidad_puerta_abierta);
   if (fmod(a,_probabilidad_puerta_abierta) == 0.0) {
       _puerta_abierta = true;
   }
   else
   {
       _puerta_abierta = false;
   }
}
