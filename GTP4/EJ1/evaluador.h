#ifndef EVALUADOR_H
#define EVALUADOR_H

#include "math.h"
#include "genomax.h"
/*
 * Funcion de evaluacion para el ejeficio 1 A
 */
static double evaluar( double valor ) {
    return (-1.0) * valor * ( sin( sqrt( abs( valor ) ) ) );
}

static double evaluar( GenomaX elem ) {
    return evaluar( elem.getX() );
}

#endif // EVALUADOR_H
