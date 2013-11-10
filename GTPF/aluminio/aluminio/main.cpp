#include <QtCore/QCoreApplication>

#include "../GenomaAluminio.h"
#include "../templateventana.h"
#include "../templatealuminio.h"

#include "../GenomaAluminio.h"


#include "../evaluarAluminio.h"


#include "../poblacion.h"

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
    poblacionAluminio.setearBrechaGeneracional( parametrosA.value( "brecha_generacional" ).toDouble() );
    poblacionAluminio.setearProbabilidadMutacion( parametrosA.value( "probabilidad_mutacion").toDouble() );
    poblacionAluminio.setearProbabilidadCruza( parametrosA.value( "probabilidad_cruza").toDouble() );
    poblacionAluminio.setearModoSeleccionPadres( (Poblacion<GenomaAluminio>::MetodoSeleccion)parametrosA.value( "metodo_seleccion" ).toInt() );
    poblacionAluminio.setearPorcentajeCantidadDePadres( parametrosA.value( "cantidad_padres" ).toDouble() );


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
    return 0;
    poblacionAluminio.evaluarPoblacion();

    double mejor_fitness_aluminio = DBL_MIN;
    GenomaAluminio pos_mejor_fitness_aluminio;

    while( poblacionAluminio.mejorFitnes() <= fitnes_necesarioA
           && iteraccionesA <= iteracciones_maximasA ) {
        qDebug() << "Reiniciado";
        poblacionAluminio.seleccionarPadres();
        poblacionAluminio.generarHijos();
        poblacionAluminio.evaluarPoblacion();

        iteraccionesA++;

        qDebug() << "Fitnes: "<<poblacionAluminio.mejorFitnes();
        if( mejor_fitness_aluminio <= poblacionAluminio.mejorFitnes() ) {
            mejor_fitness_aluminio = poblacionAluminio.mejorFitnes();
            qDebug() << "Fitnes Actualizado " << mejor_fitness_aluminio;
            pos_mejor_fitness_aluminio = poblacionAluminio.elementoMinimo();
        }

    }
    
    return 0;
}
