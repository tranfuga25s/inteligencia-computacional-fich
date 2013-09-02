#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QTime>
#include <QDir>
#include <QVector>
#include <QSettings>

#include "iostream"
#include "graficador.h"


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

    //Inicializo con una semilla aleatoria para la generacion de Aleatorios
    qsrand(QTime::currentTime().msec());

    // Cargo los parametros del ejercicio
    QSettings parametros( "parametros.cfg", QSettings::IniFormat );

    // Archivo de entrada
    QString archivo = QCoreApplication::applicationDirPath().append( QDir::separator() ).append( parametros.value( "archivo_entrada" ).toString() );

    //Generamos el archivo de entrenamiento en base a la desviacion indicada en la configuracion y la cantidad de datos
    generarArchivoAleatoriosEntrenamiento( archivo,
                     parametros.value( "archivo_entrenamiento_randomizado" ).toString(),
                     parametros.value( "cantidad_datos" ).toInt(),
                     parametros.value( "porcentaje_variacion" ).toDouble(),
                     parametros.value( "cantidad_entradas" ).toInt());


    //Archivo randomizado
    QString archivo_aleatorios = QCoreApplication::applicationDirPath().append( QDir::separator() ).append( parametros.value( "archivo_entrenamiento_randomizado" ).toString() );


    // Cargo los datos de los archivos que corresponda
    matriz entradas( parametros.value( "cantidad_entradas" ).toInt() );
    vector salidas( parametros.value( "cantidad_salidas" ).toInt() );

    qDebug() << endl << "--------------- /Datos del entrenamiento/ -----------------" << endl;
    qWarning() << "Archivo de lectura de datos originales: "<< archivo;
    qWarning() << "Archivo de entrenamiento: "<< archivo_aleatorios;
    if( ! leer_archivo_entrenamiento( archivo_aleatorios,
                                      &entradas,
                                      &salidas,
                                      parametros.value( "cantidad_entradas" ).toInt(),
                                      parametros.value( "cantidad_salidas" ).toInt() )  ) {
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

    Neurona n( 0, parametros.value( "cantidad_entradas" ).toInt() );
    n.inicializarPesos();
    //mostrarVector( n.devuelvePesos() );
    n.setearTasaAprendizaje( parametros.value( "tasa_aprendizaje" ).toDouble() );
    qDebug() << "Tasa de aprendizaje: " << n.tasaAprendizaje();

    int max_epocas = parametros.value( "epocas_maximas", 20 ).toInt();
    qDebug() << "Epocas: " << max_epocas;

    double tolerancia_error = parametros.value( "tolerancia_error" ).toDouble();
    qDebug() << "Error de corte: " << ( tolerancia_error ) << "%";

    qDebug() << endl << "---------------- /Comienza el entrenamiento/ ----------------";

    int epoca = 0; /* Contador de epocas */
    double porcentaje_error = 100.0; /*Mucho sino sale*/
    int cantidad_particiones_exitosas = 0;

    Graficador *graf1 = new Graficador();
    main.setCentralWidget( graf1 );
    graf1->setearTitulo( QString::fromUtf8( "Porcentaje de error según particion" ) );
    graf1->setearTituloEjeX( QString::fromUtf8( "Partición" ) );
    graf1->setearTituloEjeY( QString::fromUtf8( "Porcentaje error" ) );

    QVector<double> errores_particiones;

    for( int p=0; p<particiones.cantidadDeParticiones(); p++ ) {

        Particionador::particion part_local = particiones.getParticion( p );

        errores_particiones.insert( p, 0.0 );

        qDebug() << endl << "Utilizando Particion: " << p ;

        //pongo nuevamente en los valores iniciales las variables de corte para que entre en todas las particiones
        epoca = 0;
        porcentaje_error = 100.0;
        n.inicializarPesos();

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
                n.entrenamiento( entradas.at( part_local.entrenamiento.at(i) ), salidas.at( part_local.entrenamiento.at( i ) ) );
            }

            // Verifico el error
            //qDebug() << "--------------------------------";
            //qDebug() << ">> Verificando tasa de error";
            int errores = 0;
            int correcto = 0;
            for( int i = 0; i < part_local.validacion.size(); i++ ) {
                if( n.evaluar( entradas.at( part_local.validacion.at( i ) ) ) != salidas.at( part_local.validacion.at( i ) ) ) {
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

        // Genero las estadisticas con los datos de prueba
        int errores = 0;
        int correcto = 0;
        for( int i = 0; i < part_local.prueba.size(); i++ ) {
            if( n.evaluar( entradas.at( part_local.prueba.at( i ) ) ) != salidas.at( part_local.prueba.at( i ) ) ) {
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
        qDebug() <<"Terminada particion " << p << "- Error: " << errores_particiones.at( p ) << "% - Epoca de finalizacion: " << epoca+1;
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

    Graficador *graf2 = new Graficador();
    graf2->show();
    graf2->setearTitulo( "Errores por particion" );
    graf2->setearTituloEjeX( "Particion" );
    graf2->setearTituloEjeY( "Error" );
    graf2->agregarCurva( errores_particiones, "Errores" );

    return a.exec();

}
