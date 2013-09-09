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
        _var_pesos_ant.push_back(0.0);
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
        sumatoria+=_pesos.at(i+1)*entradas.value(i);//entradas empieza desde 0 pero los w desde 1
    }

    //qDebug() << sumatoria;

    _ultima_salida = funcionActivacion(sumatoria);
    return _ultima_salida;
}



void Neurona::ajustarPesos( QVector<double> entradas )
{

    double pesocero = _pesos[0];

    //Caso del w0 y x0. x0 siempre es -1 no importa cuantas epocas haga
    _pesos[0] = _pesos.at(0) + _tasa_aprendizaje*_delta*(-1.0) + _momento*_var_pesos_ant.at(0);

    _var_pesos_ant[0] = pesocero;

    for(int i=1 ; i<=entradas.size() ; i++) {
        double temporal = _pesos[i]; // Guardo el valor para setearlo despues

        _pesos[i]=_pesos.at(i) + _tasa_aprendizaje*_delta*entradas.at(i-1) + _momento*_var_pesos_ant.at(i);

        //_var_pesos_ant[i] = _tasa_aprendizaje*_delta*entradas.at(i-1); //Actualizo el vector
        _var_pesos_ant[i] = temporal; // Guardo el peso anterior como nuevo peso anterior
    }

}

