#include "enjambre.h"

enjambre::enjambre(double num_part, double x_min, double x_max, double tolerancia)
{
    //Particulas
    for (int i = 0; i<num_part; i++) {
        _enjambre[i].inicializar(x_min,x_max);
    }
    //Mejor posicion Global
    _mejor_y = -1.0;
    //Tolerancia seteada
    _tolerancia = tolerancia;
}

void enjambre::optimizar()
{
    do {
        //Comparaciones
        for(int i=0 ; i<_enjambre.size() ; i++){

            //Actualizo la mejor de la particula
            if(evaluarFuncion(_enjambre[i].devolverPosicion()) < evaluarFuncion(_enjambre[i].devolverMejorPosicion()) ) {
                _enjambre[i].setMejorPosicion(_enjambre[i].devolverPosicion());
            }
            //Actualizo la mejor global
            if( evaluarFuncion(_enjambre[i].devolverMejorPosicion()) < evaluarFuncion(_mejor_y)) {
                _mejor_y = _enjambre[i].devolverMejorPosicion();
            }

        }
        //Actualizaciones
        for(int i = 0 ; i < _enjambre.size() ; i++){

            double c1,c2;//???
            double r1 = valor_random(0.0,1.0);
            double r2 = valor_random(0.0,1.0);

            //Velocidad
            double vel_aux = 0.0;
            vel_aux = _enjambre[i].devolverVelocidad()
                    + c1 * r1 * (_enjambre[i].devolverMejorPosicion() - _enjambre[i].devolverPosicion())
                    + c2 * r2 * (_mejor_y -  _enjambre[i].devolverPosicion());
            _enjambre[i].setearVelocidad(vel_aux);

            //Posicion
            double pos_aux = 0.0;
            pos_aux =  _enjambre[i].devolverPosicion() + _enjambre[i].devolverVelocidad();
            _enjambre[i].setPosicion(pos_aux);

        }

    } while (evaluarFuncion(_mejor_y) <= _tolerancia);//???
}

double enjambre::evaluarFuncion(double posicion)
{
    //Seria la funcion a minimizar
}
