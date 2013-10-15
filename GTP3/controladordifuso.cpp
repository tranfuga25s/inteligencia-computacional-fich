#include "controladordifuso.h"

ControladorDifuso::ControladorDifuso(QObject *parent) :
    QObject(parent)
{
    _ultima_temp = 0.0;
}

void ControladorDifuso::calcularProximoPaso()
{
    // Fuzzificacion
    // Me devolverá que conjunto de las entradas con que valor de activacion tiene cada uno
    // Para cada trapecio del conjunto de entradas
    // calcular la pertenencia de cada uno y me quedo con que trapecio era
    double pertenencia_maxima = -1.0;
    int num_conjunto_entrada = -1;
    for( int i=0; i<_conjunto_entrada.size(); i++ ) {
        double pertenencia = _conjunto_entrada.at(i)->valorSalida( _ultima_temp );
        if( pertenencia >= pertenencia_maxima ) {
            pertenencia_maxima = pertenencia;
            num_conjunto_entrada = i;
        }
    }

    // Ejecucion de las reglas
    // Activo las reglas que estén relacionadas con el conjunto de entrada elegido antes
    QVector<int> reglas_voltaje = _reglas_voltaje.at( num_conjunto_entrada );
    QVector<int> reglas_intensidad = _reglas_intensidad.at( num_conjunto_entrada );

    // Voltaje

    // Intensidad






}


double ControladorDifuso::getVoltaje()
{ return 0.0; }

double ControladorDifuso::getIntensidad()
{ return 0.0; }

void ControladorDifuso::agregarConjuntoEntrada( QString nombre, QVector<double> posiciones )
{
    _conjunto_entrada.append(
                new TrapecioDifuso( posiciones[0], posiciones[1], posiciones[2], posiciones[3], nombre )
    );
}

void ControladorDifuso::agregarConjuntoSalidaVoltaje( QString nombre, QVector<double> posiciones )
{
    _conjunto_salida_voltaje.append(
                new TrapecioDifuso( posiciones[0], posiciones[1], posiciones[2], posiciones[3], nombre )
    );
    // Agrego esto para poder mapear las reglas
    QVector<int> temp;
    _reglas_voltaje.append( temp );
}

void ControladorDifuso::agregarConjuntoSalidaIntensidad( QString nombre, QVector<double> posiciones )
{
    _conjunto_salida_intensidad.append(
                new TrapecioDifuso( posiciones[0], posiciones[1], posiciones[2], posiciones[3], nombre )
                );
    // Agrego esto para poder mapear las reglas
    QVector<int> temp;
    _reglas_intensidad.append( temp );
}

void ControladorDifuso::agregarReglaVoltaje( int conjunto_entrada, int conjunto_salida )
{
    if( conjunto_entrada < _conjunto_entrada.size() &&
            conjunto_salida < _conjunto_salida_voltaje.size() ) {
        _reglas_voltaje[conjunto_entrada].append( conjunto_salida );
    }
}

void ControladorDifuso::agregarReglaIntensidad( int conjunto_entrada, int conjunto_salida )
{
    if( conjunto_entrada < _conjunto_entrada.size() &&
            conjunto_salida < _conjunto_salida_intensidad.size() ) {
        _reglas_intensidad[conjunto_entrada].append( conjunto_salida );
    }
}


/*!
 * \brief TrapecioDifuso::centroide
 * Calcula el centroide de el trapecio considerando que se trunca en valor_entrada
 * \param valor_y
 * \return
 */
double TrapecioDifuso::centroide( double valor_y )
{
}


TrapecioDifuso::TrapecioDifuso( double pos1, double pos2, double pos3, double pos4, QString nombre )
{

}


/**
 * @brief TrapecioDifuso::valorSalida
 * Para un valor de entrada sobre "x" te devuleve el valor de "y" o pertenencia que le corresponda a este trapecio
 * @param valor_entrada
 * @return
 */
double TrapecioDifuso::valorSalida( double valor_entrada )
{
}
