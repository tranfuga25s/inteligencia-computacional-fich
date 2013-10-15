#include "controladordifuso.h"

ControladorDifuso::ControladorDifuso(QObject *parent) :
    QObject(parent)
{
    _ultima_temp = 0.0;
}


double ControladorDifuso::getVoltaje()
{ return 0.0; }

double ControladorDifuso::getIntensidad()
{ return 0.0; }
