#include "neurona.h"
#include "funciones_aux.h"

Neurona::Neurona(QObject *parent, int cantidad_entradas ) :
QObject(parent)
{
    _tasa_aprendizaje = 0.25;
    _cantidad_entradas = cantidad_entradas;

}

void Neurona::inicializarPesos()
{
    //El termino cantidad_entradad+1 es porque reservo el lugar en el w para el bias
    for( int i = 0; i<_cantidad_entradas+1; i++ ) {
        _pesos.push_back( valor_random( -0.5, 0.5 ) );
    }
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

    return funcionActivacion(sumatoria);
}

double Neurona::funcionActivacion(double valor)
{
    /* Signo */
    if (valor >= 0.0)
    {
        return 1.0;
    }
    else
    {
        return -1.0;
    }

}


double Neurona::entrenamiento(QVector<double> entradas, double salidaDeseada)
{
    double salida = evaluar( entradas );

    if ( salida == salidaDeseada ) {
        return 0.0;
    } else {
        // Ajusto los pesos
        double error = salidaDeseada - salida;

        //Caso del w0 y x0. x0 siempre es -1 no importa cuantas epocas haga
        _pesos[0] = _pesos.at(0) + _tasa_aprendizaje*error*(-1.0);

        for(int i=1 ; i<=entradas.size() ; i++) {
            _pesos[i]=_pesos.at(i) + _tasa_aprendizaje*error*entradas.at(i-1);
        }

        return error;
    }
}

