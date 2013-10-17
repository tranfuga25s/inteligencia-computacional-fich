#include "controladordifuso.h"

#include <QMessageBox>

ControladorDifuso::ControladorDifuso( QObject *parent ) :
    QObject(parent)
{
    _ultima_temp = 0.0;
    _ultima_intensidad = 0.0;
    _ultimo_voltaje = 0.0;
    _ultima_deseada = 0.0;
}

void ControladorDifuso::calcularProximoPaso()
{
    // Fuzzificacion

    // La variable de entrada es la diferencia entre la temperatura actual y la deseada
    double variable_entrada = _ultima_temp - _ultima_deseada;

    // Me devolverá que conjunto de las entradas con que valor de activacion tiene cada uno
    // Para cada trapecio del conjunto de entradas
    // calcular la pertenencia de cada uno y me quedo con que trapecio era
    double pertenencia_maxima = -1.0;
    int num_conjunto_entrada = -1;
    for( int i=0; i<_conjunto_entrada.size(); i++ ) {
        double pertenencia = _conjunto_entrada.at(i)->valorSalida( variable_entrada );
        if( pertenencia >= pertenencia_maxima ) {
            pertenencia_maxima = pertenencia;
            num_conjunto_entrada = i;
        }
    }

    // Ejecucion de las reglas
    // Activo las reglas que estén relacionadas con el conjunto de entrada elegido antes
    QVector<int> reglas_voltaje    = _reglas_voltaje   .at( num_conjunto_entrada );
    QVector<int> reglas_intensidad = _reglas_intensidad.at( num_conjunto_entrada );

    // Voltaje
    QVector<double> areas;
    QVector<double> centroides;
    for( int i=0; i<reglas_voltaje.size(); i++ ) {
        areas.append( _conjunto_salida_voltaje.at( reglas_voltaje.at( i ) )->area( pertenencia_maxima ) );
        centroides.append( _conjunto_salida_voltaje.at( reglas_voltaje.at( i ) )->centroide( pertenencia_maxima ) );
    }
    // Calculo el centroide de los centroides seleccionados por las reglas
    double suma_areas = 0.0;
    double suma_centroides = 0.0;
    for( int i=0; i<areas.size(); i++ ) {
        suma_areas += areas.at(i);
        suma_centroides += centroides.at(i);
    }
    _ultimo_voltaje = suma_centroides/suma_areas;

    // Intensidad
    areas.clear();
    centroides.clear();
    for( int i=0; i<reglas_intensidad.size(); i++ ) {
        areas.append( _conjunto_salida_voltaje.at( reglas_voltaje.at( i ) )->area( pertenencia_maxima ) );
        centroides.append( _conjunto_salida_voltaje.at( reglas_voltaje.at( i ) )->centroide( pertenencia_maxima ) );
    }

    // Calculo el centroide de los centroides seleccionados por las reglas
    suma_areas = 0.0;
    suma_centroides = 0.0;
    for( int i=0; i<areas.size(); i++ ) {
        suma_areas += areas.at(i);
        suma_centroides += centroides.at(i);
    }

    _ultima_intensidad = suma_centroides/suma_areas;
}


double ControladorDifuso::getVoltaje()
{ return _ultimo_voltaje; }

double ControladorDifuso::getIntensidad()
{ return _ultima_intensidad; }

void ControladorDifuso::agregarConjuntoEntrada( QString nombre, QVector<double> posiciones )
{
    _conjunto_entrada.append(
                new TrapecioDifuso( posiciones[0], posiciones[1], posiciones[2], posiciones[3], nombre )
    );
    // Agrego esto para poder mapear las reglas
    QVector<int> temp;
    _reglas_intensidad.append( temp );
    _reglas_voltaje.append( temp );
}

void ControladorDifuso::agregarConjuntoSalidaVoltaje( QString nombre, QVector<double> posiciones )
{
    _conjunto_salida_voltaje.append(
                new TrapecioDifuso( posiciones[0], posiciones[1], posiciones[2], posiciones[3], nombre )
    );
}

void ControladorDifuso::agregarConjuntoSalidaIntensidad( QString nombre, QVector<double> posiciones )
{
    _conjunto_salida_intensidad.append(
                new TrapecioDifuso( posiciones[0], posiciones[1], posiciones[2], posiciones[3], nombre )
    );
}

void ControladorDifuso::agregarReglaVoltaje( int conjunto_entrada, int conjunto_salida )
{
    if( conjunto_entrada < _conjunto_entrada.size() &&
            conjunto_salida < _conjunto_salida_voltaje.size() ) {
        _reglas_voltaje[conjunto_entrada].append( conjunto_salida );
    } else {
        QMessageBox::critical( 0, "Error",
          QString::fromUtf8("Intentando cargar regla para el conjunto de entrada %1 y salida %2 pero entradas tiene %3 elementos y salidas voltaje tiene %4" )
                            .arg( conjunto_entrada )
                            .arg( conjunto_salida )
                            .arg( _conjunto_entrada.size() )
                            .arg( _conjunto_salida_voltaje.size() ) );
          abort();
    }
}

void ControladorDifuso::agregarReglaIntensidad( int conjunto_entrada, int conjunto_salida )
{
    if( conjunto_entrada < _conjunto_entrada.size() &&
            conjunto_salida < _conjunto_salida_intensidad.size() ) {
        _reglas_intensidad[conjunto_entrada].append( conjunto_salida );
    } else {
        QMessageBox::critical( 0, "Error",
          QString::fromUtf8("Intentando cargar regla para el conjunto de entrada %1 y salida %2 pero entradas tiene %3 elementos y salidas intensidad tiene %4" )
                            .arg( conjunto_entrada )
                            .arg( conjunto_salida )
                            .arg( _conjunto_entrada.size() )
                            .arg( _conjunto_salida_intensidad.size() ) );
          abort();
    }
}


/*!
 * \brief TrapecioDifuso::centroide
 * Calcula el centroide de el trapecio considerando que se trunca en valor_y
 * \param valor_y
 * \return
 */
double TrapecioDifuso::centroide( double valor_y )
{

}

/*!
 * \brief TrapecioDifuso::area
 * Calcula el área de el trapecio según la altura indicada
 * \param valor_y
 * \return
 */
double TrapecioDifuso::area( double valor_y )
{
    double area = 0.0;
    area += ( ( pos2 - pos1 ) * valor_y ) / 2.0;
    area += ( ( pos3 - pos2 ) * valor_y );
    area += ( ( pos4 - pos3 ) * valor_y ) / 2.0;
    return area;
}


TrapecioDifuso::TrapecioDifuso( double p1, double p2, double p3, double p4, QString nom )
    : pos1( p1 ), pos2( p2 ), pos3( p3 ), pos4( p4 ), _nombre( nom )
{}


/**
 * @brief TrapecioDifuso::valorSalida
 * Para un valor de entrada sobre "x" te devuleve el valor de "y" o pertenencia que le corresponda a este trapecio
 * @param valor_entrada
 * @return
 */
double TrapecioDifuso::valorSalida( double valor_entrada )
{
    if( valor_entrada < pos1 || valor_entrada > pos4 ) {
        return 0.0;
    } else if( valor_entrada >= pos2 && valor_entrada <= pos3 ) {
        return 1.0;
    } else if( valor_entrada >= pos1 && valor_entrada <= pos2 ) {
        return ( pos2 - pos1 ) * ( valor_entrada - pos1 );
    } else if( valor_entrada >= pos3 && valor_entrada <= pos4 ) {
        return ( ( ( pos4 - pos3 ) * ( valor_entrada - pos3 ) ) / -1.0 ) + 1.0;
    }
}
