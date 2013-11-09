#ifndef EVALUARVIDRIO_H
#define EVALUARVIDRIO_H

#include "FFDWDH.h"
#include "GenomaVidrio.h"
#include "TemplatePiezas.h"

static double evaluar(GenomaVidrio gen,QVector<TemplatePiezas> piezas_vidrio)
{
    FFDWDH evaluador_vidrios;
    evaluador_vidrios.setearTemplates( piezas_vidrio );

    double fitness = 0.0;
    fitness = evaluador_vidrios.evaluarGen(gen);

    return fitness;
}

#endif // EVALUARVIDRIO_H
