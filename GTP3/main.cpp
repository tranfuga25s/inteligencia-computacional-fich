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
#include "controladordifuso.h"

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
    grafTemperatura->setearParaSOM( "Temp" );

    GraficadorMdi *grafTemperaturaExterior = new GraficadorMdi( mdiArea );
    grafTemperaturaExterior->setearTitulo( QString::fromUtf8( "Temperatura Exterior" ) );
    grafTemperaturaExterior->setearTituloEjeX( QString::fromUtf8( "Tiempo" ) );
    grafTemperaturaExterior->setearTituloEjeY( QString::fromUtf8( "Temperatura" ) );
    mdiArea->addSubWindow( grafTemperaturaExterior );
    grafTemperaturaExterior->show();
    mdiArea->tileSubWindows();
    grafTemperaturaExterior->setearParaSOM( "Temp" );

    GraficadorMdi *grafTemperaturaDeseada = new GraficadorMdi( mdiArea );
    grafTemperaturaDeseada->setearTitulo( QString::fromUtf8( "Temperatura Deseada" ) );
    grafTemperaturaDeseada->setearTituloEjeX( QString::fromUtf8( "Tiempo" ) );
    grafTemperaturaDeseada->setearTituloEjeY( QString::fromUtf8( "Temperatura" ) );
    mdiArea->addSubWindow( grafTemperaturaDeseada );
    grafTemperaturaDeseada->show();
    mdiArea->tileSubWindows();
    grafTemperaturaDeseada->setearParaSOM( "Temp" );

    // barra de progreso para mostrar el avance del tiempo
    QDockWidget *dockBarra = new QDockWidget( QString::fromUtf8( "Paso del tiempo" ) );
    main.addDockWidget( Qt::BottomDockWidgetArea, dockBarra );
    QProgressBar *PBTiempo = new QProgressBar( dockBarra );
    dockBarra->setWidget( PBTiempo );

    //Inicializo con una semilla aleatoria para la generacion de Aleatorios
    qsrand( QTime::currentTime().msec() );

    // Cargo los parametros del ejercicio
    QSettings parametros( "parametros.cfg", QSettings::IniFormat );

    /// @TODO
    ///faltaria definir la matriz de entradas y la de salidas que estarian
    ///ya codificadas describiendo los puntos de los trapecios

    // Genero el entorno que voy a controlar
    Entorno entorno( 0, parametros.value("pa_puerta").toDouble() );
    // Seteo los valores iniciales
    entorno.setearTemperaturaExterna( parametros.value("temp_ext").toDouble() );
    entorno.setearTemperaturaInterna( parametros.value("temp_ini_int").toDouble() );


    PBTiempo->setRange( 0, parametros.value("cant_segundos").toInt() );
    PBTiempo->setValue(0);

    Exterior exterior;
    exterior.setearTemperaturaSuperior( parametros.value("temp_ext_max").toDouble() );
    exterior.setearTemperaturaInferior( parametros.value("temp_ext_min").toDouble() );
    exterior.setearTiempoCambio( parametros.value("temp_ext_cambio").toInt() );

    Exterior deseada;
    deseada.setearTemperaturaInferior( parametros.value("temp_deseada_max").toDouble() );
    deseada.setearTemperaturaSuperior( parametros.value("temp_deseada_min").toDouble() );
    deseada.setearTiempoCambio( parametros.value("temp_deseada_cambio").toInt() );

    ControladorDifuso controlador;
    parametros.beginGroup( "Entradas" );
    foreach( QString clave, parametros.allKeys() ) {
        // Clave es el nombre del grupo
        controlador.agregarConjuntoEntrada( clave, stringAQVectord( parametros.value( clave ).toString() ) );
    }
    parametros.endGroup();

    parametros.beginGroup( "Salidas" );
    parametros.beginGroup( "voltaje" );
    foreach( QString clave, parametros.allKeys() ) {
        // Clave es el nombre del grupo
        controlador.agregarConjuntoSalidaVoltaje( clave, stringAQVectord( parametros.value( clave ).toString() ) );
    }
    parametros.endGroup();
    parametros.beginGroup("intensidad");
    foreach( QString clave, parametros.allKeys() ) {
        // Clave es el nombre del grupo
        controlador.agregarConjuntoSalidaIntensidad( clave, stringAQVectord( parametros.value( clave ).toString() ) );
    }
    parametros.endGroup();
    parametros.endGroup();

    parametros.beginGroup( "Reglas" );
    parametros.beginGroup( "voltaje" );
    foreach( QString clave, parametros.allKeys() ) {
        foreach( int conjunto_salida, stringAQVector( parametros.value( clave ).toString() ) ) {
            controlador.agregarReglaVoltaje( clave.toInt(), conjunto_salida );
        }
    }
    parametros.endGroup();
    parametros.beginGroup("intensidad");
    foreach( QString clave, parametros.allKeys() ) {
        foreach( int conjunto_salida, stringAQVector( parametros.value( clave ).toString() ) ) {
            controlador.agregarReglaIntensidad( clave.toInt(), conjunto_salida );
        }
    }
    parametros.endGroup();
    parametros.endGroup();

    int intervalo = parametros.value( "t_act").toInt();
    int cant_total = parametros.value("cant_segundos").toInt();

    QVector<int> escala_tiempo;

    for( int i=0; i<cant_total; i+=intervalo ) {

        escala_tiempo.append( i );

        // Coloco la temperatura interior en el controlador
        controlador.setearTemperaturaInterior( entorno.temperaturaActual() );
        controlador.setearTemperaturaDeseada ( deseada.getTemperatura( i ) );

        // Genero todos los pasos para que se actualize la temperatura interior
        entorno.setearTemperaturaExterna( exterior.getTemperatura( i ) );
        entorno.setearPotenciaEstufa( controlador.getIntensidad() );
        entorno.setearVoltajeRefrigeracion( controlador.getVoltaje() );
        // La puerta se maneja de manera interna

        entorno.calcularTemperaturaTiempo();

        // Grafico el paso
        grafTemperatura->setearPuntos( entorno.historicoTemperatura(), escala_tiempo );
        grafTemperaturaExterior->setearPuntos( exterior.getHistoricoTemperatura(), escala_tiempo );
        grafTemperaturaDeseada->setearPuntos( deseada.getHistoricoTemperatura(), escala_tiempo );

        PBTiempo->setValue( i+1 );

    }

    return a.exec();

}
