#ifndef POBLACION_H
#define POBLACION_H

#include <QVector>

template<typename T> class Poblacion : public QVector<T>
{

public:

    enum MetodoSeleccion {
        Ruleta = 1,
        Ventana = 2,
        Torneo = 3
    };

    Poblacion();
    void setearTotal( int cantidad_total ) { _cantidad_total = cantidad_total; }
    int totalPoblacion() const { return _cantidad_total; }

    void setearElitismo( bool activo ) { _elitismo = activo; }
    bool elitismo() const  { return _elitismo; }

    void setearModoSeleccionPadres( Poblacion::MetodoSeleccion metodo ) { _metodo_seleccion = metodo; }
    int modoSeleccionPadres() const { return _metodo_seleccion; }

    void evaluar();
    double mejorIndividuo() const;


private:
    int _cantidad_total;
    bool _elitismo;
    MetodoSeleccion _metodo_seleccion;
    
};

#endif // POBLACION_H
