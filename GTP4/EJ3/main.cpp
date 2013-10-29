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
//    QMainWindow main;
//    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
//    main.showMaximized();
//    QMdiArea *mdiArea = new QMdiArea;
//    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    main.setCentralWidget(mdiArea);

//    // barra de progreso para mostrar el avance del tiempo
//    QDockWidget *dockBarra = new QDockWidget( QString::fromUtf8( "Paso del tiempo" ) );
//    main.addDockWidget( Qt::BottomDockWidgetArea, dockBarra );
//    QProgressBar *PBTiempo = new QProgressBar( dockBarra );
//    dockBarra->setWidget( PBTiempo );

    //Inicializo con una semilla aleatoria para la generacion de Aleatorios
    qsrand( QTime::currentTime().msec() );

    // Cargo los parametros del ejercicio
    //QSettings parametros( "parametros.cfg", QSettings::IniFormat );

    //Funcion 1
    int cant_particulas1 = 50;
    double x1_max = 512.0;
    double x1_min = -512.0;
    double tasa_error1 = 0.1;

    enjambre funcion1(cant_particulas1,x1_min,x1_max,tasa_error1,1);
    int it1 = funcion1.optimizar();

    qDebug() << "-----Funcion 1-----";
    qDebug() << "Cantidad de Particulas: " << cant_particulas1;
    qDebug() << "Limites: X(" << x1_min << "," << x1_max << ")";
    qDebug() << "Tasa de error: " << tasa_error1 << "%";
    qDebug() << "Cantidad de Iteraciones: " << it1;
    qDebug() << "Minimo de la Funcion: " << funcion1.devuelveValorMinimoGlobal();
    qDebug() << "Posicion del Minimo: " << funcion1.devuelvePosicionMinimoGlobal();

    //Funcion 2 (tomo 1000 valores entre 0 y 20)
    int cant_particulas2 = 10;
    double x2_max = 20.0;
    double x2_min = 0.0;
    double tasa_error2 = 0.1;

    enjambre funcion2(cant_particulas2,x2_min,x2_max,tasa_error2,2);
    int it2 = funcion2.optimizar();

    qDebug() << "-----Funcion 2-----";
    qDebug() << "Cantidad de Particulas: " << cant_particulas2;
    qDebug() << "Limites: X(" << x2_min << "," << x2_max << ")";
    qDebug() << "Tasa de error: " << tasa_error2 << "%";
    qDebug() << "Cantidad de Iteraciones: " << it2;
    qDebug() << "Minimo de la Funcion: " << funcion2.devuelveValorMinimoGlobal();
    qDebug() << "Posicion del Minimo: " << funcion2.devuelvePosicionMinimoGlobal();

    //Funcion 3
    int cant_particulas3 = 20;
    double x3_max = 100.0;
    double x3_min = -100.0;
    double y3_max = 100.0;
    double y3_min = -100.0;
    double tasa_error3 = 0.1;

    enjambre_parametrico funcion3(cant_particulas3,x3_min,x3_max,y3_min,y3_max,tasa_error3);
    int it3 = funcion3.optimizar();

    qDebug() << "-----Funcion 3-----";
    qDebug() << "Cantidad de Particulas: " << cant_particulas3;
    qDebug() << "Limites: X(" << x3_min << "," << x3_max << ") Y(" << y3_min << "," << y3_max << ")";
    qDebug() << "Tasa de error: " << tasa_error3 << "%";
    qDebug() << "Cantidad de Iteraciones: " << it3;
    qDebug() << "Minimo de la Funcion: " << funcion3.devuelveValorMinimoGlobal();
    qDebug() << "Posicion del Minimo: " << funcion3.devuelvePosicionMinimoGlobal();

    return a.exec();
}
