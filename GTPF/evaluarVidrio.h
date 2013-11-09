#ifndef EVALUARVIDRIO_H
#define EVALUARVIDRIO_H

#include "FFDWDH.h"
#include "GenomaVidrio.h"
#include "TemplatePiezas.h"

double evaluar( GenomaVidrio gen , QVector<TemplatePiezas> piezas_vidrio) {

    double fitness = 0.0;

    FFDWDH evaluador_vidrios;
    evaluador_vidrios.setearTemplates( piezas_vidrio );

    fitness = evaluador_vidrios.evaluarGen(gen);

    return fitness;
}

#endif // EVALUARVIDRIO_H
