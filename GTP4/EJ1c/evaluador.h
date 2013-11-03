#ifndef EVALUADOR_H
#define EVALUADOR_H

/*
 * Funcion de evaluacion para el ejeficio 1 A
 */
static double evaluar( GenomaXY g ) {
    return ( pow(
                 pow( g.getX(), 2.0 ) +
                 pow( g.getY(), 2.0 ) )
                 , 0.25 ) +
            ( pow( sin( 50.0
                        * pow(
                            pow( g.getX(), 2.0 ) +
                            pow( g.getY(), 2.0 ) )
                            , 0.1 )
                  , 2.0 )
               + 1.0 );
}

#endif // EVALUADOR_H
