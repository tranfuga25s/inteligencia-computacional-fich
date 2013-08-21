#include "neurona.h"
#include "funciones_aux.h"

Neurona::Neurona(QObject *parent, int cantidad_entradas ) :
QObject(parent)
{
    _tasa_aprendizaje = 0.25;
    _cantidad_entradas = cantidad_entradas;
    _alfa_activacion = 0;

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

void Neurona::setearTasaAprendizaje(double tasa)
{
    if( tasa > 0.0 ) {
        this->_tasa_aprendizaje = tasa;
    }
}

double Neurona::tasaAprendizaje()
{ return _tasa_aprendizaje; }

int Neurona::cantidadEntradas()
{ return _cantidad_entradas; }

double Neurona::evaluar(QVector<double> entradas)
{
    double sumatoria=0.0;

    //sumo primero el w0*x0
    sumatoria += (_pesos.at(0)*(-1.0));

    for (int i=0 ; i<entradas.size() ; i++)
    {
        sumatoria+=_pesos.at(i+1)*entradas.value(i);//entradas empieza desde 0 pero los w desde 1
    }

    return funcionActivacion(sumatoria);
}

double Neurona::funcionActivacion(double valor)
{
    /// @TODO RENATO! hacer esta función
    switch(_tipo_funcion_activacion)
    {

    case 1:
    {
        /* Signo */
        if (valor >= 0)
        {
            return 1.0;
        }
        else
        {
            return -1.0;
        }
        break;
    }
    case 2:
    {
        /* Lineal */
        if (valor >= _alfa_activacion)
        {
            return 1.0;
        }
        else
        {
            if(valor < (-1.0)*_alfa_activacion)
            {
                return -1.0;
            }
            else
            {
                return _alfa_activacion*valor;
            }
        }
        break;
    }
    case 3:
    {
        /* Sigmoidea */
        return (1 - exp(-1.0*_alfa_activacion*valor)) / (1 + exp(-1.0*_alfa_activacion*valor));
        break;
    }
    }

}


bool Neurona::entrenamiento(QVector<double> entradas, double salidaDeseada)
{
    double salida = evaluar( entradas );
    if ( salida == salidaDeseada ) {
        return true;
    } else {
        // Ajusto los pesos
        double error = salidaDeseada - salida;

        //Caso del w0 y x0. x0 siempre es -1 no importa cuantas epocas haga
        _pesos[0] = _pesos.at(0) + _tasa_aprendizaje*error*-1;

        for(int i=1 ; i<entradas.size() ; i++) {
            _pesos[i]=_pesos.at(i)+_tasa_aprendizaje*error*entradas.at(i-1);
        }

        return false;
    }
}

