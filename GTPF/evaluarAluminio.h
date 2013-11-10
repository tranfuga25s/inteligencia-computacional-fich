#ifndef EVALUARALUMINIO_H
#define EVALUARALUMINIO_H

#include "GenomaAluminio.h"
#include "FFDW.h"

static double evaluar( const GenomaAluminio gen )
{
    qDebug() << "Procesando...";
    return gen.getEvaluador()->evaluarGen( gen );
}

#endif // EVALUARALUMINIO_H
