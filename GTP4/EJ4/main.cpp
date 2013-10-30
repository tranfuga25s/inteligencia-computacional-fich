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
#include "redneuronal.h"
#include "capaneuronal.h"

typedef QVector<double> vector;
typedef QVector< QVector<double> > matriz;

#include "funciones_aux.h"
#include "neurona.h"
#include "particionador.h"
#include "enjambre.h"

/*!
 * \brief main
 * Ejercicio 4 Guia de Trabajos Practicos 4
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

    QFile arch( "pesos.csv" );
    arch.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate );
    //QTextStream pesos( &arch );

    //Inicializo con una semilla aleatoria para la generacion de Aleatorios
    qsrand( QTime::currentTime().msec() );

    // Cargo los parametros del ejercicio
    QSettings parametros( "parametros.cfg", QSettings::IniFormat );

    // Archivo de entrada
    QString archivo = QCoreApplication::applicationDirPath().append( QDir::separator() ).append( parametros.value( "archivo_entrada" ).toString() );

    // Cargo los datos de los archivos que corresponda
    matriz entradas( parametros.value( "cantidad_entradas" ).toInt() );
    vector salidas( parametros.value( "cantidad_salidas" ).toInt() );

    qWarning() << "Archivo de lectura de datos originales: "<< archivo;
    if( ! leer_archivo_entrenamiento( archivo,
                                      &entradas,
                                      &salidas,
                                      parametros.value( "cantidad_entradas" ).toInt() )  ) {
        qDebug() << "No se pudo encontrar el archivo de entrenamiento! cancelando!";
        abort();
    }

    qDebug() << endl << "--------------- /Datos del entrenamiento/ -----------------" << endl;

    // Inicializo la red neuronal
    QVector<int> neuronas_por_capas = stringAQVector( parametros.value( "capas" ).toString() );
    RedNeuronal red( neuronas_por_capas.size(),
                     neuronas_por_capas,
                     parametros.value("cantidad_entradas").toInt(),
                     main.centralWidget() );

    red.setearTasaAprendizaje( parametros.value( "tasa_aprendizaje" ).toDouble() );
    qDebug() << "Tasa de aprendizaje: " << parametros.value( "tasa_aprendizaje" ).toDouble();

    red.setearCodificacion( stringAQVector( parametros.value( "codificacion_salida" ).toString() ) );
    qDebug() << "Codificacion salida: " << red.mostrarCodificacionSalida();

    // Inicializo el enjambre de particulas

    double tolerancia_error = parametros.value( "tolerancia_error" ).toDouble();
    qDebug() << "Error de corte: " << ( tolerancia_error ) << "%";

    int cant_particulas = parametros.value( "cant_part" ).toInt();
    qDebug() << "Cantidad de Particulas: " << ( cant_particulas );

    double xmax = parametros.value( "xmax" ).toDouble();
    qDebug() << "Limite Superior: " << ( xmax ) << "%";

    double xmin = parametros.value( "xmin" ).toDouble();
    qDebug() << "Limite Inferior: " << ( xmin ) << "%";

    enjambre psonn(cant_particulas,xmin,xmax,tolerancia_error);

    qDebug() << endl << "---------------- /Comienza el entrenamiento/ ----------------";

    if( stringAQVector( parametros.value( "codificacion_salida" ).toString() ).size() <= 2 ) {
        GraficadorMdi *graf2 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf2 );
        graf2->showMaximized();
        graf2->setearTitulo( "Datos originales" );
        graf2->setearEjesEnGrafico();
        graf2->setearTituloEjeX( " X " );
        graf2->setearTituloEjeY( " y " );
        graf2->agregarPuntosClasificados( entradas, salidas, 0.5 );
        mdiArea->tileSubWindows();
    } else {
        matriz entradas1, entradas2;
        vector salidas1, salidas2;
        for( int i=0; i < entradas.size(); i++ ) {
            vector temp;
            temp.append( entradas.at(i).at(0) );
            temp.append( entradas.at(i).at(1) );
            entradas1.append( temp );
            vector temp2;
            temp2.append( entradas.at(i).at(2) );
            temp2.append( entradas.at(i).at(3) );
            entradas2.append( temp2 );
            salidas1.append( salidas.at( i ) );
            salidas2.append( salidas.at( i ) );
        }

        GraficadorMdi *graf2 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf2 );
        graf2->showMaximized();
        graf2->setearTitulo( "Datos originales" );
        //graf2->setearEjesEnGrafico();
        graf2->setearTituloEjeX( "Longitud" );
        graf2->setearTituloEjeY( "Ancho" );
        graf2->agregarPuntosClasificados( entradas1, salidas1, stringAQVector( parametros.value( "codificacion_salida" ).toString() ) );

        GraficadorMdi *graf3 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf3 );
        graf3->showMaximized();
        graf3->setearTitulo( "Datos originales" );
        //graf3->setearEjesEnGrafico();
        graf3->setearTituloEjeX( "Petalos" );
        graf3->setearTituloEjeY( "Sepalos" );
        graf3->agregarPuntosClasificados( entradas2, salidas2, stringAQVector( parametros.value( "codificacion_salida" ).toString() ) );
        mdiArea->tileSubWindows();

    }

    // Mido el tiempo
    QElapsedTimer medidor_tiempo;
    medidor_tiempo.start();

    psonn.optimizar();

    qint64 milisegundos = medidor_tiempo.elapsed();

    qDebug() << "Tiempo medido: " << milisegundos << " ms";

    //ACA TENDRIA QUE COPIARLE LOS PESOS OPTIMIZADOS A LA RED NEURONAL

    QVector<int> nueva_salida;
    for( int i=0; i<entradas.size(); i++ ) {
        nueva_salida.append( red.mapeadorSalidas( red.forwardPass( entradas.at(i) ) ) );
    }

    if( stringAQVector( parametros.value( "codificacion_salida" ).toString() ).size() <= 2 ) {
        GraficadorMdi *graf4 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf4 );
        graf4->showMaximized();
        graf4->setearTitulo( "Datos evaluados con red neuronal" );
        graf4->setearEjesEnGrafico();
        graf4->setearTituloEjeX( " X " );
        graf4->setearTituloEjeY( " y " );
        graf4->agregarPuntosClasificados( entradas, nueva_salida, stringAQVector( parametros.value( "codificacion_salida" ).toString() ) );
        //graf4->agregarPuntosClasificados( entradas, nueva_salida );
    } else {

        matriz entradas1, entradas2;
        vector salidas1, salidas2;
        for( int i=0; i < entradas.size(); i++ ) {
            vector temp;
            temp.append( entradas.at(i).at(0) );
            temp.append( entradas.at(i).at(1) );
            entradas1.append( temp );
            vector temp2;
            temp2.append( entradas.at(i).at(2) );
            temp2.append( entradas.at(i).at(3) );
            entradas2.append( temp2 );
            salidas1.append( nueva_salida.at( i ) );
            salidas2.append( nueva_salida.at( i ) );
        }

        GraficadorMdi *graf4 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf4 );
        graf4->showMaximized();
        graf4->setearTitulo( "Datos evaluados con red neuronal" );
        graf4->setearTituloEjeX( "Largo" );
        graf4->setearTituloEjeY( "Ancho" );
        graf4->agregarPuntosClasificados( entradas1, salidas1, stringAQVector( parametros.value( "codificacion_salida" ).toString() ) );

        GraficadorMdi *graf5 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf5 );
        graf5->showMaximized();
        graf5->setearTitulo( "Datos evaluados con red neuronal" );
        graf5->setearTituloEjeX( "Petalos" );
        graf5->setearTituloEjeY( "Sepalos" );
        graf5->agregarPuntosClasificados( entradas2, salidas2, stringAQVector( parametros.value( "codificacion_salida" ).toString() ) );
    }
    mdiArea->tileSubWindows();

    arch.close();

    return a.exec();

}