#include "som.h"

#include <QPointF>

#include "math.h"
#include "cfloat"

SOM::SOM( int tamano_x, int tamano_y, int tamano_entradas )
{
    for( int f=0; f<tamano_x; f++ ) {
        QVector< QVector<double> > temp;
        for( int c=0; c<tamano_y; c++ ) {
            QVector<double> temporal( tamano_entradas );
            for(int t=0; t<tamano_entradas; t++ ) {
                temporal[t] = valor_random( -0.5, 0.5 );
            }
            temp.append( temporal );
        }
        _som.append( temp );
    }
}

/*!
 * \brief SOM::entrenar
 * \param patron
 */
void SOM::entrenar( QVector<double> patron )
{
    double distancia_minima = DBL_MAX;
    int fila_ganadora = -1;
    int columna_ganadora = -1;
    double ultima_distancia;

    for( int f=0; f<_som.size(); f++ ) {

        for( int c=0; c<_som.at(f).size(); c++ ) {

            double dist = this->distancia( patron, f, c );
            ultima_distancia = dist;

            if( dist <= distancia_minima ) {
                distancia_minima = dist;
                fila_ganadora = f;
                columna_ganadora = c;
            }
        }

    }
    //qDebug() << ultima_distancia;
    if( columna_ganadora == -1 || fila_ganadora == -1 ) {
        qDebug() << "Patron: " << patron << " no tuvo ninguna neurona ganadora. Distancia: "<<ultima_distancia;
        //abort();
    } else {

        // La distancia tiene que ser un vector de las mismas dimensiones
        // que la entrada para "acercarlo" al patron
        vector dif = diferenciaVector( patron, _som.at( fila_ganadora ).at( columna_ganadora ) );

        actualizarPeso( fila_ganadora, columna_ganadora, dif );
    }

}

/*!
 * \brief SOM::distancia
 * \param patron
 * \param fila
 * \param columna
 * \return
 */
double SOM::distancia( QVector<double> patron, int fila, int columna )
{
    double distancia = 0.0;
    for( int i=0; i<patron.size(); i++ ) {
        distancia += pow( ( patron.at( i ) - _som.at( fila ).at( columna ).at( i ) ), 2.0 );
    }
    return sqrt( distancia );
}

/*!
 * \brief SOM::actualizarPeso
 * \param fila
 * \param columna
 * \param distancia_obtenida
 */
void SOM::actualizarPeso( int fila, int columna, QVector<double> distancia_obtenida )
{
    int max_vec_x = max_x_matriz( columna, this->_radio_vecindad, _som.size() );
    int min_vec_x = min_x_matriz( columna, this->_radio_vecindad );
    int max_vec_y = max_y_matriz( fila   , this->_radio_vecindad, _som.at(0).size() );
    int min_vec_y = min_y_matriz( fila   , this->_radio_vecindad );

    for( int fil=min_vec_y; fil< max_vec_y; fil++ ) {

        for( int col=min_vec_x; col<max_vec_x; col++ ) {

            QVector<double> vecindad = funcionVecindad( fil, col, fila, columna );

            for( int pos=0; pos<vecindad.size(); pos++ ) { //_som.at(fil).at(col).size()

                if( vecindad.at( pos ) > 0.15 ) {
                    double dif =  _tasa_aprendizaje*
                            distancia_obtenida.at(pos)*
                            vecindad.at( pos );
                    if( dif > 0.6 ) {
                        abort();
                    } else {
                        qDebug() << dif;
                        _som[fil][col][pos] += _tasa_aprendizaje*
                                               distancia_obtenida.at(pos)*
                                               vecindad.at( pos );
                    }
                }
            }
        }
    }
}

/*!
 * \brief SOM::funcionVecindad
 * \param fila
 * \param columna
 * \param fila_ganadora
 * \param columna_ganadora
 * \return
 */
QVector<double> SOM::funcionVecindad( int fila, int columna, int fila_ganadora, int columna_ganadora )
{
    QVector<double> temp;
        temp << exp((-1)*(pow((double)(fila_ganadora-fila),2.0))/(2.0*pow(_radio_vecindad,2.0)))
             << exp((-1)*(pow((double)(columna_ganadora-columna),2.0))/(2.0*pow(_radio_vecindad,2.0)));
    return temp;
}

/*!
 * \brief SOM::obtenerPuntos
 * \return
 */
QVector<QPointF> SOM::obtenerPuntos()
{
    QVector<QPointF> temp;
    for( int fil=0; fil< _som.size(); fil++ ) {
        for( int col=0; col<_som.at(fil).size(); col++ ) {
            QPointF punto;
            punto.setX( _som.at(fil).at(col).at(0) );
            punto.setY( _som.at(fil).at(col).at(1) );
            temp.append( punto );
        }
    }
    return temp;
}

/*!
 * \brief SOM::diferenciaVector
 * \param val1
 * \param val2
 * \return
 */
QVector<double> SOM::diferenciaVector( QVector<double> val1, QVector<double> val2 )
{
    QVector<double> ret( val1.size() );
    for( int i=0; i<val1.size(); i++ ) {
        ret[i] = val2.at( i ) - val1.at( i );
    }
    return ret;
}
