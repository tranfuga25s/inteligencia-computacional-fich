#ifndef POBLACION_H
#define POBLACION_H

#include <QVector>
#include <QMap>
//#include "evaluador.h"
#include <cfloat>
#include "funciones_aux.h"

template<typename T> class Poblacion : public QVector<T>
{

public:

    enum MetodoSeleccion {
        Ruleta = 1,
        Ventana = 2,
        Torneo = 3
    };

    Poblacion();

    void setearTotal( int cantidad_total );
    int totalPoblacion() const { return _cantidad_total; }

    void setearElitismo( bool activo ) { _elitismo = activo; }
    bool elitismo() const  { return _elitismo; }

    void setearModoSeleccionPadres( Poblacion::MetodoSeleccion metodo ) { _metodo_seleccion = metodo; }
    int modoSeleccionPadres() const { return _metodo_seleccion; }

    double mejorFitnes() const { return _mejor_fitness; }
    double posicionMinimo() { return this->at(_pos_mejor_fitness).getX(); }

    double posicionMinimoX() { return this->at( _pos_mejor_fitness ).getX(); }
    double posicionMinimoY() { return this->at( _pos_mejor_fitness ).getY(); }

    void setearBrechaGeneracional( double valor ) { _brecha_generacional = valor; }
    double brechaGeneracional() const { return _brecha_generacional; }

    void setearProbabilidadMutacion( int valor ) { _probabilidad_mutacion = valor; }
    int probabilidadMutacion() { return _probabilidad_mutacion; }

    void setearPorcentajeCantidadDePadres( double valor ) { _cantidad_padres = valor; }
    int  cantidadDePadres() { return floor( _cantidad_total * _cantidad_padres ); }

    void setearMinMax( double min, double max ) { _min = min; _max = max; }

    void evaluarPoblacion();
    void seleccionarPadres();
    void generarHijos();

private:
    int _cantidad_total;

    double _mejor_fitness;
    int _pos_mejor_fitness;

    MetodoSeleccion _metodo_seleccion;
    bool _elitismo;
    double _brecha_generacional;
    double _cantidad_padres;
    int _probabilidad_mutacion;

    double _max;
    double _min;

    QVector<double> _fitness;
    QVector<T> _nuevos_padres;

    void ruleta();
    void ventaneo();
    void torneo();
    
};

template<typename T>
Poblacion<T>::Poblacion() : QVector<T>()
{
    _elitismo = false;
    _cantidad_total = 0.0;
    _metodo_seleccion = Ruleta;
    _mejor_fitness = 0.0;
    _pos_mejor_fitness = -1;
    _probabilidad_mutacion = 0;
    _min = 0.0;
    _max = 0.0;
}

template<typename T>
void Poblacion<T>::setearTotal( int cantidad_total )
{
    _cantidad_total = cantidad_total;
    _fitness.resize( _cantidad_total );
}

template<typename T>
void Poblacion<T>::evaluarPoblacion()
{
    _fitness.clear();
    _fitness.resize( this->size() );
    _mejor_fitness = (-1.0)*DBL_MAX;
    // recorro todo el vector y veo cual es el mejor valor
    for( int i=0; i<this->size(); i++ ) {
        double temp = evaluar( this->at( i ) );
        // VEO QUE ESTÉ BIEN ESTA FUNCION!
        temp = (-1.0)*temp;                                /// fit = -y
        //
        if( temp > _mejor_fitness ) {
            _mejor_fitness = temp;
            _pos_mejor_fitness = i;
        }
        _fitness[i] = temp;
    }
    if( _pos_mejor_fitness == -1 ) {
        abort();
    }
}

template<typename T>
void Poblacion<T>::seleccionarPadres()
{
    // inicializo el vector de padres a utilizar
    _nuevos_padres.clear();

    // Me aseguro el elitismo para cualquier metodo
    if( _elitismo ) {
        _nuevos_padres.append( this->at( _pos_mejor_fitness ) );
        this->remove( _pos_mejor_fitness );
        _fitness.remove( _pos_mejor_fitness );
        _pos_mejor_fitness = -1;
    }

    // Recorro el vector y selecciono segun el metodo elegido
    switch( _metodo_seleccion ) {
        case Ruleta:  { this->ruleta();   break; }
        case Ventana: { this->ventaneo(); break; }
        case Torneo:  { this->torneo();   break; }
    }
}

template<typename T>
void Poblacion<T>::ruleta()
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
        this->remove( azar );
        _fitness.remove( azar );

    }


}

template<typename T>
void Poblacion<T>::ventaneo()
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
        orden.remove( indices_ordenados.at( indices_ordenados.size() - azar -1 ) );

        // lo elimino de los proximos candidatos
        this->remove( pos_actual );
        // Elimino su fitness
        _fitness.remove( pos_actual );

    }

}

template<typename T>
void Poblacion<T>::torneo()
{
    int tam_nueva_generacion = this->cantidadDePadres();

    for( int j=0; j<tam_nueva_generacion; j++ ) {

        // Elijo cuatro participantes y los hago competir
        QMap<double,int> mposiciones;
        for( int i=0; i<this->size(); i++ ) {
            mposiciones.insertMulti( _fitness.at(i), i );
        }
        QList<int> posiciones = mposiciones.values(); // Valores ordenados

        int p = valor_random( 0, posiciones.size() );
        int pos1 = posiciones.takeAt( p );
        //posiciones.remove( p );
        p = valor_random( 0, posiciones.size() );
        int pos2 = posiciones.takeAt( p );
        //posiciones.remove( p );
        p = valor_random( 0, posiciones.size() );
        int pos3 = posiciones.takeAt( p );
        //posiciones.remove( p );
        p = valor_random( 0, posiciones.size() );
        int pos4 = posiciones.takeAt( p );
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
        this->remove( ganador );
        // Elimino su fitness
        _fitness.remove( ganador );

    }
}

template<typename T>
void Poblacion<T>::generarHijos()
{

    this->clear();
    _pos_mejor_fitness = -1;

    if( _elitismo ) {
        this->append( _nuevos_padres.at( 0 ) );
        _pos_mejor_fitness = 0;
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

        T hijo1 = _nuevos_padres.at( p1 );
        T hijo2 = _nuevos_padres.at( p2 );

        cruza( hijo1, hijo2 );

        int  prob1 = valor_random_int( 0, 100 );
        int  prob2 = valor_random_int( 0, 100 );

        if( prob1 != 0 && prob1 % ( 100 - _probabilidad_mutacion ) == 0 ) {
            mutar( hijo1 );
            //qDebug() << "mutacion";
        }
        if( prob2 != 0 && prob2 % ( 100 - _probabilidad_mutacion ) == 0 ) {
            mutar( hijo2 );
            //qDebug() << "mutacion";
        }

        if( hijo1.getX() >= _min && hijo1.getX() <= _max ) {
            this->append( hijo1 );
        }
        if( hijo2.getX() >= _min && hijo2.getX() <= _max ) {
            this->append( hijo2 );
        }
    }
}

#endif // POBLACION_H
