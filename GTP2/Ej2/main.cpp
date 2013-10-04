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
    graf1->setearTitulo( QString::fromUtf8( "Porcentaje de error según particion ( entrenamiento )" ) );
    graf1->setearTituloEjeX( QString::fromUtf8( "Epoca" ) );
    graf1->setearTituloEjeY( QString::fromUtf8( "Porcentaje error" ) );
    mdiArea->addSubWindow( graf1 );
    mdiArea->tileSubWindows();

    // Archivo de entrada
    QString archivo = QCoreApplication::applicationDirPath().append( QDir::separator() ).append( parametros.value( "archivo_entrada" ).toString() );

    // Cargo los datos de los archivos que corresponda
    matriz entradas( parametros.value( "cantidad_entradas" ).toInt() );

    qDebug() << endl << "--------------- /Datos del entrenamiento/ -----------------" << endl;
    qWarning() << "Archivo de lectura de datos originales: "<< archivo;
    if( ! leer_archivo_entrenamiento( archivo,
                                      &entradas,
                                      parametros.value( "cantidad_entradas" ).toInt() )  ) {
        qDebug() << "No se pudo encontrar el archivo de entrenamiento! cancelando!";
        abort();
    }

    // Inicializo el SOM
    SOM som( parametros.value( "som_tam_x", 2 ).toInt(),
             parametros.value( "som_tam_y", 2 ).toInt(),
             parametros.value( "tamano_entradas" ).toInt() );

    qDebug() << endl << "---------------- /Comienza el entrenamiento/ ----------------";

    QVector<int> epocas = stringAQVector( parametros.value( "epocas" ).toString() );
    QVector<double> tasas = stringAQVectord( parametros.value( "tasa_aprendizaje" ).toString() );
    int tamano_vecindad_inicial = parametros.value( "radio_vecindad").toInt();


    // Etapa de Ordenamiento Global
    som.setearRadioVecindad( tamano_vecindad_inicial );
    som.setearTasaAprendizaje( tasas.at( 0 ) );

    for( int epoca=0; epoca<epocas.at(0); epoca++ ) {

        for( int p=0; p<entradas.size(); p++ ) {

            som.entrenar( entradas.at( p ) );

        }

    }

    // Etapa de transición
    QVector<int> tamano_vecindad = aproximacionLineal( epocas.at(0), epocas.at( 1 ), tamano_vecindad_inicial, 1 );
    QVector<double> tasa_aprendizajes = aproximacionLineald( epocas.at(0), epocas.at( 1 ), tasas.at( 0 ), tasas.at( 1 ) );

    for( int epoca=0; epoca<epocas.at(0); epoca++ ) {

        som.setearRadioVecindad( tamano_vecindad.at( epoca ) );
        som.setearTasaAprendizaje( tasa_aprendizajes.at( epoca ) );

        for( int p=0; p<entradas.size(); p++ ) {

            som.entrenar( entradas.at( p ) );

        }

    }

    // Etapa de ajuste fino
    som.setearRadioVecindad( 0 );
    tasa_aprendizajes = aproximacionLineald( epocas.at( 1 ), epocas.at(2) , tasas.at( 1 ), tasas.at( 2 ) );


    for( int epoca=0; epoca<epocas.at(0); epoca++ ) {

        som.setearTasaAprendizaje( tasa_aprendizajes.at( epoca ) );

        for( int p=0; p<entradas.size(); p++ ) {

            som.entrenar( entradas.at( p ) );

        }

    }

 /*


    int epoca = 0; // Contador de epocas
    double porcentaje_error = 100.0; // Mucho sino sale
    int cantidad_particiones_exitosas = 0;

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
        graf3->setearTituloEjeX( "Petalos" );
        graf3->setearTituloEjeY( "Sepalos" );
        graf3->agregarPuntosClasificados( entradas2, salidas2, stringAQVector( parametros.value( "codificacion_salida" ).toString() ) );
        mdiArea->tileSubWindows();

    }

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

    // Mido el tiempo
    QElapsedTimer medidor_tiempo;
    medidor_tiempo.start();

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
            for(int i = 0; i<part_local.entrenamiento.size(); i++ )
            {
                red.entrenarCapaNeuronalComun( entradas.at( part_local.entrenamiento.at(i) ), salidas.at( part_local.entrenamiento.at( i ) ) );
                //red.mostrarPesos( pesos );
            }

            // Verifico el error
            int errores = 0;
            int correcto = 0;

            for( int i = 0; i < part_local.validacion.size(); i++ ) {
                int pos = part_local.validacion.at( i );
                vector entrada_a_evaluar = entradas.at( pos );
                vector salida_red = red.probarPatron( entrada_a_evaluar ) ;
                double salida_mapeada = red.mapeadorSalidas( salida_red );
                double salida_deseada = salidas.at( pos );
                if( salida_mapeada != salida_deseada  ) {
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

        qDebug() << " Epoca de finalizacion: " << epoca+1 << " - Error de salida de entrenamiento: " << porcentaje_error << "%";

        // Genero las estadisticas con los datos de prueba
        porcentaje_error = 0.0;
        int errores = 0;
        int correcto = 0;
        for( int i = 0; i < part_local.prueba.size(); i++ ) {
            if( red.mapeadorSalidas( red.probarPatron( entradas.at( part_local.prueba.at( i ) ) ) ) != salidas.at( part_local.prueba.at( i ) ) ) {
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
        //        double error_promedio = 0.0;
        //        double desviacion_estandar = 0.0;
        //        double error_aux = 0.0;


        //        for (int i = 0 ; i < errores_epocas.size() ; i++ ) { error_promedio += errores_epocas.at(i);}
        //        error_promedio /= errores_epocas.size();

        //        qDebug() <<"Error Promedio: " << error_promedio << "%";

        //        for (int i = 0 ; i < errores_epocas.size() ; i++ ) { error_aux += exp(errores_epocas.at(i) - error_promedio);}
        //        desviacion_estandar = sqrt( (1.0 / (errores_epocas.size() - 1.0) ) * error_aux );

        //        qDebug() <<"Desviacion Estandar: " << desviacion_estandar << "%";

        errores_epocas.clear();
        PBParticiones->setValue( PBParticiones->value() + 1 );

        QVector<int> nueva_salida;
        matriz nueva_entrada;
        for( int i=0; i<part_local.prueba.size(); i++ ) {
            nueva_salida.append( red.mapeadorSalidas( red.forwardPass( entradas.at( part_local.prueba.at( i ) ) ) ) );
            nueva_entrada.append( entradas.at( part_local.prueba.at( i ) ) );
        }

        if( particiones.cantidadDeParticiones() <= 5 ) {
            GraficadorMdi *graf = new GraficadorMdi( mdiArea );
            mdiArea->addSubWindow( graf );
            graf->show();
            graf->setearTitulo( QString( "Datos de prueba evaluados con red neuronal - Particion %1" ).arg( p+1 ) );
            graf->setearEjesEnGrafico();
            graf->setearTituloEjeX( " X " );
            graf->setearTituloEjeY( " y " );
            graf->agregarPuntosClasificados( nueva_entrada, nueva_salida, stringAQVector( parametros.value( "codificacion_salida" ).toString() ) );
            mdiArea->tileSubWindows();
        }

        QApplication::processEvents();
    }
    qint64 milisegundos = medidor_tiempo.elapsed();

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

    qDebug() << "Tiempo medido: " << milisegundos << " ms";

    if( particiones.cantidadDeParticiones() != 1 ) {
        GraficadorMdi *graf3 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf3 );
        graf3->showMaximized();
        graf3->setearTitulo( "Errores por particion( datos de prueba )" );
        graf3->setearTituloEjeX( "Particion" );
        graf3->setearTituloEjeY( "Error" );
        graf3->agregarCurva( errores_particiones, "Errores" );
        mdiArea->tileSubWindows();
    }

    QVector<int> nueva_salida;
    for( int i=0; i<entradas.size(); i++ ) {
        nueva_salida.append( red.mapeadorSalidas( red.forwardPass( entradas.at(i) ) ) );
    }

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
*/
    return a.exec();

}
