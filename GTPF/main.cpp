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
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>
#include <QMdiSubWindow>
#include <QTableView>

#include "iostream"

typedef QVector<double> vector;
typedef QVector< QVector<double> > matriz;

#include "graficadormdi.h"
#include "evaluarVentana.h"
#include "poblacion.h"
#include "GenomaVentana.h"

/*!
 * \brief main
 * TP FINAL OPTIMIZACION DE VENTANAS
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

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName( "aberturas.sqlite" );
    if( !db.open() ) {
        qDebug() << "No se pudo abrir la base de datos";
        abort();
    }

    QSqlTableModel modelo;
    modelo.setTable( "aberturas" );
    modelo.select();
    modelo.setHeaderData( 0, Qt::Horizontal, "#ID" );
    modelo.setHeaderData( 1, Qt::Horizontal, "Nombre" );
    modelo.setHeaderData( 2, Qt::Horizontal, "Ancho Base" );
    modelo.setHeaderData( 3, Qt::Horizontal, "Alto Base" );
    modelo.setHeaderData( 4, Qt::Horizontal, "Maximo Alto" );
    modelo.setHeaderData( 5, Qt::Horizontal, "Minimo Alto" );
    modelo.setHeaderData( 6, Qt::Horizontal, "Maximo Acho" );
    modelo.setHeaderData( 7, Qt::Horizontal, "Minimo Ancho" );
    modelo.setHeaderData( 8, Qt::Horizontal, "Cantida de repeticiones" );

    QVector<TemplateVentana> data;
    for( int i=0; i<modelo.rowCount(); i++ ) {
        TemplateVentana temp;
        QSqlRecord r = modelo.record( i );
        temp.setearNombre( r.value( "nombre" ).toString() );
        temp.setearTipo( r.value( "id_abertura" ).toInt() );
        temp.setearAncho( r.value( "ancho" ).toDouble() );
        temp.setearAlto( r.value( "alto" ).toDouble() );
        temp.setearMaxAlto( r.value( "max_alto" ).toDouble() );
        temp.setearMinAlto( r.value( "min_alto" ).toDouble() );
        temp.setearMaxAncho( r.value( "max_ancho" ).toDouble() );
        temp.setearMinAncho( r.value( "max_ancho" ).toDouble() );
        temp.setearCantidad( r.value("cantidad").toInt() );
        qDebug() << "Cargada abertura " << temp.nombre();
        data.append( temp );
        qDebug() << temp.ancho() << temp.alto();
    }

    QMdiSubWindow *tiposVentanas = new QMdiSubWindow( mdiArea );
    QTableView *tablaTipos = new QTableView( tiposVentanas );
    tiposVentanas->setWidget( tablaTipos );
    tablaTipos->setModel( &modelo );
    mdiArea->addSubWindow( tiposVentanas );

    /*GraficadorMdi *grafFuncion = new GraficadorMdi( mdiArea );
    grafFuncion->setearTitulo( QString::fromUtf8( "Funcion" ) );
    grafFuncion->setearTituloEjeX( QString::fromUtf8( "X" ) );
    grafFuncion->setearTituloEjeY( QString::fromUtf8( "Y" ) );
    mdiArea->addSubWindow( grafFuncion );
    grafFuncion->show();
    mdiArea->tileSubWindows();*/

    GraficadorMdi *grafFitnes = new GraficadorMdi( mdiArea );
    grafFitnes->setearTitulo( QString::fromUtf8( "Evolucion Mejor Fitness" ) );
    grafFitnes->setearTituloEjeX( QString::fromUtf8( "Generacion" ) );
    grafFitnes->setearTituloEjeY( QString::fromUtf8( "fitness" ) );
    mdiArea->addSubWindow( grafFitnes );
    grafFitnes->show();
    mdiArea->tileSubWindows();
    grafFitnes->setearParaSOM();

    /*GraficadorMdi *grafPuntos = new GraficadorMdi( mdiArea );
    grafPuntos->setearTitulo( QString::fromUtf8( "Puntos a evaluar" ) );
    grafPuntos->setearTituloEjeX( QString::fromUtf8( "Posicion" ) );
    grafPuntos->setearTituloEjeY( QString::fromUtf8( "Y" ) );
    mdiArea->addSubWindow( grafPuntos );
    grafPuntos->show();
    mdiArea->tileSubWindows();
    //grafPuntos->setearParaSOM();
   // grafPuntos->setearEjesEnGrafico();
   */

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
    a.processEvents();

    // Inicializo la poblacion
    Poblacion<GenomaVentana> pob;
    int cant_total = parametros.value( "cantidad_elementos" ).toInt();
    pob.setearTotal( cant_total );

    pob.setearElitismo( parametros.value( "elitismo", false ).toBool() );
    pob.setearBrechaGeneracional( parametros.value( "brecha_generacional" ).toDouble() );
    pob.setearProbabilidadMutacion( parametros.value( "probabilidad_mutacion").toDouble() );
    pob.setearProbabilidadCruza( parametros.value( "probabilidad_cruza").toDouble() );
    pob.setearModoSeleccionPadres( (Poblacion<GenomaVentana>::MetodoSeleccion)parametros.value( "metodo_seleccion" ).toInt() );
    pob.setearPorcentajeCantidadDePadres( parametros.value( "cantidad_padres" ).toDouble() );

    double fitnes_necesario = parametros.value( "fitnes_necesario", 0.0 ).toDouble();

    int iteracciones_maximas = parametros.value( "iteracciones_maximas", 1000 ).toInt();
    int iteracciones = 0;
    PBTiempo->setRange( 0, iteracciones_maximas );


    // Cargo la poblacion
    for( int i=0; i<cant_total; i++ ) {
        GenomaVentana temporal;
        temporal.setearTemplates( data );
        temporal.iniciarRandomizado();
        pob.append( temporal );
    }

    pob.evaluarPoblacionVentana();
    a.processEvents();

    /// Sucede que el fitness que me devuelve evaluar ventana mientras mas cerca este de 0
    ///mejor, por eso devuelve numeros negativos, tiende a 0. Ahora en pobacion el fitness
    ///para que sea positivo es -y entonces tengo que invertir la escala aca para que pueda
    ///entrar al while

    double mejor_fitness = pob.mejorFitnes();


    QVector<double> histFitness;
    QVector<int> histIteracion;
    QVector<double> histPromFitnes;
    histFitness.append( pob.mejorFitnes() );
    histIteracion.append( 0 );
    histPromFitnes.append( pob.mejorFitnes() );
    grafFitnes->setearPuntos( histFitness, histIteracion );
    a.processEvents();

    //GenomaVentana pos_mejor_fitness;
    int generacion_mejor_fitness = 0;


    while( pob.mejorFitnes() <= fitnes_necesario
        && iteracciones <= iteracciones_maximas ) {

        pob.seleccionarPadres();
        a.processEvents();

        pob.generarHijosVentana();
        a.processEvents();

        pob.evaluarPoblacionVentana();
        a.processEvents();

        iteracciones++;

        //GRAFICOS -------------------------

        PBTiempo->setValue( iteracciones );

        histFitness.append( pob.mejorFitnes() );
        histIteracion.append( iteracciones );
        grafFitnes->setearPuntos( histFitness, histIteracion );
        a.processEvents();

        QVector<double> x, y;
        double sumatoria = 0.0;
        for( int i=0; i<pob.size(); i++ ) {
            y.append( i );
            x.append( evaluarVentana( pob.at( i ) ) );
            sumatoria += evaluarVentana( pob.at( i ) );
        }
        sumatoria /=  pob.size();
        histPromFitnes.append( sumatoria );
        //grafPuntos->agregarCurva( x, y, QString( "Gen%1" ).arg( iteracciones ) );
        a.processEvents();


        qDebug() << "Mejor Fitness historico: "<<mejor_fitness;
        qDebug() << "Mejor Fitness: "<<pob.mejorFitnes();

        //--------------------------------------

        if( mejor_fitness <= pob.mejorFitnes() ) {

            qDebug() << "ENTRO a actualizar FITNESS VENTANA";
            mejor_fitness = pob.mejorFitnes();
            //pos_mejor_fitness = pob.elementoMinimo();
            generacion_mejor_fitness = iteracciones;
        }


        grafPromedio->setearPuntos( histPromFitnes, histIteracion );
        a.processEvents();

    }

    qDebug() << endl << "RESULTADO FINAL: ";


    qDebug() << "Mejor Fitness VENTANA: " << mejor_fitness;
    qDebug() << "Generacion: " <<  generacion_mejor_fitness;

    return a.exec();
}
