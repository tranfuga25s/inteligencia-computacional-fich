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
                     parametros.value("cantidad_entradas").toInt());

    red.setearTasaAprendizaje( parametros.value( "tasa_aprendizaje" ).toDouble() );
    qDebug() << "Tasa de aprendizaje: " << parametros.value( "tasa_aprendizaje" ).toDouble();

    red.setearCodificacion( stringAQVector( parametros.value( "codificacion_salida" ).toString() ) );
    qDebug() << "Codificacion salida: " << red.mostrarCodificacionSalida();

    //Inicializo la red
    red.inicializarPesos();

    qDebug() << "CANTIDAD PESOS RED: " << red.cantidadPesos();

    //Grafico los datos originales
    GraficadorMdi *graf2 = new GraficadorMdi( mdiArea );
    mdiArea->addSubWindow( graf2 );
    graf2->showMaximized();
    graf2->setearTitulo( "Datos originales" );
    graf2->setearEjesEnGrafico();
    graf2->setearTituloEjeX( " X " );
    graf2->setearTituloEjeY( " y " );
    graf2->agregarPuntosClasificados( entradas, salidas, red.mostrarCodificacionSalida() );
    mdiArea->tileSubWindows();


    // Inicializo el enjambre de particulas

    double tolerancia_error = parametros.value( "tolerancia_error" ).toDouble();
    if (tolerancia_error > 100) {
        qDebug() << "Cantidad de errores de evaluacion permitidos: " << ( tolerancia_error );
    }
    else
    {
        qDebug() << "Error de corte: " << ( tolerancia_error ) << "%";
    }



    int iteraciones = parametros.value( "iter" ).toDouble();
    qDebug() << "Cantidad de iteraciones Maximas: " << ( iteraciones );

    int cant_particulas = parametros.value( "cant_part" ).toInt();
    qDebug() << "Cantidad de Particulas: " << ( cant_particulas );

    double xmax = parametros.value( "xmax" ).toDouble();
    qDebug() << "Limite Superior: " << ( xmax );

    double xmin = parametros.value( "xmin" ).toDouble();
    qDebug() << "Limite Inferior: " << ( xmin );

    enjambre psonn(cant_particulas,
                   xmin,
                   xmax,
                   tolerancia_error,
                   iteraciones,
                   &red,
                   entradas,
                   salidas);



    qDebug() << endl << "---------------- /Comienza el entrenamiento/ ----------------";

    // Mido el tiempo
    QElapsedTimer medidor_tiempo;
    medidor_tiempo.start();

    bool motivo_salida = psonn.optimizar();

    qint64 milisegundos = medidor_tiempo.elapsed();

    qDebug() << "Tiempo medido: " << milisegundos << " ms";

    //Calculo el error promedio y la desviacion estandar para todo
    double error = psonn.cantidadErroresEnMinimo();
    qDebug() <<"Cantidad de Errores: " << error ;

    if (motivo_salida == true) {
        qDebug() << "Motivo Salida: TOLERANCIA";
    }
    else
    {
        qDebug() << "Motivo Salida: CANTIDAD DE ITERACIONES";
    }


    qDebug() << endl << "---------------- /Prueba de a Red/ ----------------";

    QVector<int> nueva_salida;
    for( int i=0; i<entradas.size(); i++ ) {
        nueva_salida.append( red.mapeadorSalidas( red.forwardPass( entradas.at(i) ) ) );
    }

    GraficadorMdi *graf4 = new GraficadorMdi( mdiArea );
    mdiArea->addSubWindow( graf4 );
    graf4->showMaximized();
    graf4->setearTitulo( "Datos evaluados con red neuronal" );
    graf4->setearEjesEnGrafico();
    graf4->setearTituloEjeX( " X " );
    graf4->setearTituloEjeY( " y " );
    graf4->agregarPuntosClasificados( entradas, nueva_salida, stringAQVector( parametros.value( "codificacion_salida" ).toString() ) );
    //graf4->agregarPuntosClasificados( entradas, nueva_salida );

    mdiArea->tileSubWindows();

    arch.close();

    return a.exec();

}
