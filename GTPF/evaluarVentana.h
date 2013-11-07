#ifndef EVALUARVENTANA_H
#define EVALUARVENTANA_H

#include "FFDW.h"
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
        aluminios.append( temp );

        TemplateAluminio temp2;
        temp2.setearTipo( i );
        temp2.setearLargo( ventana.at(i).ancho() );
        aluminios.append( temp2 );

        // Genero los templates de Vidrios
        TemplatePiezas temp3;
        temp3.setearTipo( i );
        piezas_vidrio.append( temp3 );


    }
}

#endif // EVALUARVENTANA_H
