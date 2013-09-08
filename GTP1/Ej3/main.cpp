#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QTime>
#include <QDir>
#include <QVector>
#include <QSettings>
#include <QMdiArea>

#include "iostream"
#include "graficadormdi.h"
#include "redneuronal.h"
#include "capaneuronal.h"


typedef QVector<double> vector;
typedef QVector< QVector<double> > matriz;

#include "funciones_aux.h"
#include "neurona.h"
#include "particionador.h"

/*!
 * \brief main
 * Ejercicio 2 Guia de Trabajos Practicos 1
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
    qsrand(QTime::currentTime().msec());

    // Cargo los parametros del ejercicio
    QSettings parametros( "parametros.cfg", QSettings::IniFormat );

    // Archivo de entrada
    QString archivo = QCoreApplication::applicationDirPath().append( QDir::separator() ).append( parametros.value( "archivo_entrada" ).toString() );

    // Cargo los datos de los archivos que corresponda
    matriz entradas( parametros.value( "cantidad_entradas" ).toInt() );
    matriz salidas( parametros.value( "cantidad_salidas" ).toInt() );

    qDebug() << endl << "--------------- /Datos del entrenamiento/ -----------------" << endl;
    qWarning() << "Archivo de lectura de datos originales: "<< archivo;
    if( ! leer_archivo_entrenamiento( archivo,
                                      &entradas,
                                      &salidas,
                                      parametros.value( "cantidad_entradas" ).toInt(),
                                      parametros.value( "cantidad_salidas" ).toInt())  ) {
        qDebug() << "No se pudo encontrar el archivo de entrenamiento! cancelando!";
        abort();
    }

    // particionamos los datos
    Particionador particiones;
    particiones.setearCantidadDatos( entradas.size() );
    particiones.setearCantidadDeParticiones( parametros.value( "cantidad_particiones" ).toInt() );
    particiones.setearPorcentajeEntrenamiento( parametros.value( "porcentaje_entrenamiento" ).toDouble() );
    particiones.setearPorcentajeValidacion( parametros.value("porcentaje_validacion").toDouble() );
    particiones.particionarDatos();

    // Inicializo la red neuronal
    QString temporal = parametros.value( "capas" ).toString();
    QVector<QString> temp = temporal.split( " ", QString::KeepEmptyParts ).toVector();
    QVector<int> neuronas_por_capas;
    foreach( QString temp2, temp ) {
        neuronas_por_capas.append( temp2.toInt() );
    }
    qDebug() << neuronas_por_capas;
    RedNeuronal red( neuronas_por_capas.size(),
                     neuronas_por_capas,
                     parametros.value("cantidad_entradas").toInt(),
                     main.centralWidget() );

    red.setearTasaAprendizaje( parametros.value( "tasa_aprendizaje" ).toDouble() );
    qDebug() << "Tasa de aprendizaje: " << parametros.value( "tasa_aprendizaje" ).toDouble();

    int max_epocas = parametros.value( "epocas_maximas", 20 ).toInt();
    qDebug() << "Epocas: " << max_epocas;

    double tolerancia_error = parametros.value( "tolerancia_error" ).toDouble();
    qDebug() << "Error de corte: " << ( tolerancia_error ) << "%";

    qDebug() << endl << "---------------- /Comienza el entrenamiento/ ----------------";

    int epoca = 0; /* Contador de epocas */
    double porcentaje_error = 100.0; /*Mucho sino sale*/
    int cantidad_particiones_exitosas = 0;

    GraficadorMdi *graf1 = new GraficadorMdi( mdiArea );
    graf1->setearTitulo( QString::fromUtf8( "Porcentaje de error según particion" ) );
    graf1->setearTituloEjeX( QString::fromUtf8( "Partición" ) );
    graf1->setearTituloEjeY( QString::fromUtf8( "Porcentaje error" ) );
    mdiArea->addSubWindow( graf1 );
    mdiArea->tileSubWindows();

    GraficadorMdi *graf2 = new GraficadorMdi( mdiArea );
    mdiArea->addSubWindow( graf2 );
    graf2->showMaximized();
    graf2->setearTitulo( "Datos" );
    graf2->setearEjesEnGrafico();
    graf2->setearTituloEjeX( " X " );
    graf2->setearTituloEjeY( " y " );
    graf2->agregarPuntosClasificados( entradas, salidas, 0.5 );
    mdiArea->tileSubWindows();

    QVector<double> errores_particiones;

    for( int p=0; p<particiones.cantidadDeParticiones(); p++ ) {

        Particionador::particion part_local = particiones.getParticion( p );

        errores_particiones.insert( p, 0.0 );

        qDebug() << endl << "Utilizando Particion: " << p ;

        //pongo nuevamente en los valores iniciales las variables de corte para que entre en todas las particiones
        epoca = 0;
        porcentaje_error = 100.0;
        red.inicializarPesos();

        QVector<double> errores_epocas;

        std::cout << "Epoca: " << std::endl;

        while ( epoca < max_epocas
                && porcentaje_error > tolerancia_error )
        {
            // Inicio la etapa de entrenamiento
            //qDebug() << "--------------------------------";
            std::cout << epoca << " \r";
            for(int i =0; i<part_local.entrenamiento.size(); i++ )
            {
                red.entrenamiento( entradas.at( part_local.entrenamiento.at(i) ), salidas.at( part_local.entrenamiento.at( i ) ) );
            }

            // Verifico el error
            //qDebug() << "--------------------------------";
            //qDebug() << ">> Verificando tasa de error";
            int errores = 0;
            int correcto = 0;
            for( int i = 0; i < part_local.validacion.size(); i++ ) {
                if( red.forwardPass( entradas.at( part_local.validacion.at( i ) ) ) != salidas.at( part_local.validacion.at( i ) ) ) {
                    errores++;
                } else {
                    correcto++;
                }
            }
            porcentaje_error = ( (double) errores * 100 ) / (double) entradas.size();
            errores_epocas.push_back( porcentaje_error );

            // Aumento el contador de epocas
            epoca++;

            QApplication::processEvents();
        }

        graf1->agregarCurva( errores_epocas, QString( "Epoca %1" ).arg( p ) );

        std::cout << "\r";

        qDebug() << " Epoca de finalizacion: " << epoca+1 << " - Error de salida de entrenamiento: " << porcentaje_error << "%";

        // Genero las estadisticas con los datos de prueba
        int errores = 0;
        int correcto = 0;
        for( int i = 0; i < part_local.prueba.size(); i++ ) {
            if( red.forwardPass( entradas.at( part_local.prueba.at( i ) ) ) != salidas.at( part_local.prueba.at( i ) ) ) {
                errores++;
            } else {
                correcto++;
            }
        }
        porcentaje_error = ( (double) errores * 100 ) / (double) entradas.size();
        errores_particiones[p] = porcentaje_error;

        //Aumento el contador de las no exitosas
        if (epoca < max_epocas)
        {
            cantidad_particiones_exitosas++;
        }

        //qDebug() << errores_epocas;
        qDebug() <<"Terminada particion " << p << "- Error de prueba: " << errores_particiones.at( p ) << "%";
        errores_epocas.clear();
    }
    std::cout << std::endl;

    // Calculo el promedio de todos los errores
    double sumatoria = 0.0;
    for( int i=0; i<errores_particiones.size(); i++ ) {
        sumatoria+=errores_particiones.at(i);
    }
    qDebug() << endl << "--------------- /Resumen/ -----------------";
    qDebug() << endl << "Error total: " << sumatoria/errores_particiones.size() << "%";
    qDebug() << endl << "Cantidad de Particiones que convergen: " << cantidad_particiones_exitosas ;
    qDebug() << endl << "Cantidad de Particiones sin converger: " << (particiones.cantidadDeParticiones() - cantidad_particiones_exitosas) ;

    GraficadorMdi *graf3 = new GraficadorMdi( mdiArea );
    mdiArea->addSubWindow( graf3 );
    graf3->showMaximized();
    graf3->setearTitulo( "Errores por particion" );
    graf3->setearTituloEjeX( "Particion" );
    graf3->setearTituloEjeY( "Error" );
    graf3->agregarCurva( errores_particiones, "Errores" );

    mdiArea->tileSubWindows();


    return a.exec();

}
