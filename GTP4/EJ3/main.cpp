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
#include "enjambre.h"
#include "enjambre_parametrico.h"

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
    QDockWidget *dockBarra = new QDockWidget( QString::fromUtf8( "Paso del tiempo" ) );
    main.addDockWidget( Qt::BottomDockWidgetArea, dockBarra );
    QProgressBar *PBTiempo = new QProgressBar( dockBarra );
    dockBarra->setWidget( PBTiempo );

    //Inicializo con una semilla aleatoria para la generacion de Aleatorios
    qsrand( QTime::currentTime().msec() );

    // Cargo los parametros del ejercicio
    //QSettings parametros( "parametros.cfg", QSettings::IniFormat );

    //Funcion 1
    enjambre funcion1(1024,512.0,-512.0,5.0);
    funcion1.optimizar(1);


    //Funcion 2 (tomo 1000 valores entre 0 y 20)
    enjambre funcion2(1000,20.0,0.0,5.0);
    funcion2.optimizar(2);


    enjambre_parametrico funcion3(200,100.0,-100.0,100.0,-100.0,5.0);
    funcion3.optimizar();

    return a.exec();
}
