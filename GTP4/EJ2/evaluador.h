#ifndef EVALUADOR_H
#define EVALUADOR_H

#include "genomaciudad.h"
/*
 * Funcion de evaluacion para el ejeficio 2
 */
static double evaluar( GenomaCiudad *valor ) {
    return valor->distanciaRecorrido();
}

static double evaluar( GenomaCiudad valor ) {
    return valor.distanciaRecorrido();
}

#endif // EVALUADOR_H
