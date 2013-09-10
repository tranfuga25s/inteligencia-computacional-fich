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
    qsrand( QTime::currentTime().msec() );

    // Cargo los parametros del ejercicio
    QSettings parametros( "parametros.cfg", QSettings::IniFormat );

    // Archivo de entrada
    QString archivo = QCoreApplication::applicationDirPath().append( QDir::separator() ).append( parametros.value( "archivo_entrada" ).toString() );

    // Cargo los datos de los archivos que corresponda
    matriz entradas( parametros.value( "cantidad_entradas" ).toInt() );
    vector salidas( parametros.value( "cantidad_salidas" ).toInt() );

    qDebug() << endl << "--------------- /Datos del entrenamiento/ -----------------" << endl;
    qWarning() << "Archivo de lectura de datos originales: "<< archivo;
    if( ! leer_archivo_entrenamiento( archivo,
                                      &entradas,
                                      &salidas,
                                      parametros.value( "cantidad_entradas" ).toInt() )  ) {
        qDebug() << "No se pudo encontrar el archivo de entrenamiento! cancelando!";
        abort();
    }


    // particionamos los datos
    Particionador particiones;
    particiones.setearCantidadDatos( entradas.size() );
    particiones.setearCantidadDeParticiones( parametros.value( "cantidad_particiones" ).toInt() );
    particiones.setearPorcentajeEntrenamiento( parametros.value( "porcentaje_entrenamiento" ).toDouble() );
    particiones.setearPorcentajeValidacion( parametros.value("porcentaje_validacion").toDouble() );
    particiones.setearK(parametros.value("k").toInt());
    particiones.particionarDatos();

    // Inicializo la red neuronal
    QVector<int> neuronas_por_capas = stringAQVector( parametros.value( "capas" ).toString() );
    RedNeuronal red( neuronas_por_capas.size(),
                     neuronas_por_capas,
                     parametros.value("cantidad_entradas").toInt(),
                     main.centralWidget() );

    red.setearTasaAprendizaje( parametros.value( "tasa_aprendizaje" ).toDouble() );
    qDebug() << "Tasa de aprendizaje: " << parametros.value( "tasa_aprendizaje" ).toDouble();

    red.setearMomento( parametros.value( "momento" ).toDouble() );
    qDebug() << "Momento: " << red.getMomento();

    red.setearCodificacion( stringAQVector( parametros.value( "codificacion_salida" ).toString() ) );
    qDebug() << "Codificacion salida: " << red.mostrarCodificacionSalida();

    int max_epocas = parametros.value( "epocas_maximas", 20 ).toInt();
    qDebug() << "Epocas: " << max_epocas;

    double tolerancia_error = parametros.value( "tolerancia_error" ).toDouble();
    qDebug() << "Error de corte: " << ( tolerancia_error ) << "%";

    qDebug() << endl << "---------------- /Comienza el entrenamiento/ ----------------";

    int epoca = 0; /* Contador de epocas */
    double porcentaje_error = 100.0; /*Mucho sino sale*/
    int cantidad_particiones_exitosas = 0;

    GraficadorMdi *graf1 = new GraficadorMdi( mdiArea );
    graf1->setearTitulo( QString::fromUtf8( "Porcentaje de error según particion ( entrenamiento )" ) );
    graf1->setearTituloEjeX( QString::fromUtf8( "Epoca" ) );
    graf1->setearTituloEjeY( QString::fromUtf8( "Porcentaje error" ) );
    mdiArea->addSubWindow( graf1 );
    mdiArea->tileSubWindows();

    GraficadorMdi *graf2 = new GraficadorMdi( mdiArea );
    mdiArea->addSubWindow( graf2 );
    graf2->showMaximized();
    graf2->setearTitulo( "Datos originales" );
    graf2->setearEjesEnGrafico();
    graf2->setearTituloEjeX( " X " );
    graf2->setearTituloEjeY( " y " );
    graf2->agregarPuntosClasificados( entradas, salidas, 0.5 );
    mdiArea->tileSubWindows();

    QDockWidget *dockBarra1 = new QDockWidget( "Progreso de Particiones" );
    main.addDockWidget( Qt::BottomDockWidgetArea, dockBarra1 );
    QProgressBar *PBParticiones = new QProgressBar( dockBarra1 );
    dockBarra1->setWidget( PBParticiones );

    QDockWidget *dockBarra2 = new QDockWidget( "Progreso de Epocas" );
    main.addDockWidget( Qt::BottomDockWidgetArea, dockBarra2 );
    QProgressBar *PBEpocas = new QProgressBar( dockBarra2 );
    dockBarra2->setWidget( PBEpocas );

    QVector<double> errores_particiones;

    PBParticiones->setRange( 0, particiones.cantidadDeParticiones() );
    PBParticiones->setValue( 0 );
    PBParticiones->setFormat( "Particion %v de %m - %p%" );

    PBEpocas->setRange( 0, max_epocas );
    PBEpocas->setFormat( "Epoca %v de %m - %p%" );

    for( int p=0; p<particiones.cantidadDeParticiones(); p++ ) {

        Particionador::particion part_local = particiones.getParticion( p );

        qDebug() << endl << "Utilizando Particion: " << p ;

        //pongo nuevamente en los valores iniciales las variables de corte para que entre en todas las particiones
        epoca = 0;
        porcentaje_error = 100.0;
        red.inicializarPesos();

        QVector<double> errores_epocas;

        //std::cout << "Epoca: " << std::endl;
        PBEpocas->setValue( 0 );
        while ( epoca < max_epocas
                && porcentaje_error > tolerancia_error )
        {
            // Inicio la etapa de entrenamiento
            //qDebug() << "--------------------------------";
            //std::cout << epoca << " \r";
            for(int i = 0; i<part_local.entrenamiento.size(); i++ )
            {
                red.backwardPass( entradas.at( part_local.entrenamiento.at(i) ), salidas.at( part_local.entrenamiento.at( i ) ) );
            }

            ///@TODO Velocidad de convergencia para poder comparar con y sin momento

            // Verifico el error
            //qDebug() << "--------------------------------";
            //qDebug() << ">> Verificando tasa de error";
            int errores = 0;
            int correcto = 0;

            //TIENE QUE ESTAR ACA EL PROBLEMA RELACIONADO CON EL FORWARDPASS SALEN DE MAYOR A MENOR LAS SALIDAS
            for( int i = 0; i < part_local.validacion.size(); i++ ) {
                //qDebug() << red.forwardPass( entradas.at( part_local.validacion.at( i ) ) );
                if( red.mapeadorSalidas( red.forwardPass( entradas.at( part_local.validacion.at( i ) ) ) ) != salidas.at( part_local.validacion.at( i ) ) ) {
                    errores++;
                } else {
                    correcto++;
                }
            }
            porcentaje_error = ( (double) errores * 100 ) / (double) entradas.size();
            errores_epocas.push_back( porcentaje_error );



            // Aumento el contador de epocas
            epoca++;
            PBEpocas->setValue( epoca );

            QApplication::processEvents();

        }

        graf1->agregarCurva( errores_epocas, QString( "Particion %1" ).arg( p ) );

        //std::cout << "\r";

        qDebug() << " Epoca de finalizacion: " << epoca+1 << " - Error de salida de entrenamiento: " << porcentaje_error << "%";

        // Genero las estadisticas con los datos de prueba
        porcentaje_error = 0.0;
        int errores = 0;
        int correcto = 0;
        for( int i = 0; i < part_local.prueba.size(); i++ ) {
            if( red.mapeadorSalidas( red.forwardPass( entradas.at( part_local.prueba.at( i ) ) ) ) != salidas.at( part_local.prueba.at( i ) ) ) {
                errores++;
            } else {
                correcto++;
            }
        }
        porcentaje_error = ( (double) errores * 100 ) / (double) entradas.size();
        errores_particiones.push_back( porcentaje_error );

        //Aumento el contador de las no exitosas
        if (epoca < max_epocas)
        {
            cantidad_particiones_exitosas++;
        }

        //qDebug() << errores_epocas;
        qDebug() <<"Terminada particion " << p << "- Error de prueba: " << errores_particiones.at( p ) << "%";

        //Calculo el error promedio y la desviacion estandar para la particion
        double error_promedio = 0.0;
        double desviacion_estandar = 0.0;
        double error_aux = 0.0;


        for (int i = 0 ; i < errores_epocas.size() ; i++ ) { error_promedio += errores_epocas.at(i);}
        error_promedio /= errores_epocas.size();

        qDebug() <<"Error Promedio: " << error_promedio << "%";

        for (int i = 0 ; i < errores_epocas.size() ; i++ ) { error_aux += exp(errores_epocas.at(i) - error_promedio);}
        desviacion_estandar = sqrt( (1.0 / (errores_epocas.size() - 1.0) ) * error_aux );

        qDebug() <<"Desviacion Estandar: " << desviacion_estandar << "%";

        errores_epocas.clear();
        PBParticiones->setValue( PBParticiones->value() + 1 );

        QVector<int> nueva_salida;
        matriz nueva_entrada;
        for( int i=0; i<part_local.prueba.size(); i++ ) {
            nueva_salida.append( red.mapeadorSalidas( red.forwardPass( entradas.at( part_local.prueba.at( i ) ) ) ) );
            nueva_entrada.append( entradas.at( part_local.prueba.at( i ) ) );
        }

        GraficadorMdi *graf = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf );
        graf->show();
        graf->setearTitulo( QString( "Datos de prueba evaluados con red neuronal - Particion %1" ).arg( p+1 ) );
        graf->setearEjesEnGrafico();
        graf->setearTituloEjeX( " X " );
        graf->setearTituloEjeY( " y " );
        graf->agregarPuntosClasificados( nueva_entrada, nueva_salida, stringAQVector( parametros.value( "codificacion_salida" ).toString() ) );
        mdiArea->tileSubWindows();

        QApplication::processEvents();
    }
    //std::cout << std::endl;

    // Calculo el promedio de todos los errores
    double sumatoria = 0.0;
    for( int i=0; i<errores_particiones.size(); i++ ) {
        sumatoria+=errores_particiones.at(i);
    }
    qDebug() << endl << "--------------- /Resumen/ -----------------";
    qDebug() << endl << "Error total: " << sumatoria/errores_particiones.size() << "%";
    qDebug() << endl << "Cantidad de Particiones que convergen: " << cantidad_particiones_exitosas ;
    qDebug() << endl << "Cantidad de Particiones sin converger: " << (particiones.cantidadDeParticiones() - cantidad_particiones_exitosas) ;

    //Calculo el error promedio y la desviacion estandar para todo
    double error_promedio = sumatoria/errores_particiones.size();
    double desviacion_estandar = 0.0;
    double error_aux = 0.0;

    for (int i = 0 ; i < errores_particiones.size() ; i++ ) { error_aux += exp(errores_particiones.at(i) - error_promedio);}
    desviacion_estandar = sqrt( (1.0 / (errores_particiones.size() - 1.0) ) * error_aux );

    qDebug() <<"Desviacion Estandar: " << desviacion_estandar << "%";


    GraficadorMdi *graf3 = new GraficadorMdi( mdiArea );
    mdiArea->addSubWindow( graf3 );
    graf3->showMaximized();
    graf3->setearTitulo( "Errores por particion( datos de prueba )" );
    graf3->setearTituloEjeX( "Particion" );
    graf3->setearTituloEjeY( "Error" );
    graf3->agregarCurva( errores_particiones, "Errores" );
    mdiArea->tileSubWindows();

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
    mdiArea->tileSubWindows();

    return a.exec();

}
