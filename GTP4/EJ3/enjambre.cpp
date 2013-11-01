#include "enjambre.h"

enjambre::enjambre(double num_part, double x_min, double x_max, double tolerancia, int opc)
{
    _enjambre.clear();

    //Limites
    _X_max = x_max;
    _X_min = x_min;

    //Particulas
    for (int i = 0; i<num_part; i++) {
        Particula Auxiliar;
        Auxiliar.inicializar(_X_min,_X_max);
        _enjambre.append(Auxiliar);
    }
    //mejor_y inicial aleatorio
    _mejor_y.append(_enjambre[valor_random(0.0,num_part)].devolverPosicion());

    //Tolerancia seteada
    _tolerancia = tolerancia;

    //Opcion de funcion a evaluar
    _opc = opc;
}

int enjambre::optimizar()
{
    //opc me indica que funcion estoy usando
    double error = 100.0;//Empieza con el maximo error asi itera

    int cant_iteraciones = 0;
    do {
        //Comparaciones
        for(int i=0 ; i<_enjambre.size() ; i++){

            //Actualizo la mejor de la particula
            if(evaluarFuncion(_enjambre[i].devolverPosicion()) < evaluarFuncion(_enjambre[i].devolverMejorPosicion()) ) {
                _enjambre[i].setMejorPosicion(_enjambre[i].devolverPosicion());
            }
            //Actualizo la mejor global
            if( evaluarFuncion(_enjambre[i].devolverMejorPosicion()) < evaluarFuncion(_mejor_y.last()) ) {
                _mejor_y.append( _enjambre[i].devolverMejorPosicion() );//Guardo todos los mejores y
            }

        }
        //Actualizaciones
        for(int i = 0 ; i < _enjambre.size() ; i++){

            double c1 = 2.0;//Propuesto por Kennedy and Eberhart
            double c2 = 2.0;//Propuesto por Kennedy and Eberhart
            double r1 = valor_random(0.0,1.0);
            double r2 = valor_random(0.0,1.0);

            //Velocidad
            double vel_aux = 0.0;
            vel_aux = _enjambre[i].devolverVelocidad()
                    + c1 * r1 * (_enjambre[i].devolverMejorPosicion() - _enjambre[i].devolverPosicion())
                    + c2 * r2 * (_mejor_y.last() -  _enjambre[i].devolverPosicion());

            //controlo que la velocidad no supere vmax = (x_max - x_min)
            double vMax = _X_max - _X_min;
            if(vel_aux < vMax) {
               _enjambre[i].setearVelocidad(vel_aux);
            }
            else
            {
                _enjambre[i].setearVelocidad(vMax);
            }

            //Posicion
            double pos_aux = 0.0;
            pos_aux =  _enjambre[i].devolverPosicion() + _enjambre[i].devolverVelocidad();
            //Controlo que no se vaya de dominio
            if(pos_aux >= _X_min && pos_aux <= _X_max) {
                //En Dominio
                _enjambre[i].setPosicion(pos_aux);
            }
            else
            {
                if(pos_aux <= _X_min) {
                    //Es menor
                    _enjambre[i].setPosicion(_X_min);
                }
                else
                {
                    //Es mayor
                    _enjambre[i].setPosicion(_X_max);
                }
            }


        }

        //Porcentaje de error
        /*
         *Lo que estaria haciendo aca seria calcular el error en base a como varia la funcion
         *desde el ultimo _mejor_y y el anterior _mejor_y a ese
         */
        if (_mejor_y.size() >= 2) {

            error = fabs( evaluarFuncion(_mejor_y.at(_mejor_y.size() - 1)) - evaluarFuncion(_mejor_y.at(_mejor_y.size() - 2)) )
                    / fabs( evaluarFuncion(_mejor_y.at(_mejor_y.size() - 1)) );

        }

        cant_iteraciones++;


    } while (error >= _tolerancia); //Agregar el control de maximo de iteraciones

    return cant_iteraciones;
}

double enjambre::evaluarFuncion(double posicion)
{
    //La opcion indica cual de la funciones se evaluaria
    double valor_retorno = 0.0;
    switch (_opc) {
    case 1:
        //Funcion 1
        valor_retorno = -1.0 * posicion * sin( sqrt( fabs( posicion ) ) );
        break;
    case 2:
        //Funcion 2
        valor_retorno = posicion + 5.0 * sin( 3.0 * posicion ) + 8.0 * cos( 5.0 * posicion );
        break;
    }

    return valor_retorno;
}
