#include "controladordifuso.h"

ControladorDifuso::ControladorDifuso(QObject *parent) :
    QObject(parent)
{
    _ultima_temp = 0.0;
}

void ControladorDifuso::calcularProximoPaso()
{

    // Para cada trapecio del conjunto de entradas
    // calcular la pertenencia de cada uno y me quedo con que trapecio era



}


double ControladorDifuso::getVoltaje()
{ return 0.0; }

double ControladorDifuso::getIntensidad()
{ return 0.0; }


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
