#include "enjambre.h"

enjambre::enjambre(double num_part, double x_min, double x_max, double tolerancia, RedNeuronal &red,matriz entradas ,vector salidas)
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

    //Inicializo la red con los parametros pasados
    _redpso =  &red;
    //_redpso->setearPesos(this->devuelvePosiciones());

    //Copio las salidas deseadas y las entradas para poder comparar
    _entradas = entradas;
    _salidas = salidas;

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
            _enjambre[i].setPosicion(pos_aux);

        }

        //Una vez que actualizo todas las posiciones, actualizo nuevamente los pesos de la red neuronal

        _redpso->setearPesos(this->devuelvePosiciones());

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


    } while (error >= _tolerancia);

    return cant_iteraciones;
}

double enjambre::evaluarFuncion(double posicion)
{
    //En primera instancia tendria que cargar posicion como uno de los pesos de la red y el resto dejar los que estaban
    //Guardando los pesos anteriores???

    //Hago un feedforward de la red y comparo las salidas obtenidas con las que son correctas

    QVector<int> salida_entr;
    for( int i=0; i<_salidas.size(); i++ ) {
        salida_entr.append( _redpso->mapeadorSalidas( _redpso->forwardPass( _entradas.at(i) ) ) );
    }
    int errores = 0;
    for(int i=0;i<_salidas.size();i++) {
        if ( _salidas.at(i) != salida_entr.at(i) ) {
            errores++;
        }
    }

    return errores;
}

//!
//! \brief enjambre::devuelvePosiciones
//! Va a devolver todas las posiciones en un vector para luego ponerlas como peso en una red neuronal
//! \return
//!

QVector<double> enjambre::devuelvePosiciones()
{
    QVector<double> Auxiliar;

    for (int i = 0; i<_enjambre.size() ; i++) {
        Auxiliar.append(_enjambre[i].devolverPosicion());
    }

    return Auxiliar;
}
