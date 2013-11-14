#ifndef EVALUARVIDRIO_H
#define EVALUARVIDRIO_H

#include "GenomaVidrio.h"
#include "FFDWDH.h"

static double evaluarVidrio( GenomaVidrio gen )
{
    //qDebug() << "Procesando...";
    return gen.getEvaluador()->evaluarGen( gen );
}

#endif // EVALUARVIDRIO_H
