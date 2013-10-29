#ifndef POBLACION_H
#define POBLACION_H

#include <QVector>
#include "evaluador.h"

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

    void evaluarPoblacion();
    void seleccionarPadres();

private:
    int _cantidad_total;
    bool _elitismo;
    double _mejor_fitness;
    int _pos_mejor_fitness;
    MetodoSeleccion _metodo_seleccion;

    QVector<double> _fitness;
    QVector<bool> _no_eliminar;

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
}

template<typename T>
void Poblacion<T>::setearTotal( int cantidad_total )
{
    _cantidad_total = cantidad_total;
    _fitness.reserve( _cantidad_total );
}

template<typename T>
void Poblacion<T>::evaluarPoblacion()
{
    // recorro todo el vector y veo cual es el mejor valor
    for( int i=0; i<this->size(); i++ ) {
        double temp = evaluar( this->at( i ).getX() );
        if( temp > _mejor_fitness ) {
            _mejor_fitness = temp;
            _pos_mejor_fitness = i;
        }
        _fitness[i] = temp;
    }
}

template<typename T>
void Poblacion<T>::seleccionarPadres()
{
    // inicializo el vector de posiciones a no tocar
    for( int i=0; i<this->size(); i++ ) {
        _no_eliminar[i]=false;
    }

    // Me aseguro el elitismo para cualquier metodo
    if( _elitismo ) {
        _no_eliminar[_pos_mejor_fitness]=true;
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
}

template<typename T>
void Poblacion<T>::ventaneo()
{
}

template<typename T>
void Poblacion<T>::torneo()
{
}

#endif // POBLACION_H
