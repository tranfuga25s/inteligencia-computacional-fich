#ifndef EVALUARVENTANA_H
#define EVALUARVENTANA_H

#include "FFDW.h"
#include "FFDWDH.h"
#include "GenomaVentana.h"
#include "templatealuminio.h"
#include "TemplatePiezas.h"

double evaluar( GenomaVentana ventana ) {

    QVector<TemplateAluminio> aluminios;
    QVector<TemplatePiezas> piezas_vidrio;

    for( int i=0; i<ventana.size(); i ++ ) {

        // Genero los templates de Aluminio
        TemplateAluminio temp;
        temp.setearTipo( i );
        temp.setearLargo( ventana.at(i).largo() );
        temp.setearCantidad( 2 );
        aluminios.append( temp );

        TemplateAluminio temp2;
        temp2.setearTipo( i );
        temp2.setearLargo( ventana.at(i).ancho() );
        temp2.setearCantidad( 2 );
        aluminios.append( temp2 );

        // Genero los templates de Vidrios
        TemplatePiezas temp3;
        temp3.setearTipo( i );
        temp3.setearAlto( ventana.at(i).alto() );
        temp3.setearAncho( ventana.at(i).alto() );
        temp3.setearCantidad( 1 );
        piezas_vidrio.append( temp3 );
    }

    FFDW evaluador_aluminio;
    evaluador_aluminio.setearTemplates( aluminios );

    FFDWDH evaluador_vidrios;
    evaluador_vidrios.setearTemplates( piezas_vidrio );

    double fitness = 0.0;
    fitnes = c1 * evaluador_aluminio.optimizar() + c2 * evaluador_vidrios.optimizar();
    return fitness;
}

#endif // EVALUARVENTANA_H
