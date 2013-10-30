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

#include "funciones_aux.h"
#include "genomax.h"
#include "poblacion.h"

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

    /*GraficadorMdi *grafTemperatura = new GraficadorMdi( mdiArea );
    grafTemperatura->setearTitulo( QString::fromUtf8( "Temperatura Interior" ) );
    grafTemperatura->setearTituloEjeX( QString::fromUtf8( "Tiempo" ) );
    grafTemperatura->setearTituloEjeY( QString::fromUtf8( "Temperatura" ) );
    mdiArea->addSubWindow( grafTemperatura );
    grafTemperatura->show();
    mdiArea->tileSubWindows();
    grafTemperatura->setearParaTrapezoide();*/

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
    int cant_total = parametros.value( "cant_elementos" ).toInt();
    pob.setearTotal( cant_total );

    pob.setearElitismo( parametros.value( "elitismo", false ).toBool() );
    pob.setearBrechaGeneracional( parametros.value( "brecha_generacional" ).toInt() );
    pob.setearProbabilidadMutacion( parametros.value( "probabilidad_mutacion").toDouble() );
    pob.setearModoSeleccionPadres( (Poblacion<GenomaX>::MetodoSeleccion)parametros.value( "metodo_seleccion" ).toInt() );

    double max = parametros.value( "max" ).toDouble();
    double min = parametros.value( "min" ).toDouble();
    for( int i=0; i<cant_total; i++ ) {
        GenomaX temp;
        temp.setX( valor_random( min, max ) );
        pob.append( temp );
    }

    double fitnes_necesario = parametros.value( "fitnes_necesario", 0.0 ).toDouble();

    int iteracciones_maximas = parametros.value( "iteracciones_maximas", 1000 ).toInt();
    int iteracciones = 0;
    PBTiempo->setRange( 0, iteracciones_maximas );

    pob.evaluarPoblacion();

    while( pob.mejorFitnes() > fitnes_necesario
        && iteracciones <= iteracciones_maximas ) {

        pob.seleccionarPadres();
        pob.generarHijos();
        pob.evaluarPoblacion();

        iteracciones++;
        PBTiempo->setValue( iteracciones );
    }

    return a.exec();
}
