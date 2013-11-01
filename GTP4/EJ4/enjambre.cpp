#include "enjambre.h"

enjambre::enjambre(double num_part, double x_min, double x_max, double tolerancia,int max_iteraciones, RedNeuronal *red, matriz entradas , vector salidas)
{
    _enjambre.clear();

    //Limites
    _X_max = x_max;
    _X_min = x_min;

    //Particulas
    for (int i = 0; i<num_part; i++) {
        Particula Auxiliar;
        Auxiliar.inicializar(_X_min,_X_max,num_part);
        _enjambre.append(Auxiliar);
    }
    //mejor_y inicial aleatorio
    _mejores_pesos_globales.append(_enjambre[valor_random(0.0,num_part)].devolverPesos());

    //Tolerancia seteada
    _tolerancia = tolerancia;

    //Maximo de iteraciones permitidas
    _max_iter = max_iteraciones;

    //Inicializo la red con los parametros pasados
    _redpso =  red;

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
            if(evaluarFuncion(_enjambre[i].devolverPesos()) < evaluarFuncion(_enjambre[i].devolverMejoresPesos()) ) {
                _enjambre[i].setMejoresPesos(_enjambre[i].devolverPesos());
            }
            //Actualizo la mejor global
            if( evaluarFuncion(_enjambre[i].devolverMejoresPesos()) < evaluarFuncion(_mejores_pesos_globales.last()) ) {
                _mejores_pesos_globales.append( _enjambre[i].devolverMejoresPesos() );//Guardo todos los mejores y
            }

        }
        //Actualizaciones
        for(int i = 0 ; i < _enjambre.size() ; i++){

            QVector<double> vel_aux;
            QVector<double> pos_aux;

            for(int j=0 ; j< _enjambre[i].cantPesos() ; j++) {

                double c1 = 2.0;//Propuesto por Kennedy and Eberhart
                double c2 = 2.0;//Propuesto por Kennedy and Eberhart
                double r1 = valor_random(0.0,1.0);
                double r2 = valor_random(0.0,1.0);

                //Velocidad
                vel_aux.append(_enjambre[i].devolverVelocidad().at(j)
                        + c1 * r1 * (_enjambre[i].devolverMejoresPesos().at(j) - _enjambre[i].devolverPesos().at(j))
                        + c2 * r2 * (_mejores_pesos_globales.last().at(j) -  _enjambre[i].devolverPesos().at(j)) );

                _enjambre[i].setearVelocidad(vel_aux[j],j);

                //Posicion
                pos_aux.append( _enjambre[i].devolverPesos().at(j) + _enjambre[i].devolverVelocidad().at(j) );
                _enjambre[i].setPesos(pos_aux[j],j);
            }
        }

        //Una vez que actualizo todas los pesos en las partuculas, los copio red neuronal

        _redpso->setearPesos(_mejores_pesos_globales.last());

        //Porcentaje de error
        /*
         *Lo que estaria haciendo aca seria calcular el error en base a como varia la funcion
         *desde el ultimo _mejor_y y el anterior _mejor_y a ese
         */
        if (_mejores_pesos_globales.size() >= 2) {

            error = fabs( evaluarFuncion(_mejores_pesos_globales.at(_mejores_pesos_globales.size() - 1)) - evaluarFuncion(_mejores_pesos_globales.at(_mejores_pesos_globales.size() - 2)))
                    / fabs( evaluarFuncion(_mejores_pesos_globales.at(_mejores_pesos_globales.size() - 1)));

        }

        cant_iteraciones++;


    } while (error >= _tolerancia && cant_iteraciones < _max_iter);

    return cant_iteraciones;
}

double enjambre::evaluarFuncion(QVector<double> pesos)
{
    //Hago un feedforward de la red con los pesos que recive la funcion

    _redpso->setearPesos(pesos);

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

