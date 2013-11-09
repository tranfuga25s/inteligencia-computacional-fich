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
        //temp.setearLargo( ventana.at(i).largo() );
        temp.setearCantidad( 2 );
        aluminios.append( temp );

        TemplateAluminio temp2;
        temp2.setearTipo( i );
        //temp2.setearLargo( ventana.at(i).ancho() );
        temp2.setearCantidad( 2 );
        aluminios.append( temp2 );

        // Genero los templates de Vidrios
        TemplatePiezas temp3;
        temp3.setearTipo( i );
        //temp3.setearAlto( ventana.at(i).alto() );
        //temp3.setearAncho( ventana.at(i).alto() );
        temp3.setearCantidad( 1 );
        piezas_vidrio.append( temp3 );
    }

    FFDW evaluador_aluminio;
    evaluador_aluminio.setearTemplates( aluminios );



    //VIDRIOS
    Poblacion<GenomaVidrio> poblacionVidrios;

    // Cargo los parametros del ejercicio
    QSettings parametrosV( "parametrosVidrio.cfg", QSettings::IniFormat );

    // Inicializo la poblacion
    int cant_totalV = parametrosV.value( "cantidad_elementos" ).toInt();
    poblacionVidrios.setearTotal( cant_totalV );
    poblacionVidrios.setearElitismo( parametrosV.value( "elitismo", false ).toBool() );
    poblacionVidrios.setearBrechaGeneracional( parametrosV.value( "brecha_generacional" ).toDouble() );
    poblacionVidrios.setearProbabilidadMutacion( parametrosV.value( "probabilidad_mutacion").toDouble() );
    poblacionVidrios.setearProbabilidadCruza( parametrosV.value( "probabilidad_cruza").toDouble() );
    poblacionVidrios.setearModoSeleccionPadres( (Poblacion<GenomaVidrio>::MetodoSeleccion)parametrosV.value( "metodo_seleccion" ).toInt() );
    poblacionVidrios.setearPorcentajeCantidadDePadres( parametrosV.value( "cantidad_padres" ).toDouble() );

    double fitnes_necesarioV = parametrosV.value( "fitnes_necesario", 0.0 ).toDouble();

    int iteracciones_maximasV = parametrosV.value( "iteracciones_maximas", 1000 ).toInt();
    int iteraccionesV = 0;

    poblacionVidrios.evaluarPoblacion(piezas_vidrio);

    double mejor_fitness_vidrio = 0.0;
    GenomaVidrio pos_mejor_fitness_vidrio;

    while( poblacionVidrios.mejorFitnes() <= fitnes_necesarioV
           && iteraccionesV <= iteracciones_maximasV ) {

        poblacionVidrios.seleccionarPadres();
        poblacionVidrios.generarHijos(piezas_vidrio);
        poblacionVidrios.evaluarPoblacion(piezas_vidrio);

        iteraccionesV++;


        if( mejor_fitness_vidrio <= poblacionVidrios.mejorFitnes() ) {
            mejor_fitness_vidrio = poblacionVidrios.mejorFitnes();
            pos_mejor_fitness_vidrio = poblacionVidrios.elementoMinimo();
        }

    }

//    //ALUMINIO
//    Poblacion<GenomaVidrio> poblacionAluminio;

//    // Cargo los parametros del ejercicio
//    QSettings parametrosA( "parametrosAluminio.cfg", QSettings::IniFormat );

//    // Inicializo la poblacion
//    int cant_totalA = parametrosA.value( "cantidad_elementos" ).toInt();
//    poblacionAluminio.setearTotal( cant_totalA );
//    poblacionAluminio.setearElitismo( parametrosA.value( "elitismo", false ).toBool() );
//    poblacionAluminio.setearBrechaGeneracional( parametrosA.value( "brecha_generacional" ).toDouble() );
//    poblacionAluminio.setearProbabilidadMutacion( parametrosA.value( "probabilidad_mutacion").toDouble() );
//    poblacionAluminio.setearProbabilidadCruza( parametrosA.value( "probabilidad_cruza").toDouble() );
//    poblacionAluminio.setearModoSeleccionPadres( (Poblacion<GenomaAluminio>::MetodoSeleccion)parametrosA.value( "metodo_seleccion" ).toInt() );
//    poblacionAluminio.setearPorcentajeCantidadDePadres( parametrosA.value( "cantidad_padres" ).toDouble() );


//    double fitnes_necesarioA = parametrosA.value( "fitnes_necesario", 0.0 ).toDouble();

//    int iteracciones_maximasA = parametrosA.value( "iteracciones_maximas", 1000 ).toInt();
//    int iteraccionesA = 0;

//    poblacionAluminio.evaluarPoblacion(aluminios);

//    double mejor_fitness_aluminio = 0.0;
//    GenomaVidrio pos_mejor_fitness_aluminio;

//    while( poblacionAluminio.mejorFitnes() <= fitnes_necesarioA
//           && iteraccionesA <= iteracciones_maximasA ) {

//        poblacionAluminio.seleccionarPadres();
//        poblacionAluminio.generarHijos();
//        poblacionAluminio.evaluarPoblacion(aluminios);

//        iteraccionesA++;


//        if( mejor_fitness_aluminio <= poblacionAluminio.mejorFitnes() ) {
//            mejor_fitness_aluminio = poblacionAluminio.mejorFitnes();
//            pos_mejor_fitness_aluminio = poblacionAluminio.elementoMinimo();
//        }

//    }


    double fitness = 0.0;
    double c1 = 1.0;
    double c2 = 1.0;
    //fitness = c1 * mejor_fitness_aluminio + c2 * mejor_fitness_vidrio;
    return fitness;
}

#endif // EVALUARVENTANA_H
