#include <QtCore/QCoreApplication>

#include "../../GenomaAluminio.h"
#include "../../templateventana.h"
#include "../../templatealuminio.h"

#include "../../GenomaAluminio.h"


#include "../../evaluarAluminio.h"


#include "../../poblacion.h"

#include <QSettings>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << endl <<"COMIENZA LA EVALUACION DEL FITNESS DE LAS BARRAS DE ALUMINIO";

    Poblacion<GenomaAluminio> poblacionAluminio;

    // Cargo los parametros del ejercicio
    QSettings parametrosA( "parametrosAluminio.cfg", QSettings::IniFormat );

    // Inicializo la poblacion
    int cant_totalA = parametrosA.value( "cantidad_elementos", 10 ).toInt();
    poblacionAluminio.setearTotal( cant_totalA );
    poblacionAluminio.setearElitismo( parametrosA.value( "elitismo", false ).toBool() );
    poblacionAluminio.setearBrechaGeneracional( parametrosA.value( "brecha_generacional", 1.0 ).toDouble() );
    poblacionAluminio.setearProbabilidadMutacion( parametrosA.value( "probabilidad_mutacion", 2).toDouble() );
    poblacionAluminio.setearProbabilidadCruza( parametrosA.value( "probabilidad_cruza", 95).toDouble() );
    poblacionAluminio.setearModoSeleccionPadres( (Poblacion<GenomaAluminio>::MetodoSeleccion)parametrosA.value( "metodo_seleccion" ).toInt() );
    poblacionAluminio.setearPorcentajeCantidadDePadres( parametrosA.value( "cantidad_padres", 20 ).toDouble() );


    double fitnes_necesarioA = parametrosA.value( "fitnes_necesario", 0.0 ).toDouble();

    int iteracciones_maximasA = parametrosA.value( "iteracciones_maximas", 1000 ).toInt();
    int iteraccionesA = 0;

    QVector<TemplateAluminio> aluminios;

    // Genero los templates de Aluminio
    TemplateAluminio temp;
    temp.setearTipo( 0 );
    temp.setearLargo( 1.8 );
    temp.setearCantidad( 2 );
    aluminios.append( temp );

    TemplateAluminio temp2;
    temp2.setearTipo( 1 );
    temp2.setearLargo( 4.3  );
    temp2.setearCantidad( 4 );
    aluminios.append( temp2 );

    TemplateAluminio temp3;
    temp3.setearTipo( 2 );
    temp3.setearLargo( 0.3  );
    temp3.setearCantidad( 6 );
    aluminios.append( temp3 );

    // Genero el evaluador de las barras de aluminio
    FFDW *evaluador_aluminio = new FFDW();
    evaluador_aluminio->setearTemplates( aluminios );
    evaluador_aluminio->setearLargoBarraOriginal( parametrosA.value("largo_barra", 10.0).toDouble() );

    // Inicializo la población de cortes necesarios de aluminio
    for( int i=0; i<cant_totalA; i++ ) {
        GenomaAluminio temp;
        temp.setearEvaluador( evaluador_aluminio );
        temp.setearTemplates( aluminios );
        temp.randomizar();
        poblacionAluminio.append( temp );
    }

    poblacionAluminio.evaluarPoblacion();

    double mejor_fitness_aluminio = poblacionAluminio.mejorFitnes();
    GenomaAluminio pos_mejor_fitness_aluminio;
    int generacion_mejor_fitness = 1;

    while( poblacionAluminio.mejorFitnes() <= fitnes_necesarioA
           && iteraccionesA <= iteracciones_maximasA ) {
        qDebug() << "Reiniciado ---------------------------------------------------------";
        poblacionAluminio.seleccionarPadres();
        poblacionAluminio.generarHijos();
        poblacionAluminio.evaluarPoblacion();

        iteraccionesA++;

        qDebug() << "Fitness: "<<poblacionAluminio.mejorFitnes();
        if( poblacionAluminio.mejorFitnes() >= mejor_fitness_aluminio ) {
            mejor_fitness_aluminio = poblacionAluminio.mejorFitnes();
            qDebug() << " ------------------------------->  Fitness Actualizado " << mejor_fitness_aluminio;
            pos_mejor_fitness_aluminio = poblacionAluminio.elementoMinimo();
            generacion_mejor_fitness = iteraccionesA;
        }

    }

    qDebug() << "Mejor fitness global: " << mejor_fitness_aluminio;
    qDebug() << "Generacion mejor fitness" << generacion_mejor_fitness;
    
    return 0;
}
