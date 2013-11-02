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

    // barra de progreso para mostrar el avance del tiempo
    QDockWidget *dockBarra = new QDockWidget( QString::fromUtf8( "Paso del tiempo" ) );
    main.addDockWidget( Qt::BottomDockWidgetArea, dockBarra );
    QProgressBar *PBTiempo = new QProgressBar( dockBarra );
    dockBarra->setWidget( PBTiempo );

    //Defino los graficos
    //Funcion 1
    GraficadorMdi *grafPuntos1 = new GraficadorMdi( mdiArea );
    grafPuntos1->setearTitulo( QString::fromUtf8( "Funcion 1" ) );
    grafPuntos1->setearTituloEjeX( QString::fromUtf8( "X" ) );
    grafPuntos1->setearTituloEjeY( QString::fromUtf8( "Y" ) );
    mdiArea->addSubWindow( grafPuntos1 );
    grafPuntos1->show();
    mdiArea->tileSubWindows();
    //Funcion 2
    GraficadorMdi *grafPuntos2 = new GraficadorMdi( mdiArea );
    grafPuntos2->setearTitulo( QString::fromUtf8( "Funcion 2" ) );
    grafPuntos2->setearTituloEjeX( QString::fromUtf8( "X" ) );
    grafPuntos2->setearTituloEjeY( QString::fromUtf8( "Y" ) );
    mdiArea->addSubWindow( grafPuntos2 );
    grafPuntos2->show();
    mdiArea->tileSubWindows();
    //Funcion 3
    GraficadorMdi *grafPuntos3 = new GraficadorMdi( mdiArea );
    grafPuntos3->setearTitulo( QString::fromUtf8( "Funcion 3" ) );
    grafPuntos3->setearTituloEjeX( QString::fromUtf8( "X" ) );
    grafPuntos3->setearTituloEjeY( QString::fromUtf8( "Y" ) );
    mdiArea->addSubWindow( grafPuntos3 );
    grafPuntos3->show();
    mdiArea->tileSubWindows();

    //Inicializo con una semilla aleatoria para la generacion de Aleatorios
    qsrand( QTime::currentTime().msec() );

    // Cargo los parametros del ejercicio
    QSettings parametros( "parametros.cfg", QSettings::IniFormat );

    //Funcion 1
    int cant_particulas1 = parametros.value("cant_particulas1").toInt();
    double x1_max = parametros.value("x1_max").toDouble();
    double x1_min = parametros.value("x1_min").toDouble();;
    double tasa_error1 = parametros.value("tasa_error1").toDouble();;

    enjambre funcion1(cant_particulas1,x1_min,x1_max,tasa_error1,1);
    int it1 = funcion1.optimizar();

    //Grafico Funcion 1
    QVector<double> x1, y1;
    for( int i=x1_min; i<=x1_max; i++ ) {
        y1.append( funcion1.evaluarFuncion(i) );
        x1.append( i );
    }
    grafPuntos1->agregarCurva( x1, y1, QString( "generacion %1" ).arg( x1_max - x1_min ) );

    qDebug() << "-----Funcion 1-----";
    qDebug() << "Cantidad de Particulas: " << cant_particulas1;
    qDebug() << "Limites: X(" << x1_min << "," << x1_max << ")";
    qDebug() << "Tasa de error: " << tasa_error1 << "%";
    qDebug() << "Cantidad de Iteraciones: " << it1;
    qDebug() << "Minimo de la Funcion: " << funcion1.devuelveValorMinimoGlobal();
    qDebug() << "Posicion del Minimo: " << funcion1.devuelvePosicionMinimoGlobal();

    //Funcion 2 (tomo 1000 valores entre 0 y 20)
    int cant_particulas2 = parametros.value("cant_particulas2").toInt();;
    double x2_max = parametros.value("x2_max").toDouble();
    double x2_min = parametros.value("x2_min").toDouble();;
    double tasa_error2 = parametros.value("tasa_error2").toDouble();;

    enjambre funcion2(cant_particulas2,x2_min,x2_max,tasa_error2,2);
    int it2 = funcion2.optimizar();

    //Grafico Funcion 2
    QVector<double> x2, y2;
    for( int i=x2_min; i<=x2_max; i++ ) {
        y2.append( funcion2.evaluarFuncion(i) );
        x2.append( i );
    }
    grafPuntos2->agregarCurva( x2, y2, QString( "generacion %1" ).arg( x2_max - x2_min ) );

    qDebug() << "-----Funcion 2-----";
    qDebug() << "Cantidad de Particulas: " << cant_particulas2;
    qDebug() << "Limites: X(" << x2_min << "," << x2_max << ")";
    qDebug() << "Tasa de error: " << tasa_error2 << "%";
    qDebug() << "Cantidad de Iteraciones: " << it2;
    qDebug() << "Minimo de la Funcion: " << funcion2.devuelveValorMinimoGlobal();
    qDebug() << "Posicion del Minimo: " << funcion2.devuelvePosicionMinimoGlobal();

    //Funcion 3
    int cant_particulas3 = parametros.value("cant_particulas3").toInt();;
    double x3_max = parametros.value("x3_max").toDouble();;
    double x3_min = parametros.value("x3_min").toDouble();;
    double y3_max = parametros.value("y3_max").toDouble();;
    double y3_min = parametros.value("y3_min").toDouble();;
    double tasa_error3 = parametros.value("tasa_error3").toDouble();;

    enjambre_parametrico funcion3(cant_particulas3,x3_min,x3_max,y3_min,y3_max,tasa_error3);
    int it3 = funcion3.optimizar();

    //Grafico Funcion 3
    QVector<double> x3, y3;
    for( int i=x3_min; i<=x3_max; i++ ) {
        y3.append( funcion3.evaluarFuncion(i,0) );
        x3.append( i );
    }
    grafPuntos3->agregarCurva( x3, y3, QString( "generacion %1" ).arg( x3_max - x3_min ) );

    qDebug() << "-----Funcion 3-----";
    qDebug() << "Cantidad de Particulas: " << cant_particulas3;
    qDebug() << "Limites: X(" << x3_min << "," << x3_max << ") Y(" << y3_min << "," << y3_max << ")";
    qDebug() << "Tasa de error: " << tasa_error3 << "%";
    qDebug() << "Cantidad de Iteraciones: " << it3;
    qDebug() << "Minimo de la Funcion: " << funcion3.devuelveValorMinimoGlobal();
    qDebug() << "Posicion del Minimo: " << funcion3.devuelvePosicionMinimoGlobal();

    return a.exec();
}
