#include "enjambre_parametrico.h"

enjambre_parametrico::enjambre_parametrico(double num_part,double x_min,double x_max,double y_min,double y_max,double tolerancia)
{
    _enjambre_par.clear();

    //Limites
    _X_max = x_max;
    _X_min = x_min;
    _Y_max = y_max;
    _Y_min = y_min;

    //Particulas
    for (int i = 0; i<num_part; i++) {
        particula_parametrica Auxiliar;
        Auxiliar.inicializar(_X_min,_X_max,_Y_min,_Y_max);
        _enjambre_par.append(Auxiliar);
    }
    //mejor_y_x y _mejor_y_y inicial aleatorio
    double aleatorio = valor_random(0.0,num_part);
    _mejor_y_x.append(_enjambre_par[aleatorio].devolverPosicionX());
    _mejor_y_y.append(_enjambre_par[aleatorio].devolverPosicionY());

    //Tolerancia seteada
    _tolerancia = tolerancia;
}

int enjambre_parametrico::optimizar()
{
    //opc me indica que funcion estoy usando
    double error = 100.0;//Empieza con el maximo error asi itera

    int cant_iteraciones = 0;

    do {
        //Comparaciones
        for(int i=0 ; i<_enjambre_par.size() ; i++){

            //Actualizo la mejor de la particula
            if(evaluarFuncion(_enjambre_par[i].devolverPosicionX(),_enjambre_par[i].devolverPosicionY()) < evaluarFuncion(_enjambre_par[i].devolverMejorPosicionX(),_enjambre_par[i].devolverMejorPosicionY()) ) {
                _enjambre_par[i].setMejorPosicionX(_enjambre_par[i].devolverPosicionX());
                _enjambre_par[i].setMejorPosicionY(_enjambre_par[i].devolverPosicionY());
            }
            //Actualizo la mejor global
            if( evaluarFuncion(_enjambre_par[i].devolverMejorPosicionX(),_enjambre_par[i].devolverMejorPosicionY()) < evaluarFuncion(_mejor_y_x.last(),_mejor_y_y.last()) ) {
                _mejor_y_x.append( _enjambre_par[i].devolverMejorPosicionX() );//mejor global x
                _mejor_y_y.append( _enjambre_par[i].devolverMejorPosicionY() );//mejor global y
            }

        }
        //Actualizaciones
        for(int i = 0 ; i < _enjambre_par.size() ; i++){

            double c1 = 2.0;//Propuesto por Kennedy and Eberhart
            double c2 = 2.0;//Propuesto por Kennedy and Eberhart
            double r1_x = valor_random(0.0,1.0);
            double r2_x = valor_random(0.0,1.0);
            double r1_y = valor_random(0.0,1.0);
            double r2_y = valor_random(0.0,1.0);

            //Velocidad

            //X
            double vel_aux_x = 0.0;
            vel_aux_x = _enjambre_par[i].devolverVelocidadX()
                    + c1 * r1_x * (_enjambre_par[i].devolverMejorPosicionX() - _enjambre_par[i].devolverPosicionX())
                    + c2 * r2_x * (_mejor_y_x.last() -  _enjambre_par[i].devolverPosicionX());
            _enjambre_par[i].setearVelocidadX(vel_aux_x);

            //Y
            double vel_aux_y = 0.0;
            vel_aux_y = _enjambre_par[i].devolverVelocidadY()
                    + c1 * r1_y * (_enjambre_par[i].devolverMejorPosicionY() - _enjambre_par[i].devolverPosicionY())
                    + c2 * r2_y * (_mejor_y_y.last() -  _enjambre_par[i].devolverPosicionY());
            _enjambre_par[i].setearVelocidadY(vel_aux_y);

            //Posicion

            //X
            double pos_aux_x = 0.0;
            pos_aux_x =  _enjambre_par[i].devolverPosicionX() + _enjambre_par[i].devolverVelocidadX();


            //Y
            double pos_aux_y = 0.0;
            pos_aux_y =  _enjambre_par[i].devolverPosicionY() + _enjambre_par[i].devolverVelocidadY();

             //Controlo no sobrepasar los limites
            if ( pos_aux_x <= _X_max && pos_aux_x >= _X_min && pos_aux_y <= _Y_max && pos_aux_y >= _Y_min) {
                //Dentro de los limites
                _enjambre_par[i].setPosicionX(pos_aux_x);
                _enjambre_par[i].setPosicionY(pos_aux_y);
            }
            else
            {
                //Estrategia: Borro las particulas que se van de dominio con la correccion
                _enjambre_par.remove(i);
            }

        }

        //Porcentaje de error
        /*
         *Compruebo el tamaño de cualquiera x o y porque van a ser iguales siempre
         */
        if (_mejor_y_x.size() >= 2) {

            error = fabs( evaluarFuncion(_mejor_y_x.at(_mejor_y_x.size() - 1),_mejor_y_y.at(_mejor_y_y.size() - 1))
                          - evaluarFuncion(_mejor_y_x.at(_mejor_y_x.size() - 2),_mejor_y_y.at(_mejor_y_y.size() - 2)) )
                    / fabs( evaluarFuncion(_mejor_y_x.at(_mejor_y_x.size() - 1),_mejor_y_y.at(_mejor_y_y.size() - 1)) );

        }

        cant_iteraciones++;


    } while (error >= _tolerancia);

    return cant_iteraciones;
}

double enjambre_parametrico::evaluarFuncion(double posicion_x,double posicion_y)
{
    double valor_retorno = 0.0;

    valor_retorno = pow( pow(posicion_x,2.0) + pow(posicion_y,2.0) , 0.25)
            * ( pow(sin( 50.0 * pow( pow(posicion_x,2.0) + pow(posicion_y,2.0) , 0.1) ),2.0) + 1.0 );

    return valor_retorno;
}
