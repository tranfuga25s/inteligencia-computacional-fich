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


    som.setearRadioVecindad( parametros.value( "radio_vecindad").toInt() );
    som.setearLimiteVecindad( parametros.value( "limite_vecindad" ).toDouble() );

    graf1->setearParaSOM();
    graf1->setearPuntos( som.obtenerPuntos() );
    //graf1->deshabilitarEscalado();

    GraficadorMdi *graf3 = new GraficadorMdi( mdiArea );
    graf3->setearTitulo( QString::fromUtf8( "Funcion de vecindad" ) );
    graf3->setearTituloEjeX( QString::fromUtf8( "X" ) );
    graf3->setearTituloEjeY( QString::fromUtf8( "Y" ) );
    mdiArea->addSubWindow( graf3 );
    QVector<double> nx, ny;
    int min = (-1)*parametros.value( "som_tam_x", 2 ).toInt() -1;
    int max = parametros.value( "som_tam_x", 2 ).toInt() +1;
    int medio = floor( ( max + min ) / 2 );
    for( int i = min; i<max; i++ ) {
        nx.append( i );
        ny.append( som.funcionVecindad( i, medio, medio, medio ).first() );
    }
    graf3->agregarCurva( nx, ny, "Gauseana" );
    graf3->show();
    mdiArea->tileSubWindows();

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

    QDockWidget *dockBarra5 = new QDockWidget( QString::fromUtf8( "Tasa de aprendizaje" ) );
    main.addDockWidget( Qt::BottomDockWidgetArea, dockBarra5 );
    QProgressBar *PBTasaAprendizaje = new QProgressBar( dockBarra5 );
    dockBarra5->setWidget( PBTasaAprendizaje );

    PBTasaAprendizaje->setRange( 0, 100 );
    PBTasaAprendizaje->setFormat( "Tasa %v/100" );

    QDockWidget *dockBarra1 = new QDockWidget( "Epocas de Ordenamiento Global" );
    main.addDockWidget( Qt::TopDockWidgetArea, dockBarra1 );
    QProgressBar *PBEpocas = new QProgressBar( dockBarra1 );
    dockBarra1->setWidget( PBEpocas );

    PBEpocas->setRange( 0, epocas.at( 0 ) );
    PBEpocas->setFormat( "Epoca %v de %m - %p%" );

    // Etapa de Ordenamiento Global --------------------------------------------------------------------
    //som.setearRadioVecindad( tamano_vecindad_inicial );
    //som.setearTasaAprendizaje( tasas.at( 0 ) );
    //PBTasaAprendizaje->setValue( tasas.at( 0 ) * 100 );

    PBEpocas->setRange( 0, epocas.at( 0 ) );
    PBEpocas->setFormat( "Epoca %v de %m - %p%" );

    QVector<int> tamano_vecindad1 = distribucionEquitativa( epocas.at( 0 ), 5 ,tamano_vecindad_inicial );
    QVector<double> tasa_aprendizajes1 = aproximacionLineald( epocas.at( 0 ), tasas.at( 0 ), tasas.at( 1 ) );

    for( int epoca=0; epoca<epocas.at(0); epoca++ ) {
        som.setearRadioVecindad( tamano_vecindad1.at( epoca ) );
        som.setearTasaAprendizaje( tasa_aprendizajes1.at( epoca ) );
        PBEpocas->setValue( epoca + 1 );
        PBTamanoVecindad->setValue( tamano_vecindad1.at( epoca ) );
        PBTasaAprendizaje->setValue( tasa_aprendizajes1.at( epoca ) * 100 );
        for( int p=0; p<entradas.size(); p++ ) {
            som.entrenar( entradas.at( p ) );
            graf1->setearPuntos( som.obtenerPuntos() );
            a.processEvents();
            som.cambiosSignificativos();
        }
    }

//    for( int epoca=0; epoca<epocas.at(0); epoca++ ) {
//        PBEpocas->setValue( epoca );
//        for( int p=0; p<entradas.size(); p++ ) {
//            som.entrenar( entradas.at( p ) );
//            graf1->setearPuntos( som.obtenerPuntos() );
//            a.processEvents();
//        }
//        graf1->setearPuntos( som.obtenerPuntos() );
//        a.processEvents();
//        som.cambiosSignificativos();
//    }

    // Etapa de transición -----------------------------------------------------------------------------
    QVector<int> tamano_vecindad2 = distribucionEquitativa( epocas.at( 1 ), 1, 5);
    QVector<double> tasa_aprendizajes2 = aproximacionLineald( epocas.at( 1 ), tasas.at( 1 ), tasas.at( 2 ) );

    GraficadorMdi *graf4 = new GraficadorMdi( mdiArea );
    graf4->setearTitulo( QString::fromUtf8( "Tasa de aprendizaje" ) );
    graf4->setearTituloEjeX( QString::fromUtf8( "X" ) );
    graf4->setearTituloEjeY( QString::fromUtf8( "Y" ) );
    mdiArea->addSubWindow( graf4 );
    nx.clear();
    for( int i=0; i<tasa_aprendizajes2.size(); i++ ) { nx.append( i ); }
    graf4->agregarCurva( nx, tasa_aprendizajes2, "Tasa Aprendizaje" );
    graf4->show();
    mdiArea->tileSubWindows();

    GraficadorMdi *graf5 = new GraficadorMdi( mdiArea );
    graf5->setearTitulo( QString::fromUtf8( "Funcion de vecindad" ) );
    graf5->setearTituloEjeX( QString::fromUtf8( "X" ) );
    graf5->setearTituloEjeY( QString::fromUtf8( "Y" ) );
    mdiArea->addSubWindow( graf5 );
    nx.clear();
    ny.clear();
    for( int i=0; i<tamano_vecindad2.size(); i++ ) { nx.append( i ); ny.append( tamano_vecindad2.at( i ) ); }
    graf5->agregarCurva( nx, ny, "Tasa Aprendizaje" );
    graf5->show();
    mdiArea->tileSubWindows();

    dockBarra1->setWindowTitle( QString::fromUtf8( "Epocas de transición" ) );

    PBEpocas->setRange( 0, epocas.at( 1 ) );
    PBEpocas->setFormat( "Epoca %v de %m - %p%" );

    for( int epoca=0; epoca<epocas.at(1); epoca++ ) {
        som.setearRadioVecindad( tamano_vecindad2.at( epoca ) );
        som.setearTasaAprendizaje( tasa_aprendizajes2.at( epoca ) );
        PBEpocas->setValue( epoca + 1 );
        PBTamanoVecindad->setValue( tamano_vecindad2.at( epoca ) );
        PBTasaAprendizaje->setValue( tasa_aprendizajes2.at( epoca ) * 100 );
        for( int p=0; p<entradas.size(); p++ ) {
            som.entrenar( entradas.at( p ) );
            graf1->setearPuntos( som.obtenerPuntos() );
            a.processEvents();
            som.cambiosSignificativos();
        }
    }

    // Etapa de ajuste fino ----------------------------------------------------------------------------
    dockBarra1->setWindowTitle( "Epocas de ajuste fino" );

    PBEpocas->setRange( 0, epocas.at( 2 ) );
    PBEpocas->setFormat( "Epoca %v de %m - %p%" );

    som.setearRadioVecindad( 0 );
    tasa_aprendizajes2 = aproximacionLineald( epocas.at( 2 ), tasas.at( 2 ), tasas.at( 3 ) );

    for( int epoca=0; epoca<epocas.at(2); epoca++ ) {

        som.setearTasaAprendizaje( tasa_aprendizajes2.at( epoca ) );
        PBEpocas->setValue( epoca + 1 );
        PBTasaAprendizaje->setValue( tasa_aprendizajes2.at( epoca )  * 100 );

        for( int p=0; p<entradas.size(); p++ ) {
            som.entrenar( entradas.at( p ) );
            graf1->setearPuntos( som.obtenerPuntos() );
            a.processEvents();
            som.cambiosSignificativos();
        }

    }

    return a.exec();

}
