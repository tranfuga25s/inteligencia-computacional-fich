#ifndef EVALUARVIDRIO_H
#define EVALUARVIDRIO_H

#include "GenomaVidrio.h"

static double evaluar( GenomaVidrio gen )
{
    return gen.getEvaluador()->evaluarGen( gen );
}

#endif // EVALUARVIDRIO_H
