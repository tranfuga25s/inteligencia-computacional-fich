#include <QCoreApplication>
#include <QDebug>
#include <QTime>
#include <QDir>
#include <QVector>
#include <QSettings>

typedef QVector<double> vector;
typedef QVector< QVector<double> > matriz;

#include "funciones_aux.h"
#include "neurona.h"

/*!
 * \brief main
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char *argv[])
{
    QCoreApplication a( argc, argv );

    //Inicializo con una semilla aleatoria para la generacion de Aleatorios
    qsrand(QTime::currentTime().msec());

    // Cargo los parametros del ejercicio
    QSettings parametros( "parametros.cfg", QSettings::IniFormat );

    //Archivo OR
    QString archivo = QCoreApplication::applicationDirPath().append( QDir::separator() ).append( parametros.value( "archivo_entrada" ).toString() );

    //Generamos el archivo de entrenamiento en base a la desviacion del 5%
    generarArchivoAleatoriosEntrenamiento( archivo,
                     parametros.value( "archivo_entrenamiento_randomizado" ).toString(),
                     parametros.value( "cantidad_datos_extras" ).toInt(),
                     parametros.value( "porcentaje_variacion" ).toDouble() );


    //Archivo OR randomizado
    QString archivo_aleatorios = QCoreApplication::applicationDirPath().append( QDir::separator() ).append( parametros.value( "archivo_entrenamiento_randomizado" ).toString() );


    // Randomizamos los datos en base a el contenido de "archivo" para la prueba
    generarArchivoAleatoriosPrueba( archivo,
                     parametros.value( "archivo_prueba_randomizado" ).toString(),
                     parametros.value( "cantidad_datos_extras" ).toInt(),
                     parametros.value( "porcentaje_variacion" ).toDouble() );
    

    // Cargo los datos de los archivos que corresponda
    matriz entradas( parametros.value( "cantidad_entradas" ).toInt() );
    vector salidas( parametros.value( "cantidad_salidas" ).toInt() );


    qWarning() << archivo;
    if( ! leer_archivo_entrenamiento( archivo_aleatorios,
                                      &entradas,
                                      &salidas,
                                      parametros.value( "cantidad_entradas" ).toInt(),
                                      parametros.value( "cantidad_salidas" ).toInt() ) ) {
        qDebug() << "No se pudo encontrar el archivo de entrenamiento! cancelando!";
        abort();
    }

    /*qDebug() << "Salidas";
    mostrarVector( salidas );
    qDebug() << "Entradas";
    mostrarMatriz( entradas );*/


    Neurona n(0,parametros.value( "cantidad_entradas" ).toInt() );
    n.inicializarPesos();
    //mostrarVector( n.devuelvePesos() );
    n.setearTasaAprendizaje( parametros.value( "tasa_aprendizaje" ).toDouble() );
    qDebug() << "Tasa de aprendizaje: " << n.tasaAprendizaje();

    int max_etapas = parametros.value( "etapas_maximas" ).toInt();
    qDebug() << "Epocas: " << max_etapas;
    double tolerancia_error = parametros.value( "tolerancia_error" ).toDouble();
    qDebug() << "Error de corte: " << ( tolerancia_error * 100.0 ) << "%";
    int epoca = 0; /* Contador de etapa */

    double porcentaje_error = 100.0; /*Mucho sino sale*/
    double porcentaje_acierto = 0.0;
    double error_parcial_maximo = tolerancia_error+0.001;

    while ( epoca <= max_etapas
            && (porcentaje_error > tolerancia_error ))
    {
        // randomizo el la lectura del vector de entradas
        QVector<int> mapa = randomizarEntradas( entradas.size() );
        //qDebug() << "orden de datos: " << mapa;

        // Inicio la etapa de entrenamiento
        qDebug() << "--------------------------------";
        qDebug() << ">> Entrenando - Epoca: " << epoca;
        for(int i =0; i<entradas.size(); i++ )
        {
            double error_parcial = abs( n.entrenamiento( entradas.at( mapa.at(i) ), salidas.at( mapa.at( i ) ) ) );
            if( error_parcial > error_parcial_maximo )
            {
                error_parcial_maximo = error_parcial;
                //qDebug() << "ep: " << error_parcial_maximo;
            }
            //qDebug()<<n.devuelvePesos();
        }



        // Verifico el error
        //qDebug() << "--------------------------------";
        qDebug() << ">> Verificando tasa de error";
        int errores = 0;
        int correcto = 0;
        for( int i = 0; i < entradas.size(); i++ ) {
            if( n.evaluar( entradas.at( i ) ) != salidas.at( i ) ) {
                errores++;
            } else {
                correcto++;
            }
        }
        porcentaje_error = ( (double) errores * 100.0 ) / (double) entradas.size();
        porcentaje_acierto = ( (double) correcto * 100.0 ) / (double) entradas.size();
        qDebug() << "Cantidad de errores: " << errores << ", acertados: " << correcto;
        qDebug() << "Porcentaje de acierto: " << porcentaje_acierto << "%";
        qDebug() << "Porcentaje de error: " << porcentaje_error << "%";

        // Aumento el contador de epocas
        epoca++;

        error_parcial_maximo=tolerancia_error+0.001;

    }

    qDebug() << "Probando con archivo de datos aleatorios";
    leer_archivo_entrenamiento( parametros.value( "archivo_prueba_randomizado" ).toString(),
                                &entradas,
                                &salidas,
                                2,
                                1 );

    qDebug() << "Escribiendo resultados";
    salidas.clear();
    for( int i=0; i<entradas.size(); i++ ) {
        salidas.append( n.evaluar( entradas.at( i ) ) );
    }
    escribe_archivo_salida( parametros.value( "archivo_salida" ).toString(),
                            &entradas,
                            &salidas );

    return 0;

}
