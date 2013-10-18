#include "entorno.h"

Entorno::Entorno( QObject *parent, double prob_puerta ) :
QObject(parent)
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
    if( _historico_temperaturas.size() > 0 ) {
        return _historico_temperaturas.at( _historico_temperaturas.size() - 1 );
    } else {
        return _temperatura_interna;
    }
}


void Entorno::calcularNuevaTemperatura()
{
    // Calcula la temperatura nueva
    double nueva_temp = 0.0;
    double temp_ant = 0.0;
    if( _historico_temperaturas.size() > 2 ) {
        temp_ant = _historico_temperaturas.at( _historico_temperaturas.size() - 2 );
    } else {
        temp_ant = _temperatura_interna;
    }

    if( _voltaje == 0.0 && _potencia == 0.0 ) {
        // estamos en un sistema sin control
        if( _puerta_abierta == false ) {
            nueva_temp = 0.912*temp_ant + 0.088*_temperatura_externa;
        } else {
            nueva_temp = 0.169*temp_ant + 0.831*_temperatura_externa;
        }
    } else {
        if( _puerta_abierta == false ) {
            nueva_temp = 0.912 * temp_ant +
                         0.088 * _temperatura_externa +
                         0.604 * pow( _potencia, 2.0 ) -
                         0.0121 * _voltaje;
        } else {
            nueva_temp = 0.169 * temp_ant +
                         0.831 * _temperatura_externa +
                         0.112 * pow( _potencia, 2.0 ) -
                         0.002 * _voltaje;
        }
    }


    _historico_temperaturas.append( nueva_temp );
}

void Entorno::calcularPuertaAbierta(int tiempo)
{
   if ( fmod( tiempo, _probabilidad_puerta_abierta ) == 0.0 ) {
       _puerta_abierta = true;
       qDebug() << "Puerta abierta";
   } else {
       _puerta_abierta = false;
   }
}
