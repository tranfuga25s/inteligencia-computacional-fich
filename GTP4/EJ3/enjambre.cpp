#include "enjambre.h"

enjambre::enjambre(double num_part, double x_min, double x_max, double tolerancia)
{
    //Particulas
    for (int i = 0; i<num_part; i++) {
        _enjambre[i].inicializar(x_min,x_max);
    }
    //Tolerancia seteada
    _tolerancia = tolerancia;
}

void enjambre::optimizar()
{
    double error = 0.0;

    do {
        //Comparaciones
        for(int i=0 ; i<_enjambre.size() ; i++){

            //Actualizo la mejor de la particula
            if(evaluarFuncion(_enjambre[i].devolverPosicion()) < evaluarFuncion(_enjambre[i].devolverMejorPosicion()) ) {
                _enjambre[i].setMejorPosicion(_enjambre[i].devolverPosicion());
            }
            //Actualizo la mejor global
            if( evaluarFuncion(_enjambre[i].devolverMejorPosicion()) < evaluarFuncion(_mejor_y.last())) {
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
            _enjambre[i].setearVelocidad(vel_aux);

            //Posicion
            double pos_aux = 0.0;
            pos_aux =  _enjambre[i].devolverPosicion() + _enjambre[i].devolverVelocidad();
            _enjambre[i].setPosicion(pos_aux);

        }

        //Porcentaje de error
        /*
         *Lo que estaria haciendo aca seria calcular el error en base a como varia la funcion
         *desde el ultimo _mejor_y y el anterior _mejor_y a ese
         */
        error = 0.0;
        error = fabs(evaluarFuncion(_mejor_y[_mejor_y.size() - 1]) - evaluarFuncion(_mejor_y[_mejor_y.size() - 2]) )
                / fabs( evaluarFuncion(_mejor_y[_mejor_y.size() - 1]) );

    } while (error < _tolerancia);
}

double enjambre::evaluarFuncion(double posicion)
{
    //Seria la funcion a minimizar
}
