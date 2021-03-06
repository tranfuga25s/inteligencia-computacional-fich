#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QTime>
#include <QDir>
#include <QVector>
#include <QSettings>

typedef QVector<double> vector;
typedef QVector< QVector<double> > matriz;

#include "funciones_aux.h"
#include "neurona.h"
#include "graficador.h"

/*!
 * \brief main
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

    //Archivo OR
    QString archivo = QCoreApplication::applicationDirPath().append( QDir::separator() ).append( parametros.value( "archivo_entrada" ).toString() );

    //Generamos el archivo de entrenamiento en base a la desviacion del 5%
    generarArchivoAleatoriosEntrenamientoRadial( archivo,
                     parametros.value( "archivo_entrenamiento_randomizado" ).toString(),
                     parametros.value( "cantidad_datos_extras" ).toInt(),
                     parametros.value( "porcentaje_variacion" ).toDouble(),
                     parametros.value( "cantidad_entradas" ).toInt() );


    //Archivo OR randomizado
    QString archivo_aleatorios = QCoreApplication::applicationDirPath().append( QDir::separator() ).append( parametros.value( "archivo_entrenamiento_randomizado" ).toString() );


    // Randomizamos los datos en base a el contenido de "archivo" para la prueba
    generarArchivoAleatoriosPruebaRadial( archivo,
                     parametros.value( "archivo_prueba_randomizado" ).toString(),
                     parametros.value( "cantidad_datos_extras" ).toInt(),
                     parametros.value( "porcentaje_variacion" ).toDouble(),
                     parametros.value( "cantidad_entradas" ).toInt() );
    

    // Cargo los datos de los archivos que corresponda
    matriz entradas( parametros.value( "cantidad_entradas" ).toInt() );
    vector salidas( parametros.value( "cantidad_salidas" ).toInt() );

    qDebug() << "--------------- /Datos del entrenamiento/ -----------------" << endl;
    qWarning() << "Archivo de datos: " << archivo;
    qWarning() << "Archivo de aleatorios: " << archivo_aleatorios;
    if( ! leer_archivo_entrenamiento( archivo_aleatorios,
                                      &entradas,
                                      &salidas,
                                      parametros.value( "cantidad_entradas" ).toInt() ) ) {
        qDebug() << "No se pudo encontrar el archivo de entrenamiento! cancelando!";
        abort();
    }

    /*qDebug() << "Salidas";
    mostrarVector( salidas );
    qDebug() << "Entradas";
    mostrarMatriz( entradas );*/

    Graficador *graf = new Graficador();

    Neurona n(0,parametros.value( "cantidad_entradas" ).toInt() );
    n.inicializarPesos();
    //mostrarVector( n.devuelvePesos() );
    n.setearTasaAprendizaje( parametros.value( "tasa_aprendizaje" ).toDouble() );
    qDebug() << "Tasa de aprendizaje: " << n.tasaAprendizaje();

    int max_etapas = parametros.value( "etapas_maximas" ).toInt();
    qDebug() << "Epocas: " << max_etapas;
    double tolerancia_error = parametros.value( "tolerancia_error" ).toDouble();
    qDebug() << "Error de corte: " << ( tolerancia_error ) << "%";

    qDebug() << endl <<"--------------- /Comienza el entrenamiento/ -----------------" << endl;

    int epoca = 0; /* Contador de etapa */
    double porcentaje_error = 100.0; /*Mucho sino sale*/
    QVector<double> erroresParciales;

    Graficador *graf3 = new Graficador();
    graf3->setearTitulo( " 1 - Recta durante el entrenamiento" );
    graf3->setearTituloEjeX( "X" );
    graf3->setearTituloEjeY( "Y" );
    graf3->setearEjesEnGrafico();
    graf3->agregarPuntosClasificados( entradas, salidas );
    main.setCentralWidget( graf3 );
    graf3->setearTamanoFijo();

    while ( epoca <= max_etapas
            && (porcentaje_error > tolerancia_error ))
    {
        // randomizo el la lectura del vector de entradas
        QVector<int> mapa = randomizarEntradas( entradas.size() );

        // Inicio la etapa de entrenamiento
        qDebug() << "--------------------------------";
        qDebug() << ">> Entrenando - Epoca: " << epoca;
        for(int i =0; i<entradas.size(); i++ )
        {
            n.entrenamiento( entradas.at( mapa.at(i) ), salidas.at( mapa.at( i ) ) );
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
        qDebug() << "Cantidad de errores: " << errores << ", acertados: " << correcto;
        qDebug() << "Porcentaje de error: " << porcentaje_error << "%";
        erroresParciales.append( porcentaje_error );

        // Aumento el contador de epocas
        epoca++;

        // Grafico la recta
        graf3->dibujarRecta( 0, n.devuelvePesos() , QString::fromUtf8( "Recta de División" ) );
        QApplication::processEvents();

    }

    graf->setearTitulo( QString::fromUtf8( " 2 - Evolución del error de entrenamiento" ) );
    graf->agregarCurva( erroresParciales, "Errores parciales" );
    graf->setearTituloEjeX( "Epocas" );
    graf->setearTituloEjeY( "Porcentaje" );
    graf->showMaximized();

    qDebug() <<"-----------------------------------------";
    qDebug() << endl <<"Probando con archivo de datos aleatorios";
    leer_archivo_entrenamiento( parametros.value( "archivo_prueba_randomizado" ).toString(),
                                &entradas,
                                &salidas,
                                2 );

    qDebug() << "Escribiendo resultados";
    salidas.clear();
    for( int i=0; i<entradas.size(); i++ ) {
        double salida = n.evaluar( entradas.at( i ) );
        salidas.append( salida );
    }

    Graficador *graf2 = new Graficador();
    graf2->setearTitulo( " 3 - Salidas de particion de prueba" );
    graf2->setearEjesEnGrafico();
    graf2->agregarPuntosClasificados( entradas, salidas );
    graf2->showMaximized();

    escribe_archivo_salida( parametros.value( "archivo_salida" ).toString(),
                            &entradas,
                            &salidas );

    return a.exec();

}
