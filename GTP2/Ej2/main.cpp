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
#include "graficadormdi.h"

typedef QVector<double> vector;
typedef QVector< QVector<double> > matriz;

#include "funciones_aux.h"

#include "som.h"

/*!
 * \brief main
 * Ejercicio 2 Guia de Trabajos Practicos 2
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

    //Inicializo con una semilla aleatoria para la generacion de Aleatorios
    qsrand( QTime::currentTime().msec() );

    // Cargo los parametros del ejercicio
    QSettings parametros( "parametros.cfg", QSettings::IniFormat );

    GraficadorMdi *graf1 = new GraficadorMdi( mdiArea );
    graf1->setearTitulo( QString::fromUtf8( "Organizacion" ) );
    graf1->setearTituloEjeX( QString::fromUtf8( "X" ) );
    graf1->setearTituloEjeY( QString::fromUtf8( "Y" ) );
    graf1->setearEjesEnGrafico();
    mdiArea->addSubWindow( graf1 );
    mdiArea->tileSubWindows();

    GraficadorMdi *graf2 = new GraficadorMdi( mdiArea );
    graf2->setearTitulo( QString::fromUtf8( "Datos Originales" ) );
    graf2->setearTituloEjeX( QString::fromUtf8( "X" ) );
    graf2->setearTituloEjeY( QString::fromUtf8( "Y" ) );
    graf2->setearEjesEnGrafico();
    mdiArea->addSubWindow( graf2 );
    mdiArea->tileSubWindows();

    // Archivo de entrada
    QString archivo = QCoreApplication::applicationDirPath().append( QDir::separator() ).append( parametros.value( "archivo_entrada" ).toString() );

    // Cargo los datos de los archivos que corresponda
    matriz entradas( parametros.value( "cantidad_entradas" ).toInt() );

    qDebug() << endl << "--------------- /Datos del entrenamiento/ -----------------" << endl;
    qWarning() << "Archivo de lectura de datos originales: "<< archivo;
    if( ! leer_archivo_entrenamiento( archivo,
                                      &entradas,
                                      parametros.value( "tamano_entradas" ).toInt() )  ) {
        qDebug() << "No se pudo encontrar el archivo de entrenamiento! cancelando!";
        abort();
    }

    // Dibujo las entradas
    graf2->agregarPuntos( entradas, "Datos originales" );
    a.processEvents();

    // Inicializo el SOM
    SOM som( parametros.value( "som_tam_x", 2 ).toInt(),
             parametros.value( "som_tam_y", 2 ).toInt(),
             parametros.value( "tamano_entradas" ).toInt() );

    graf1->setearParaSOM();
    graf1->setearPuntos( som.obtenerPuntos() );
    qDebug() << endl << "---------------- /Comienza el entrenamiento/ ----------------";

    QVector<int> epocas = stringAQVector( parametros.value( "epocas" ).toString() );
    QVector<double> tasas = stringAQVectord( parametros.value( "tasa_aprendizaje" ).toString() );
    int tamano_vecindad_inicial = parametros.value( "radio_vecindad").toInt();

    QDockWidget *dockBarra3 = new QDockWidget( QString::fromUtf8( "Tamaño Vecindad" ) );
    main.addDockWidget( Qt::BottomDockWidgetArea, dockBarra3 );
    QProgressBar *PBTamanoVecindad = new QProgressBar( dockBarra3 );
    dockBarra3->setWidget( PBTamanoVecindad );

    PBTamanoVecindad->setRange( 0, parametros.value( "som_tam_x", 2 ).toInt() );
    PBTamanoVecindad->setFormat( "%v neuronas de %m - %p%" );
    PBTamanoVecindad->setValue( tamano_vecindad_inicial );

    QDockWidget *dockBarra5 = new QDockWidget( QString::fromUtf8( "Tasa de apredizaje" ) );
    main.addDockWidget( Qt::BottomDockWidgetArea, dockBarra5 );
    QProgressBar *PBTasaAprendizaje = new QProgressBar( dockBarra5 );
    dockBarra5->setWidget( PBTasaAprendizaje );

    PBTasaAprendizaje->setRange( 0, 100 );
    PBTasaAprendizaje->setFormat( "Tasa %v/100" );

    QDockWidget *dockBarra1 = new QDockWidget( "Epocas de Ordenamiento Global" );
    main.addDockWidget( Qt::TopDockWidgetArea, dockBarra1 );
    QProgressBar *PBEpocasOrdenamiento = new QProgressBar( dockBarra1 );
    dockBarra1->setWidget( PBEpocasOrdenamiento );

    PBEpocasOrdenamiento->setRange( 0, epocas.at( 0 ) );
    PBEpocasOrdenamiento->setFormat( "Epoca %v de %m - %p%" );

    // Etapa de Ordenamiento Global
    som.setearRadioVecindad( tamano_vecindad_inicial );
    som.setearTasaAprendizaje( tasas.at( 0 ) );
    PBTasaAprendizaje->setValue( tasas.at( 0 ) );

    for( int epoca=0; epoca<epocas.at(0); epoca++ ) {
        PBEpocasOrdenamiento->setValue( PBEpocasOrdenamiento->value() + 1 );
        for( int p=0; p<entradas.size(); p++ ) {
            som.entrenar( entradas.at( p ) );
            graf1->setearPuntos( som.obtenerPuntos() );
            a.processEvents();
        }
    }
    return a.exec();
    // Etapa de transición
    QVector<int> tamano_vecindad = aproximacionLineal( epocas.at( 1 ), tamano_vecindad_inicial, 1 );
    QVector<double> tasa_aprendizajes = aproximacionLineald( epocas.at( 1 ), tasas.at( 0 ), tasas.at( 1 ) );

    QDockWidget *dockBarra2 = new QDockWidget( "Epocas de transición" );
    main.addDockWidget( Qt::TopDockWidgetArea, dockBarra2 );
    QProgressBar *PBEpocasTransicion = new QProgressBar( dockBarra2 );
    dockBarra2->setWidget( PBEpocasTransicion );

    PBEpocasTransicion->setRange( 0, epocas.at( 1 ) );
    PBEpocasTransicion->setFormat( "Epoca %v de %m - %p%" );

    for( int epoca=0; epoca<epocas.at(0); epoca++ ) {
        som.setearRadioVecindad( tamano_vecindad.at( epoca ) );
        som.setearTasaAprendizaje( tasa_aprendizajes.at( epoca ) );
        PBEpocasTransicion->setValue( PBEpocasTransicion->value() + 1 );
        PBTamanoVecindad->setValue( tamano_vecindad.at( epoca ) );
        PBTasaAprendizaje->setValue( tasa_aprendizajes.at( epoca ) );
        for( int p=0; p<entradas.size(); p++ ) {
            som.entrenar( entradas.at( p ) );
            graf1->setearPuntos( som.obtenerPuntos() );
            a.processEvents();
        }
    }

    // Etapa de ajuste fino
    QDockWidget *dockBarra4 = new QDockWidget( "Epocas de ajuste fino" );
    main.addDockWidget( Qt::TopDockWidgetArea, dockBarra4 );
    QProgressBar *PBEpocasFino = new QProgressBar( dockBarra4 );
    dockBarra4->setWidget( PBEpocasFino );

    PBEpocasFino->setRange( 0, epocas.at( 2 ) );
    PBEpocasFino->setFormat( "Epoca %v de %m - %p%" );

    som.setearRadioVecindad( 0 );
    tasa_aprendizajes = aproximacionLineald (epocas.at( 2 ), tasas.at( 1 ), tasas.at( 2 ) );

    for( int epoca=0; epoca<epocas.at(0); epoca++ ) {

        som.setearTasaAprendizaje( tasa_aprendizajes.at( epoca ) );
        PBEpocasFino->setValue( epoca );
        PBTasaAprendizaje->setValue( tasa_aprendizajes.at( epoca ) );

        for( int p=0; p<entradas.size(); p++ ) {
            som.entrenar( entradas.at( p ) );
            graf1->setearPuntos( som.obtenerPuntos() );
            a.processEvents();
        }

    }

    return a.exec();

}
