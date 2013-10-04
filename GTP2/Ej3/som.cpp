#include "som.h"

#include "math.h"

SOM::SOM( int tamano_x, int tamano_y, int tamano_entradas )
{
    for( int c=0; c<tamano_x; c++ ) {
        QVector< QVector<double> > temp;
        for( int f=0; f<tamano_y; f++ ) {
            QVector<double> temporal( tamano_entradas );
            temp.append( temporal );
        }
        _som.append( temp );
    }
}

void SOM::entrenar( QVector<double> patron )
{
    double distancia_minima = 0.0;
    int fila_ganadora = -1;
    int columna_ganadora = -1;

    for( int c=0; c<_som.size(); c++ ) {

        for( int f=0; f<_som.at(c).size(); f++ ) {

            double dist = distancia( patron, c, f );

            if( dist <= distancia_minima ) {
                distancia_minima = dist;
                fila_ganadora = f;
                columna_ganadora = c;
            }

        }

    }

    actualizarPeso( fila_ganadora, columna_ganadora, distancia_minima );

}

double SOM::distancia( QVector<double> patron, int fila, int columna )
{
    double distancia;
    for( int i=0; i<patron.size(); i++ ) {
        distancia += pow( patron.at( i ) - _som.at( columna ).at( fila ).at( i ), 2.0 );
    }
    return sqrt( distancia );
}

void SOM::actualizarPeso( int fila, int columna, double distancia_obtenida )
{
    int max_vec_x = max_x_matriz(columna,distancia_obtenida,_som.size());
    int min_vec_x = min_x_matriz(columna,distancia_obtenida);
    int max_vec_y = max_y_matriz(fila,distancia_obtenida,_som.at(0).size());
    int min_vec_y = min_y_matriz(fila,distancia_obtenida);

    for( int col=min_vec_x; col< max_vec_x; col++ ) {

        for( int fil=min_vec_y; fil<max_vec_y; fil++ ) {

            for( int pos=0; pos<_som.at(col).at(fil).size(); pos++ ) {

                _som[col][fil][pos] += _tasa_aprendizaje*distancia_obtenida*funcionVecindad( fil, col, fila, columna );

            }

        }

    }

}

double SOM::funcionVecindad( int fila, int columna, int fila_ganadora, int columna_ganadora )
{

    if( _radio_vecindad == 0 && fila != fila_ganadora && columna != columna_ganadora ) {
        return 0.0;
    }

    double distancia = sqrt( pow( fila_ganadora - fila, 2.0 ) + pow( columna_ganadora - columna, 2.0 ) );

    return exp( ( -1 )  * ( pow( abs( distancia ), 2.0 ) ) / ( 2.0 * pow( _radio_vecindad, 2.0 ) ) );
}

void SOM::setearClase(int fila, int col, int clase)
{
    _som_clasificado[fila][col] = clase;
}

QPair<int, int> SOM::getNeuronaGanadora(QVector<double> patron)
{
    double distancia_minima = 0.0;
    int fila_ganadora = -1;
    int columna_ganadora = -1;

    for( int c=0; c<_som.size(); c++ ) {

        for( int f=0; f<_som.at(c).size(); f++ ) {

            double dist = distancia( patron, c, f );

            if( dist <= distancia_minima ) {
                distancia_minima = dist;
                fila_ganadora = f;
                columna_ganadora = c;
            }

        }

    }

    return QPair<int, int>(fila_ganadora,columna_ganadora);
}
