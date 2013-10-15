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





}


double ControladorDifuso::getVoltaje()
{ return 0.0; }

double ControladorDifuso::getIntensidad()
{ return 0.0; }

void ControladorDifuso::agregarConjuntoEntrada(QString nombre, QVector<double> posiciones)
{
}

void ControladorDifuso::agregarConjuntoSalidaVoltaje(QString nombre, QVector<double> posiciones)
{
}

void ControladorDifuso::agregarConjuntoSalidaIntensidad(QString nombre, QVector<double> posiciones)
{
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
