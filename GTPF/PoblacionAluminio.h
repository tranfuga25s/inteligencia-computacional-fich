#ifndef POBLACIONALUMINIO_H
#define POBLACIONALUMINIO_H

#include <QVector>
#include <QMap>
#include <QtConcurrentMap>
#include <cfloat>

#include "funciones_aux.h"

#include "GenomaAluminio.h"

class PoblacionAluminio : public QVector<GenomaAluminio>
{

public:

    enum MetodoSeleccion {
        Ruleta = 1,
        Ventana = 2,
        Torneo = 3
    };

    PoblacionAluminio();

    void setearTotal( int cantidad_total );
    int totalPoblacion() const { return _cantidad_total; }

    void setearElitismo( bool activo ) { _elitismo = activo; }
    bool elitismo() const  { return _elitismo; }

    void setearModoSeleccionPadres( MetodoSeleccion metodo ) { _metodo_seleccion = metodo; }
    int modoSeleccionPadres() const { return _metodo_seleccion; }

    double mejorFitnes() const { return _mejor_fitness; }
    GenomaAluminio elementoMinimo() { return this->at( _pos_mejor_fitness ); }

    void setearBrechaGeneracional( double valor ) { _brecha_generacional = valor; }
    double brechaGeneracional() const { return _brecha_generacional; }

    void setearProbabilidadMutacion( int valor ) { _probabilidad_mutacion = valor; }
    int probabilidadMutacion() { return _probabilidad_mutacion; }

    void setearProbabilidadCruza( int valor ) { _probabilidad_cruza = valor; }
    int probabilidadCruza() { return _probabilidad_cruza; }

    void setearPorcentajeCantidadDePadres( double valor ) { _cantidad_padres = valor; }
    int  cantidadDePadres() { return floor( _cantidad_total * _cantidad_padres ); }

    void setearMinMax( double min, double max ) { _min = min; _max = max; }

    double minimoFitness() const { return _minimo_fitness; }
    double maximoFitness() const { return _maximo_fitness; }

    void evaluarPoblacion();
    void seleccionarPadres();
    void generarHijos();

private:
    int _cantidad_total;

    double _mejor_fitness;
    double _minimo_fitness;
    double _maximo_fitness;
    int _pos_mejor_fitness;

    MetodoSeleccion _metodo_seleccion;
    bool _elitismo;
    double _brecha_generacional;
    double _cantidad_padres;
    int _probabilidad_mutacion;
    int _probabilidad_cruza;

    //Rango
    double _max;
    double _min;

    QVector<double> _fitness;
    QVector<GenomaAluminio> _nuevos_padres;

    void ruleta();
    void ventaneo();
    void torneo();

};

PoblacionAluminio::PoblacionAluminio() : QVector<GenomaAluminio>()
{
    _elitismo = false;
    _cantidad_total = 0.0;
    _metodo_seleccion = Ruleta;
    _mejor_fitness = 0.0;
    _pos_mejor_fitness = -1;
    _probabilidad_mutacion = 0;
    _min = 0.0;
    _max = 0.0;
    _maximo_fitness = 0.0;
    _minimo_fitness = 0.0;
}


void PoblacionAluminio::setearTotal( int cantidad_total )
{
    _cantidad_total = cantidad_total;
    _fitness.resize( _cantidad_total );
}

void PoblacionAluminio::evaluarPoblacion()
{
    _fitness.clear();
    _fitness.resize( this->size() );
    _mejor_fitness = (-1.0)*DBL_MAX;
    _maximo_fitness = (-1.0)*DBL_MAX;
    _minimo_fitness = DBL_MAX;

    _fitness = QtConcurrent::blockingMapped<QVector<double> >( *this, evaluarAluminio );

    // recorro todo el vector y veo cual es el mejor valor
    for( int i=0; i<this->size(); i++ ) {
        double temp = _fitness.at( i );
        // VEO QUE ESTÉ BIEN ESTA FUNCION!
//        temp = (-1.0)*temp;                                /// fit = -y
        //qDebug() << "Fitness:" << temp;
        if( temp > _mejor_fitness ) {
            _mejor_fitness = temp;
            //qDebug() << "Mejor Fitnes: " << _mejor_fitness;
            _pos_mejor_fitness = i;
        }
        if( temp < _minimo_fitness ) {
            _minimo_fitness = temp;
        }
        if( temp >= _maximo_fitness ) {
            _maximo_fitness = temp;
        }
        _fitness[i] = temp;
    }
    if( _pos_mejor_fitness == -1 ) {
        abort();
    }
}



void PoblacionAluminio::seleccionarPadres()
{
    // inicializo el vector de padres a utilizar
    _nuevos_padres.clear();

    // Me aseguro el elitismo para cualquier metodo
    if( _elitismo ) {
        _nuevos_padres.append( this->at( _pos_mejor_fitness ) );
        //this->remove( _pos_mejor_fitness );
        //_fitness.remove( _pos_mejor_fitness );
        _pos_mejor_fitness = -1;
    }

    // Recorro el vector y selecciono segun el metodo elegido
    switch( _metodo_seleccion ) {
        case Ruleta:  { this->ruleta();   break; }
        case Ventana: { this->ventaneo(); break; }
        case Torneo:  { this->torneo();   break; }
    }
}


void PoblacionAluminio::ruleta()
{
    QVector<double> _probabilidades( this->size() );

    // Busco el maximo y minimo de los fitnes
    double minimo = DBL_MAX;
    double maximo = (-1.0)*DBL_MAX;
    for( int i=0; i<this->size(); i++ ) {
        if( _fitness.at( i ) < minimo ) {
            minimo = _fitness.at(i);
        }
        if( _fitness[i] > maximo ) {
            maximo = _fitness.at(i);
        }
    }

    int tam_nueva_generacion = this->cantidadDePadres();

    for( int j=0; j<tam_nueva_generacion; j++ ) {

        // Genero la escala para la ruleta y las probabilidades de cada uno
        _probabilidades.clear();
        _probabilidades.resize( this->size() );
        for( int i=0; i<this->size(); i++ ) {
            _probabilidades[i] = ( _fitness[i] - minimo ) / ( maximo - minimo ); // Interpolacion
        }

        // Armo el vector de indices de la ruleta
        QVector<int> ruleta( this->size() );
        for( int i=0; i<_probabilidades.size(); i++ ) {
            // Calculo cuantos elementos de la ruleta le corresponden
            int cant = floor( _probabilidades.at( i ) / 100 );
            // Lleno la ruleta con los indices
            for( int j=0; j<cant; j++ ) {
                ruleta.append( i );
            }

        }

        int azar = valor_random_int( 0, ruleta.size() );

        // Coloco el seleccionado en la población de padres
        _nuevos_padres.append( this->at( azar ) );
        // Lo elimino de la poblacion actual para rehacer el sistema actual
        //this->remove( azar );
        //_fitness.remove( azar );

    }
}

void PoblacionAluminio::ventaneo()
{
    int tam_nueva_generacion = this->cantidadDePadres();

    for( int j=0; j<tam_nueva_generacion; j++ ) {

        // Hago un mapa que me ordene los datos de fitness de cada uno
        // El mapa contiene el fitnes y la posicion en el vector
        // El mapa al estar implementado como un arbol, se auto ordena al insertar elementos.
        QMap<double,int> orden;
        for( int i=0; i<this->size(); i++ ) {
            orden.insertMulti( _fitness.at(i), i );
        }

        // Calculo el tamaño de la ventana a utilizar
        int tam_ventana = ( this->size() - ( j * ( this->size() / tam_nueva_generacion ) ) );

        int azar = valor_random_int( 0, tam_ventana );


        // La lista esta ordenada en ascendente, o sea que el fitnes mayor está en las utlimas posiciones
        QList<int> indices_ordenados = orden.values();
        int pos_actual = indices_ordenados.at( indices_ordenados.size() - azar -1 );

        // Agrego la posicion al vector de padres
        _nuevos_padres.append( this->at( pos_actual ) );

        // Saco el elemento sacado de la lista de orden
        //orden.remove( indices_ordenados.at( indices_ordenados.size() - azar -1 ) );

        // lo elimino de los proximos candidatos
        //this->remove( pos_actual );
        // Elimino su fitness
        //_fitness.remove( pos_actual );

    }

}


void PoblacionAluminio::torneo()
{
    int tam_nueva_generacion = this->cantidadDePadres();

    // Elijo cuatro participantes y los hago competir
    QMap<double,int> mposiciones;
    for( int i=0; i<this->size(); i++ ) {
        mposiciones.insertMulti( _fitness.at(i), i );
    }
    QList<int> posiciones = mposiciones.values(); // Valores ordenados

    for( int j=0; j<tam_nueva_generacion; j++ ) {

        int p = valor_random( 0, posiciones.size() );
        int pos1 = posiciones.value( p );
        //posiciones.remove( p );
        p = valor_random( 0, posiciones.size() );
        int pos2 = posiciones.value( p );
        //posiciones.remove( p );
        p = valor_random( 0, posiciones.size() );
        int pos3 = posiciones.value( p );
        //posiciones.remove( p );
        p = valor_random( 0, posiciones.size() );
        int pos4 = posiciones.value( p );
        posiciones.clear();

        int ganador1 = 0;
        int ganador2 = 0;

        if( _fitness.at( pos1 ) > _fitness.at( pos2 ) ) {
            ganador1 = pos1;
        } else {
            ganador1 = pos2;
        }
        if( _fitness.at( pos3 ) > _fitness.at( pos4 ) ) {
            ganador2 = pos3;
        } else {
            ganador2 = pos4;
        }
        int ganador = 0;
        if( _fitness.at( ganador1 ) > _fitness.at( ganador2 ) ) {
            ganador = ganador1;
        } else {
            ganador = ganador2;
        }

        // lo coloco con los padres
        _nuevos_padres.append( this->at( ganador ) );
        // Lo elimino de los elementos actuale
        //this->remove( ganador );
        // Elimino su fitness
        //_fitness.remove( ganador );

    }
}


void PoblacionAluminio::generarHijos()
{

    this->clear();
    _pos_mejor_fitness = -1;

    if( _elitismo ) {
        this->append( _nuevos_padres.at( 0 ) );
        _pos_mejor_fitness = 0;
        _mejor_fitness = evaluarAluminio( this->at( 0 ) );
    }

    // Genero la brecha generacional copiando los padres para convervar las buenas soluciones
    int brecha = floor( this->_cantidad_total * this->_brecha_generacional );
    if( brecha > _nuevos_padres.size() ) {
        brecha = _nuevos_padres.size();
    }
    for( int i=0; i<brecha; i++ ) {
        this->append( _nuevos_padres.at( i ) );
    }

    while( this->size() < _cantidad_total ) {


        int p1 = valor_random_int( 0, _nuevos_padres.size() );
        int p2 = valor_random_int( 0, _nuevos_padres.size() );
        while( p1 == p2 ) {
            p2 = valor_random_int( 0, _nuevos_padres.size() );
        }


        GenomaAluminio hijo1 = _nuevos_padres.at( p1 );
        GenomaAluminio hijo2 = _nuevos_padres.at( p2 );

        //CRUZAS

        int  prob0 = valor_random_int( 0, 100 );

        if( prob0 != 0 && prob0 <=  _probabilidad_cruza ) {
            //Hay Cruza
            cruza( hijo1, hijo2 );
            //qDebug() << "cruza";
        }

        //En el caso de que no haya cruza podria dejar los mismos padres y listo?

        int  prob1 = valor_random_int( 0, 100 );
        int  prob2 = valor_random_int( 0, 100 );


        //MUTACIONES
        if( prob1 != 0 && prob1 <= _probabilidad_mutacion ) {
            mutar( hijo1 );
            //qDebug() << "mutacion";
        }
        if( prob2 != 0 && prob2 <= _probabilidad_mutacion ) {
            mutar( hijo2 );
            //qDebug() << "mutacion";
        }

        this->append( hijo1 );
        this->append( hijo2 );

    }
}

#endif // POBLACIONALUMINIO_H
