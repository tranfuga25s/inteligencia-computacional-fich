#ifndef EVALUARVENTANA_H
#define EVALUARVENTANA_H

#include "FFDW.h"
#include "GenomaVentana.h"
#include "templatealuminio.h"
#include "templatepieza.h"

double evaluar( GenomaVentana ventana ) {

    QVector<TemplateAluminio> aluminios;
    QVector<TemplatePieza> piezas_vidrio;

    for( int i=0; i<ventana.size(); i ++ ) {


        // Genero los templates de Aluminio


        // Genero los templates de Vidrios


    }
}

#endif // EVALUARVENTANA_H
