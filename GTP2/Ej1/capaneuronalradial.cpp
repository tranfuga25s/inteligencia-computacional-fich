#include <QVector>
#include "capaneuronalradial.h"

CapaNeuronalRadial::CapaNeuronalRadial( int cantidad_neuronas, int cantidad_entradas, int cantidad_clases )
{
    if( cantidad_neuronas != 0 ) {
        _neuronas = new QVector<NeuronaRadial>();
        _neuronas->reserve( cantidad_neuronas );
        for( int i=0; i<cantidad_neuronas; i++ ) {
            _neuronas->insert( i, NeuronaRadial( cantidad_entradas ) );
        }
        _patrones_clase = new QVector< QList<vector> >( cantidad_clases );
    }
}

void CapaNeuronalRadial::setearTasaAprendizaje( double )
{
    return;
}

void CapaNeuronalRadial::setearMomento( double )
{
    return;
}

QVector<double> CapaNeuronalRadial::getSalidas( vector entrada )
{
    QVector<double> temp;
    for( int i=0; i<_neuronas->size(); i++ ) {
        temp.append( _neuronas->operator []( i ).getSalida( entrada ) );
    }
    return temp;
}

/*!
 * \brief CapaNeuronalRadial::buscarCentroides
 * \param _datos_originales
 */
void CapaNeuronalRadial::buscarCentroides( QVector<vector> &_datos_originales )
{
    int datos_por_conjunto = floor( _datos_originales.size() / _cantidad_clases );

    for( int i = 0; i<_cantidad_clases; i ++ ) {

        for( int j = 0; j<datos_por_conjunto; j++ ) {
            _patrones_clase->operator []( i ).append( _datos_originales.first() );
            _datos_originales.pop_front();
        }

    }

    for( int nr = 0; nr < _neuronas->size(); nr++ ) {

        _neuronas->operator [] (nr).recalcularCentroide( _patrones_clase->at( nr ) );

    }

    bool hubo_cambio = true; // para que entre al while

    while( hubo_cambio ) {

        hubo_cambio = false;

        QVector< QList<vector> >::iterator clase;
        for( clase = _patrones_clase->begin(); clase != _patrones_clase->end(); ++clase ) {

            QList<vector>::iterator p;
            for( p = clase->begin(); p != clase->end(); ++p ) {

                double distancia_minima = 0;
                int clase_elegida = -1;

                // Busco que centroide tiene mas cerca
                for( int nr = 0; nr < _neuronas->size(); nr ++ ) {

                    double nuevo = _neuronas->operator []( nr ).distanciaCentroide( *p );
                    if( nuevo <= distancia_minima ) {
                        distancia_minima = nuevo;
                        clase_elegida = nr;
                    }

                }

                // Cambio el patron de lugar si corresponde
                if( _patrones_clase->indexOf( *clase ) != clase_elegida ) {
                    // Muevo el patron a la clase que le corresponde
                    _patrones_clase->operator []( clase_elegida ).append( clase->takeAt( clase->indexOf( *p ) ) );
                    //_patrones_clase->at( clase ).removeAt( p );
                    hubo_cambio = true;
                }

            } // fin recorrido patrones de clase

        } // fin recorrido clases

    } // fin while

    // Graficar? para ir viendo el proceso :p


}
