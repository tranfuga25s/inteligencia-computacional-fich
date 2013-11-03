#ifndef EVALUADORXY_H
#define EVALUADORXY_H

#include "genomaxy.h"
/*
 * Funcion de evaluacion para el ejeficio 1 A
 */
static double evaluar( GenomaXY g ) {
    return ( pow(
                 pow( g.getX(), 2.0 ) +
                 pow( g.getY(), 2.0 )
                 , 0.25 ) +
            ( pow( sin( 50.0
                        * pow(
                            pow( g.getX(), 2.0 ) +
                            pow( g.getY(), 2.0 )
                            , 0.1 )
                       )
                  , 2.0 )
               + 1.0 ) );
}

static double evaluar( double x, double y ) {
    return ( pow(
                 pow( x, 2.0 ) +
                 pow( y, 2.0 )
                 , 0.25 ) +
            ( pow( sin( 50.0
                        * pow(
                            pow( x, 2.0 ) +
                            pow( y, 2.0 )
                            , 0.1 )
                       )
                  , 2.0 )
               + 1.0 ) );
}

#endif // EVALUADORXY_H
