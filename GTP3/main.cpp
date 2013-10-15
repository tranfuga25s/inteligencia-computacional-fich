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
#include "entorno.h"
#include "exterior.h"
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

    GraficadorMdi *grafTemperatura = new GraficadorMdi( mdiArea );
    grafTemperatura->setearTitulo( QString::fromUtf8( "Temperatura Interior" ) );
    grafTemperatura->setearTituloEjeX( QString::fromUtf8( "Tiempo" ) );
    grafTemperatura->setearTituloEjeY( QString::fromUtf8( "Temperatura" ) );
    mdiArea->addSubWindow( grafTemperatura );
    grafTemperatura->show();
    mdiArea->tileSubWindows();

    // barra de progreso para mostrar el avance del tiempo
    QDockWidget *dockBarra = new QDockWidget( QString::fromUtf8( "Paso del tiempo" ) );
    main.addDockWidget( Qt::BottomDockWidgetArea, dockBarra );
    QProgressBar *PBTiempo = new QProgressBar( dockBarra );
    dockBarra->setWidget( PBTiempo );

    //Inicializo con una semilla aleatoria para la generacion de Aleatorios
    qsrand( QTime::currentTime().msec() );

    // Cargo los parametros del ejercicio
    QSettings parametros( "parametros.cfg", QSettings::IniFormat );

    // Genero el entorno que voy a controlar
    Entorno entorno( 0,
                     parametros.value("k1").toDouble(),
                     parametros.value("k2").toDouble(),
                     parametros.value("k3").toDouble(),
                     parametros.value("k4").toDouble(),
                     parametros.value("pa_puerta").toDouble()
                   );
    // Seteo los valores iniciales
    entorno.setearTemperaturaExterna( parametros.value("temp_ext").toDouble() );
    entorno.setearTemperaturaInterna( parametros.value("temp_int").toDouble() );

    PBTiempo->setRange( 0, parametros.value("cant_segundos").toInt() );
    PBTiempo->setValue(0);

    Exterior exterior;

    int intervalo = parametros.value( "t_act").toInt();
    int cant_total = parametros.value("cant_segundos").toInt();

    QVector<int> escala_tiempo;

    for( int i=0; i<cant_total; i+=intervalo ) {

        escala_tiempo.append( i );
        // Genero todos los pasos para que se actualize la temperatura interior

        entorno.setearTemperaturaExterna( exterior.getTemperaturaExterior( i ) );


        grafTemperatura->setearPuntos( entorno.historicoTemperatura(), escala_tiempo );
        PBTiempo->setValue( i );
    }

    return a.exec();

}
