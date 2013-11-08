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
 * Ejercicio 3 Guia de Trabajos Practicos 2
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

//    GraficadorMdi *graf1 = new GraficadorMdi( mdiArea );
//    graf1->setearTitulo( QString::fromUtf8( "Porcentaje de error según particion ( entrenamiento )" ) );
//    graf1->setearTituloEjeX( QString::fromUtf8( "Epoca" ) );
//    graf1->setearTituloEjeY( QString::fromUtf8( "Porcentaje error" ) );
//    mdiArea->addSubWindow( graf1 );
//    mdiArea->tileSubWindows();

    // Archivo de entrada
    QString archivo = QCoreApplication::applicationDirPath().append( QDir::separator() ).append( parametros.value( "archivo_entrada" ).toString() );

    // Cargo los datos de los archivos que corresponda
    matriz entradas( parametros.value( "cantidad_entradas" ).toInt() );
    QVector<int> salidas (parametros.value( "cantidad_salidas" ).toInt());

    qDebug() << endl << "--------------- /Datos del entrenamiento/ -----------------" << endl;
    qWarning() << "Archivo de lectura de datos originales: "<< archivo;
    if( ! leer_archivo_entrenamiento( archivo,
                                      &entradas,
                                      &salidas,
                                      parametros.value( "tamano_entradas" ).toInt())  ) {
        qDebug() << "No se pudo encontrar el archivo de entrenamiento! cancelando!";
        abort();
    }

//    //Grafico los originales

    if( parametros.value( "tamano_entradas" ).toInt() == 2 ) {
        // Grafico los datos de clouds
        GraficadorMdi *graf2 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf2 );
        graf2->showMaximized();
        graf2->setearTitulo( "Datos originales" );
        graf2->setearTituloEjeX( " X " );
        graf2->setearTituloEjeY( " Y " );
        graf2->agregarPuntosClasificados( entradas, salidas, 0.5 );
        mdiArea->tileSubWindows();
    } else {
        // Grafico como para utilizar phoneme
        // Contiene 5 dimensiones
        matriz entradas1, entradas2, entradas3, entradas4, entradas5;

        // ver porque el graficador necesita 2 dimensiones x elemento a graficar!
        for( int i=0; i < entradas.size(); i++ ) {
            vector temp1, temp2, temp3, temp4, temp5;
            //1er Armonico
            temp1.append( entradas.at(i).at(0) );
            temp1.append( i );
            entradas1.append( temp1 );

            //2do Armonico
            temp2.append( entradas.at(i).at(1) );
            temp2.append( i );
            entradas2.append( temp2 );

            //3er Armonico
            temp3.append( entradas.at(i).at(2) );
            temp3.append( i );
            entradas3.append( temp3 );

            //4to Armonico
            temp4.append( entradas.at(i).at(3) );
            temp4.append( i );
            entradas4.append( temp4 );

            //5to Armonico
            temp5.append( entradas.at(i).at(4) );
            temp5.append( i );
            entradas5.append( temp5 );
        }

        GraficadorMdi *graf2 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf2 );
        graf2->showMaximized();
        graf2->setearTitulo( "Datos originales - 1º Armonico" );
        graf2->setearTituloEjeX( " X " );
        graf2->setearTituloEjeY( " Y " );
        graf2->agregarPuntosClasificados( entradas1, salidas, 0.5 );
        mdiArea->tileSubWindows();

        GraficadorMdi *graf3 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf3 );
        graf3->showMaximized();
        graf3->setearTitulo( "Datos originales - 2º Armonico" );
        graf3->setearTituloEjeX( " X " );
        graf3->setearTituloEjeY( " Y " );
        graf3->agregarPuntosClasificados( entradas2, salidas, 0.5  );
        mdiArea->tileSubWindows();

        GraficadorMdi *graf4 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf4 );
        graf4->showMaximized();
        graf4->setearTitulo( "Datos originales - 3º Armonico" );
        graf4->setearTituloEjeX( " X " );
        graf4->setearTituloEjeY( " Y " );
        graf4->agregarPuntosClasificados( entradas3, salidas, 0.5  );
        mdiArea->tileSubWindows();

        GraficadorMdi *graf5 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf5 );
        graf5->showMaximized();
        graf5->setearTitulo( "Datos originales - 4º Armonico" );
        graf5->setearTituloEjeX( " X " );
        graf5->setearTituloEjeY( " Y " );
        graf5->agregarPuntosClasificados( entradas4, salidas, 0.5  );
        mdiArea->tileSubWindows();

        GraficadorMdi *graf6 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf6 );
        graf6->showMaximized();
        graf6->setearTitulo( "Datos originales - 5º Armonico" );
        graf6->setearTituloEjeX( " X " );
        graf6->setearTituloEjeY( " Y " );
        graf6->agregarPuntosClasificados( entradas5, salidas, 0.5  );
        mdiArea->tileSubWindows();
    }

    a.processEvents();

    // Inicializo el SOM
       SOM som( parametros.value( "som_tam_x", 2 ).toInt(),
                  parametros.value( "som_tam_y", 2 ).toInt(),
                  parametros.value( "tamano_entradas" ).toInt() );



       qDebug() << endl << "---------------- /Comienza el entrenamiento/ ----------------";

    QVector<int> epocas = stringAQVector( parametros.value( "epocas" ).toString() );
    QVector<double> tasas = stringAQVectord( parametros.value( "tasa_aprendizaje" ).toString() );
    int cant_clases =  parametros.value( "cant_clases" ).toInt();
    QVector<int> tamano_vecindades = stringAQVector( parametros.value( "radio_vecindad" ).toString() );


    //Habria que usar particiones???

    QElapsedTimer medidor_tiempo;
    medidor_tiempo.start();

    // -----Etapa de Ordenamiento Global-----
    QVector<int> tamano_vecindad1 = distribucionEquitativa( epocas.at( 0 ), tamano_vecindades.at(1), tamano_vecindades.at(0) );
    QVector<double> tasa_aprendizajes1 = aproximacionLineald( epocas.at( 0 ), tasas.at( 0 ), tasas.at( 1 ) );

    for( int epoca=0; epoca<epocas.at(0); epoca++ ) {

        som.setearRadioVecindad( tamano_vecindad1.at( epoca ) );
        som.setearTasaAprendizaje( tasa_aprendizajes1.at( epoca ) );
        for( int p=0; p<entradas.size(); p++ ) {

            som.entrenar( entradas.at( p ) );

        }

    }

    // -----Etapa de transición------
    QVector<int> tamano_vecindad2 = distribucionEquitativa( epocas.at( 1 ), tamano_vecindades.at(2), tamano_vecindades.at(1));
    QVector<double> tasa_aprendizajes2 = aproximacionLineald( epocas.at( 1 ), tasas.at( 1 ), tasas.at( 2 ) );


    for( int epoca=0; epoca<epocas.at(1); epoca++ ) {

        som.setearRadioVecindad( tamano_vecindad2.at( epoca ) );
        som.setearTasaAprendizaje( tasa_aprendizajes2.at( epoca ) );

        for( int p=0; p<entradas.size(); p++ ) {

            som.entrenar( entradas.at( p ) );

        }

    }

    // -----Etapa de ajuste fino-----
    som.setearRadioVecindad( 0 );
    QVector<double> tasa_aprendizajes3 = aproximacionLineald( epocas.at( 2 ), tasas.at( 2 ), tasas.at( 3 ) );

    for( int epoca=0; epoca<epocas.at(2); epoca++ ) {

        som.setearTasaAprendizaje( tasa_aprendizajes3.at( epoca ) );

        for( int p=0; p<entradas.size(); p++ ) {

            som.entrenar( entradas.at( p ) );

        }

    }

    qDebug()<< "------------------Fin del Entrenamiento--------------------";

    qint64 milisegundos = medidor_tiempo.elapsed();

    qDebug() << "Tiempo medido: " << milisegundos << " ms";

    // ----Comienzo el etiquetado-----
    cant_clases =  parametros.value( "cant_clases" ).toInt();
    // Matrices de conteo de activacion
    QVector< QVector< QVector<int> > > contadores(cant_clases);
    //Clases
    for( int clase=0; clase<cant_clases; clase++ ) {
        contadores[clase].resize(parametros.value( "som_tam_x", 2 ).toInt()); // Pre reserva el espacio
        //Filas
        for( int f=0; f<contadores.at(clase).size(); f++ ) {
            contadores[clase][f].resize(parametros.value( "som_tam_y", 2 ).toInt());// Prereserva el espacio
            //Columnas
            for( int c=0; c<contadores.at(clase).at(f).size() ; c++ ) {
                contadores[clase][f][c] = 0; // pongo los contadores en cero
            }
        }
    }

    // Para cada patron busco cual es la neurona ganadora y aumento su contador
    QPair<int,int> pos;
    // Recorro todas las entradas
    for( int entrada = 0; entrada < entradas.size(); entrada++ ) {

        pos = som.getNeuronaGanadora( entradas.at( entrada ) );

        int clase = salidas.at( entrada );

        contadores[clase][pos.first][pos.second] += 1;
    }

    // Busco a que etiqueta corresponde cada uno viendo cual es el número de conteo de clase más alto
    for( int fila=0; fila<parametros.value( "som_tam_x", 2 ).toInt(); fila++ ) {
        for( int columna=0; columna<parametros.value( "som_tam_y", 2 ).toInt(); columna++ ) {

            int maximo = -1;
            int clase = -1;
            for( int c=0; c<cant_clases; c++ ) {
                if( contadores.at( c ).at( columna ).at( fila ) > maximo ) {
                    clase = c;
                    maximo = contadores.at( c ).at( columna ).at( fila );
                }
            }
            // Seteo la clase según corresponda
            som.setearClase( fila, columna, clase );
        }

    }

    //Cargo las salidas del som en un vector asi las puedo graficar
    //Para esto tendria que recorrer las entradas buscar las neuronas ganadoras y asignarle la clase que tiene asociada
    QVector<int> nuevas_salidas;
    double cant_errores;

    for( int entrada = 0; entrada < entradas.size(); entrada++ ) {

        //Evaluo
        pos = som.getNeuronaGanadora( entradas.at( entrada ) );

        if(som.devolverClasesSalida(pos.first,pos.second) != salidas.at(entrada)) {cant_errores++;}

        nuevas_salidas.append(som.devolverClasesSalida(pos.first,pos.second));
    }

    double porcentaje_error = (cant_errores * 100) / entradas.size();

    qDebug() << "CANTIDAD DE ERRORES EN EL SOM" << cant_errores;

    qDebug() << "PORCENTAJE DE ERROR EN LA CLASIFICACION" << porcentaje_error << "%";

    //Ya tengo la nueva evaluacion de todos los patrones en la red som
    // Mostrar resultado de la clasificacion
    // Si el tamaño es = 2 => clouds
    if( parametros.value( "tamano_entradas" ).toInt() == 2 ) {
        // Grafico los datos de clouds
        GraficadorMdi *graf2 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf2 );
        graf2->showMaximized();
        graf2->setearTitulo( "Datos Clasificados" );
        graf2->setearTituloEjeX( " X " );
        graf2->setearTituloEjeY( " Y " );
        graf2->agregarPuntosClasificados( entradas, nuevas_salidas, 0.5 );
        mdiArea->tileSubWindows();
    } else {
        // Grafico como para utilizar phoneme
        // Contiene 5 dimensiones
        matriz entradas1, entradas2, entradas3, entradas4, entradas5;
        // ver porque el graficador necesita 2 dimensiones x elemento a graficar!
        for( int i=0; i < entradas.size(); i++ ) {
            vector temp1, temp2, temp3, temp4, temp5;
            temp1.append( entradas.at(i).at(0) );
            temp1.append( i );
            entradas1.append( temp1 );
            temp2.append( entradas.at(i).at(1) );
            temp2.append( i );
            entradas2.append( temp2 );
            temp3.append( entradas.at(i).at(2) );
            temp3.append( i );
            entradas3.append( temp3 );
            temp4.append( entradas.at(i).at(3) );
            temp4.append( i );
            entradas4.append( temp4 );
            temp5.append( entradas.at(i).at(4) );
            temp5.append( i );
            entradas5.append( temp5 );
        }
        GraficadorMdi *graf2 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf2 );
        graf2->showMaximized();
        graf2->setearTitulo( "Datos Clasificados - 1º Armonico" );
        graf2->setearTituloEjeX( " X " );
        graf2->setearTituloEjeY( " Y " );
        graf2->agregarPuntosClasificados( entradas1, nuevas_salidas, 0.5 );
        mdiArea->tileSubWindows();

        GraficadorMdi *graf3 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf3 );
        graf3->showMaximized();
        graf3->setearTitulo( "Datos Clasificados - 2º Armonico" );
        graf3->setearTituloEjeX( " X " );
        graf3->setearTituloEjeY( " Y " );
        graf3->agregarPuntosClasificados( entradas2, nuevas_salidas, 0.5 );
        mdiArea->tileSubWindows();

        GraficadorMdi *graf4 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf4 );
        graf4->showMaximized();
        graf4->setearTitulo( "Datos Clasificados- 3º Armonico" );
        graf4->setearTituloEjeX( " X " );
        graf4->setearTituloEjeY( " Y " );
        graf4->agregarPuntosClasificados( entradas3, nuevas_salidas, 0.5 );
        mdiArea->tileSubWindows();

        GraficadorMdi *graf5 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf5 );
        graf5->showMaximized();
        graf5->setearTitulo( "Datos Clasificados - 4º Armonico" );
        graf5->setearTituloEjeX( " X " );
        graf5->setearTituloEjeY( " Y " );
        graf5->agregarPuntosClasificados( entradas4, nuevas_salidas, 0.5 );
        mdiArea->tileSubWindows();

        GraficadorMdi *graf6 = new GraficadorMdi( mdiArea );
        mdiArea->addSubWindow( graf6 );
        graf6->showMaximized();
        graf6->setearTitulo( "Datos Clasificados - 5º Armonico" );
        graf6->setearTituloEjeX( " X " );
        graf6->setearTituloEjeY( " Y " );
        graf6->agregarPuntosClasificados( entradas5, nuevas_salidas, 0.5 );
        mdiArea->tileSubWindows();
    }


    return a.exec();

}
