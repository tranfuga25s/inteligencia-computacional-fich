#include "neurona.h"
#include "funciones_aux.h"

Neurona::Neurona( int cantidad_entradas )
{
    _tasa_aprendizaje = 0.25;
    _cantidad_entradas = cantidad_entradas;
    _ultima_salida = 0.0;
}

void Neurona::inicializarPesos()
{
    //El termino cantidad_entradad+1 es porque reservo el lugar en el w para el bias
    for( int i = 0; i<_cantidad_entradas+1; i++ ) {
        _pesos.push_back( valor_random( -0.5, 0.5 ) );
    }
    _ultima_salida = 0.0;
}

QVector<double> Neurona::devuelvePesos()
{
    return _pesos;
}

void Neurona::seteaPesos(QVector<double> pesos)
{
     _pesos = pesos;
}

double Neurona::evaluar( QVector<double> entradas )
{
    double sumatoria=0.0;

    //sumo primero el w0*x0
    sumatoria += (_pesos.at(0)*(-1.0));

    for (int i=0 ; i<entradas.size() ; i++)
    {
        sumatoria+=_pesos.at(i+1)*entradas.at(i);//entradas empieza desde 0 pero los w desde 1
    }

    //qDebug() << sumatoria;

    _ultima_salida = funcionActivacion(sumatoria);
    return _ultima_salida;
}

