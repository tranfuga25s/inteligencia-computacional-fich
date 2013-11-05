#ifndef EVALUADOR_H
#define EVALUADOR_H

#include "math.h"
#include "../EJ1/genomax.h"
/*
 * Funcion de evaluacion para el ejeficio 1 B
 */
static double evaluar( GenomaX valor ) {
    return (valor.getX())+(5.0 * sin( 3.0 * valor.getX() ) )+ (8.0 * cos( 5.0 * valor.getX() ));
}

static double evaluar( double valor ) {
    return (valor)+(5.0 * sin( 3.0 * valor ) )+ (8.0 * cos( 5.0 * valor ));
}

#endif // EVALUADOR_H
