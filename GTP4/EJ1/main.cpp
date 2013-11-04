#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QTime>
#include <QDir>
#include <QVector>
#include <QSettings>
#include <QMdiArea>
#include <QProgressBar>
#include <QDockWidget>
#include <QLayout>
#include <QElapsedTimer>

#include "iostream"

typedef QVector<double> vector;
typedef QVector< QVector<double> > matriz;

#include "evaluador.h"
#include "funciones_aux.h"
#include "genomax.h"
#include "poblacion.h"
#include "graficadormdi.h"

/*!
 * \brief main
 * Guia de Trabajos Practicos 3
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char *argv[])
{
    QApplication a( argc, argv );
    QMainWindow main;
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    main.showMaximized();
    QMdiArea *mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    main.setCentralWidget(mdiArea);

    GraficadorMdi *grafFuncion = new GraficadorMdi( mdiArea );
    grafFuncion->setearTitulo( QString::fromUtf8( "Funcion" ) );
    grafFuncion->setearTituloEjeX( QString::fromUtf8( "X" ) );
    grafFuncion->setearTituloEjeY( QString::fromUtf8( "Y" ) );
    mdiArea->addSubWindow( grafFuncion );
    grafFuncion->show();
    mdiArea->tileSubWindows();

    GraficadorMdi *grafFitnes = new GraficadorMdi( mdiArea );
    grafFitnes->setearTitulo( QString::fromUtf8( "Evolucion Mejor Fitness" ) );
    grafFitnes->setearTituloEjeX( QString::fromUtf8( "Generacion" ) );
    grafFitnes->setearTituloEjeY( QString::fromUtf8( "fitness" ) );
    mdiArea->addSubWindow( grafFitnes );
    grafFitnes->show();
    mdiArea->tileSubWindows();
    grafFitnes->setearParaSOM();

    GraficadorMdi *grafPuntos = new GraficadorMdi( mdiArea );
    grafPuntos->setearTitulo( QString::fromUtf8( "Puntos a evaluar" ) );
    grafPuntos->setearTituloEjeX( QString::fromUtf8( "Posicion" ) );
    grafPuntos->setearTituloEjeY( QString::fromUtf8( "Y" ) );
    mdiArea->addSubWindow( grafPuntos );
    grafPuntos->show();
    mdiArea->tileSubWindows();
    //grafPuntos->setearParaSOM();
   // grafPuntos->setearEjesEnGrafico();

    GraficadorMdi *grafPromedio = new GraficadorMdi( mdiArea );
    grafPromedio->setearTitulo( QString::fromUtf8( "Fitness Promedio" ) );
    grafPromedio->setearTituloEjeX( QString::fromUtf8( "Posicion" ) );
    grafPromedio->setearTituloEjeY( QString::fromUtf8( "Y" ) );
    mdiArea->addSubWindow( grafPromedio );
    grafPromedio->show();
    mdiArea->tileSubWindows();
    grafPromedio->setearParaSOM();

    // barra de progreso para mostrar el avance del tiempo
    QDockWidget *dockBarra = new QDockWidget( QString::fromUtf8( "Evaluaciones" ) );
    main.addDockWidget( Qt::BottomDockWidgetArea, dockBarra );
    QProgressBar *PBTiempo = new QProgressBar( dockBarra );
    dockBarra->setWidget( PBTiempo );

    //Inicializo con una semilla aleatoria para la generacion de Aleatorios
    qsrand( QTime::currentTime().msec() );

    // Cargo los parametros del ejercicio
    QSettings parametros( "parametros.cfg", QSettings::IniFormat );

    // Inicializo la poblacion
    Poblacion<GenomaX> pob;
    int cant_total = parametros.value( "cantidad_elementos" ).toInt();
    pob.setearTotal( cant_total );

    pob.setearElitismo( parametros.value( "elitismo", false ).toBool() );
    pob.setearBrechaGeneracional( parametros.value( "brecha_generacional" ).toDouble() );
    pob.setearProbabilidadMutacion( parametros.value( "probabilidad_mutacion").toDouble() );
    pob.setearModoSeleccionPadres( (Poblacion<GenomaX>::MetodoSeleccion)parametros.value( "metodo_seleccion" ).toInt() );
    pob.setearPorcentajeCantidadDePadres( parametros.value( "cantidad_padres" ).toDouble() );

    double max = parametros.value( "max" ).toDouble();
    double min = parametros.value( "min" ).toDouble();
    pob.setearMinMax( min, max );
    for( int i=0; i<cant_total; i++ ) {
        GenomaX temp;
        double valor = valor_random( min, max );
        temp.setX( valor );
        temp.setMinMax( min, max );
        pob.append( temp );
    }

    // Grafico la funcion
    QVector<double> posy, posx;
    for( double i=min; i<max; i++ ) {
        posx.append( i );
        posy.append( evaluar( i ) );
    }
    grafFuncion->agregarCurva( posx, posy, "funcion" );
    a.processEvents();

    double fitnes_necesario = parametros.value( "fitnes_necesario", 0.0 ).toDouble();

    int iteracciones_maximas = parametros.value( "iteracciones_maximas", 1000 ).toInt();
    int iteracciones = 0;
    PBTiempo->setRange( 0, iteracciones_maximas );

    pob.evaluarPoblacion();
    a.processEvents();

    QVector<double> histFitness;
    QVector<int> histIteracion;
    QVector<double> histPromFitnes;
    histFitness.append( pob.mejorFitnes() );
    histIteracion.append( 0 );
    histPromFitnes.append( pob.mejorFitnes() );

    double mejor_fitness = 0.0;
    double pos_mejor_fitness = 0.0;
    int generacion_mejor_fitness = -1;

    while( pob.mejorFitnes() <= fitnes_necesario
        && iteracciones <= iteracciones_maximas ) {

        pob.seleccionarPadres();
        a.processEvents();

        pob.generarHijos();
        a.processEvents();

        pob.evaluarPoblacion();
        a.processEvents();

        iteracciones++;
        PBTiempo->setValue( iteracciones );

        histFitness.append( pob.mejorFitnes() );
        histIteracion.append( iteracciones );
        grafFitnes->setearPuntos( histFitness, histIteracion );
        a.processEvents();

        QVector<double> x, y;
        double sumatoria = 0.0;
        for( int i=0; i<pob.size(); i++ ) {
            y.append( i );
            x.append( pob.at( i ).getX() );
            sumatoria += (-1.0)*evaluar( pob.at( i ).getX() );
        }
        sumatoria /=  pob.size();
        histPromFitnes.append( sumatoria );
        grafPuntos->agregarCurva( x, y, QString( "Gen%1" ).arg( iteracciones ) );

        if( mejor_fitness <= pob.mejorFitnes() ) {
            mejor_fitness = pob.mejorFitnes();
            pos_mejor_fitness = pob.posicionMinimo();
            generacion_mejor_fitness = iteracciones;
        }
        grafPromedio->setearPuntos( histPromFitnes, histIteracion );

    }

    qDebug() << "Mejor Fitness: " << mejor_fitness;
    qDebug() << "Posicion Minimo: " << pos_mejor_fitness;
    qDebug() << "Minimo: " << evaluar( pos_mejor_fitness );
    qDebug() << "Generacion: " << generacion_mejor_fitness;
    return a.exec();
}
