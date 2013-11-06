#include "som.h"

#include <QPointF>

#include "math.h"
#include "cfloat"

SOM::SOM( int tamano_x, int tamano_y, int tamano_entradas )
{
    for( int f=0; f<tamano_x; f++ ) {
        QVector< QVector<double> > temp;
        QVector<double> temp_delta;
        for( int c=0; c<tamano_y; c++ ) {
            QVector<double> temporal( tamano_entradas );
            for(int t=0; t<tamano_entradas; t++ ) {
                temporal[t] = valor_random( -1.0, 1.0 );
            }
            temp.append( temporal );
            temp_delta.append( 0.0 );
        }
        _som.append( temp );
        _ultimos_deltas.append( temp_delta );
    }
}

/*!
 * \brief SOM::entrenar
 *Calcula la neurona ganadora y actualiza sus pesos y los de su vecindad
 * \param patron
 */
void SOM::entrenar( QVector<double> patron )
{
    double distancia_minima = DBL_MAX;
    int fila_ganadora = -1;
    int columna_ganadora = -1;
    QVector<double> ultima_distancia;

    for( int f=0; f<_som.size(); f++ ) {

        for( int c=0; c<_som.at(f).size(); c++ ) {

            double dist = this->distancia( patron, f, c );
            ultima_distancia.append(dist);

            if( dist < distancia_minima ) {
                distancia_minima = dist;
                fila_ganadora = f;
                columna_ganadora = c;
            }
        }

    }

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
    return pow( distancia, 0.5 );
}

/*!
 * \brief SOM::actualizarPeso
 * \param fila
 * \param columna
 * \param distancia_obtenida
 */
void SOM::actualizarPeso( int fila_ganadora, int columna_ganadora, vector distancia_obtenida )
{
    int max_vec_x = max_x_matriz( fila_ganadora   , this->_radio_vecindad, _som.size() );
    int min_vec_x = min_x_matriz( fila_ganadora   , this->_radio_vecindad );
    int max_vec_y = max_y_matriz( columna_ganadora, this->_radio_vecindad, _som.at(0).size() );
    int min_vec_y = min_y_matriz( columna_ganadora, this->_radio_vecindad );

    for( int fil=min_vec_x; fil<max_vec_x; fil++ ) {

        for( int col=min_vec_y; col<max_vec_y; col++ ) {

            QVector<double> vecindad = funcionVecindad( fil, col, fila_ganadora, columna_ganadora );

            // posicion x e y
            for( int pos=0; pos<_som.at(fil).at(col).size(); pos++ ) {
                if( vecindad.at( pos ) > _limite_vecindad ) {
                        double temp = _tasa_aprendizaje*
                                      distancia_obtenida.at(pos)/*
                                      vecindad.at( pos )*/;
                        _som[fil][col][pos] += temp;
                        _ultimos_deltas[fil][col] = temp;
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

    //qDebug() << radioVecindad();
    QVector<double> temp;
    if (_radio_vecindad > 0) {
        temp.append(exp((-1.0)*(pow((double)(fila_ganadora-fila),2.0))/(2.0*pow(_radio_vecindad,2.0))));
        temp.append(exp((-1.0)*(pow((double)(columna_ganadora-columna),2.0))/(2.0*pow(_radio_vecindad,2.0))));
    }
    else
    {
        temp.append(exp((-1.0)*(pow((double)(fila_ganadora-fila),2.0))/(2.0*pow(1.0,2.0))));
        temp.append(exp((-1.0)*(pow((double)(columna_ganadora-columna),2.0))/(2.0*pow(1.0,2.0))));
    }

//    if( fila == fila_ganadora && columna == columna_ganadora ) {
//        temp << 1.0 << 1.0;
//    } else {
//        temp << 0.0 << 0.0;
//    }
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
    qSort( temp.begin(), temp.end(), SOM::menorque );
    return temp;
}

bool SOM::cambiosSignificativos()
{
    //Calculo el error promedio y la desviacion estandar para la particion
    double media = 0.0;
    double desviacion_estandar = 0.0;
    double aux = 0.0;


    for (int i = 0 ; i < _ultimos_deltas.size() ; i++ ) {
        for(int j = 0; j<_ultimos_deltas.at(i).size(); j++) {
            media += _ultimos_deltas.at(i).at(j);
        }
    }
    int cant_datos = _ultimos_deltas.size()*_ultimos_deltas.at(0).size();

    media /= cant_datos;

    for (int i = 0 ; i < _ultimos_deltas.size() ; i++ ) {
        for(int j = 0; j<_ultimos_deltas.at(i).size(); j++) {
            aux += pow( _ultimos_deltas.at(i).at(j) - media ,2.0);
        }
    }

    desviacion_estandar = sqrt( (1.0 / ((double)cant_datos - 1.0) ) * aux );


    double varianza = (media + desviacion_estandar)*2.0;

    varianza = varianza*0.5 + 1.0;

    if(varianza > _tasa_aprendizaje) {
        return true;
    }
    else
    {
        return false;
    }
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
        ret[i] = val1.at( i ) - val2.at( i );
    }
    return ret;
}
