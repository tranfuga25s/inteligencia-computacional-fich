#ifndef FUNCIONES_AUX_H
#define FUNCIONES_AUX_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QStringList>
#include <QDebug>
#include <QTextStream>
#include <math.h>

typedef QVector<double> vector;
typedef QVector< QVector<double> > matriz;

#ifndef LEERARCHIVOENTRENAMIENTO
#define LEERARCHIVOENTRENAMIENTO

static bool leer_archivo_entrenamiento( QString direccion,
                                        matriz* vect_entradas,
                                        matriz* vect_salidas_deseadas,
                                        int tam_entradas,
                                        int tam_salidas)
{

    QFile archivo_entrada( direccion );
    if( !archivo_entrada.exists() ) {
        qDebug() << "El archivo de entrada no existe! " << direccion;
        return false;
    }

    int cant=0;
    // Evita las primeras entradas de constructores nulos que agregas ceros en los vectores.
    vect_entradas->clear();
    vect_salidas_deseadas->clear();
    if(archivo_entrada.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QVector<double> aux;
        while(!archivo_entrada.atEnd())
        {

            //Leo la linea y la proceso almacenandola en los vectores correspondientes
            QString Linea = archivo_entrada.readLine();
            QStringList divisiones = Linea.split( ',', QString::SkipEmptyParts );

            // Guardo las entradas
            for( int i = 0; i<tam_entradas; i++ ) {
                aux.push_back( divisiones.takeFirst().toDouble() );
            }
            vect_entradas->append( aux );
            aux.clear();
            // Guardo las salidas
            for( int i = 0; i<tam_salidas; i++ ) {
                aux.push_back( divisiones.takeFirst().toDouble() );
            }

            vect_salidas_deseadas->append( aux );
            aux.clear();

            cant++;
        }
        //qDebug() << "Leidas " << cant << " entradas de entrenamiento";
        archivo_entrada.close();
    }
    if( cant > 0 )
    { return true; } else { return false; }
}
#endif

/*!
 * \brief leer_archivo_entrenamiento
 * \param direccion
 * \param vect_entradas
 * \param tam_entradas
 * \return
 */
static bool leer_archivo_entrenamiento( QString direccion,
                                        matriz* vect_entradas,
                                        int tam_entradas )
{

    QFile archivo_entrada( direccion );
    if( !archivo_entrada.exists() ) {
        qDebug() << "El archivo de entrada no existe! " << direccion;
        return false;
    }

    int cant=0;
    // Evita las primeras entradas de constructores nulos que agregas ceros en los vectores.
    vect_entradas->clear();
    if(archivo_entrada.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QVector<double> aux;
        while( !archivo_entrada.atEnd() )
        {

            //Leo la linea y la proceso almacenandola en los vectores correspondientes
            QString Linea = archivo_entrada.readLine();
            QStringList divisiones = Linea.split( ',', QString::SkipEmptyParts );

            // Guardo las entradas
            for( int i = 0; i<tam_entradas; i++ ) {
                aux.push_back( divisiones.takeFirst().toDouble() );
            }
            vect_entradas->append( aux );
            cant++;
        }
        //qDebug() << "Leidas " << cant << " entradas de entrenamiento";
        archivo_entrada.close();
    }
    if( cant > 0 )
    { return true; } else { return false; }
}



#ifndef LEERARCHIVOENTRENAMIENTOOLD
#define LEERARCHIVOENTRENAMIENTOOLD
/*!
 * \brief leer_archivo_entrenamiento
 * Recive la direccion de donde lee el archivo y el vector por direccion de los datos de entrada y el vector de salidas deseadas
 * \param direccion Archivo de datos a cargar
 * \param vect_entradas vector de entradas
 * \param vect_salidas_deseadas vector de salidas
 * \return Verdadero si se pudieron cargar al menos una entrada del archivo
 */
static bool leer_archivo_entrenamiento( QString direccion,
                                        matriz* vect_entradas,
                                        vector* vect_salidas_deseadas,
                                        int tam_entradas )
{

    QFile archivo_entrada( direccion );
    if( !archivo_entrada.exists() ) {
        qDebug() << "El archivo de entrada no existe! " << direccion;
        return false;
    }

    int cant=0;
    // Evita las primeras entradas de constructores nulos que agregas ceros en los vectores.
    vect_entradas->clear();
    vect_salidas_deseadas->clear();
    if(archivo_entrada.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QVector<double> aux;
        while(!archivo_entrada.atEnd())
        {

            //Leo la linea y la proceso almacenandola en los vectores correspondientes
            QString Linea = archivo_entrada.readLine();
            QStringList divisiones = Linea.split( ',', QString::SkipEmptyParts );

            // Guardo las entradas
            for( int i = 0; i<tam_entradas; i++ ) {
                aux.push_back( divisiones.takeFirst().toDouble() );
            }
            vect_entradas->append( aux );
            aux.clear();
            // Guardo las salidas
            vect_salidas_deseadas->append( divisiones.takeFirst().toDouble() );
            cant++;
        }
        //qDebug() << "Leidas " << cant << " entradas de entrenamiento";
        archivo_entrada.close();
    }
    if( cant > 0 )
    { return true; } else { return false; }
}


static bool leer_archivo_entrenamiento( QString direccion,
                                        matriz* vect_entradas,
                                        QVector<int>* vect_salidas_deseadas,
                                        int tam_entradas )
{

    QFile archivo_entrada( direccion );
    if( !archivo_entrada.exists() ) {
        qDebug() << "El archivo de entrada no existe! " << direccion;
        return false;
    }

    int cant=0;
    // Evita las primeras entradas de constructores nulos que agregas ceros en los vectores.
    vect_entradas->clear();
    vect_salidas_deseadas->clear();
    if(archivo_entrada.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QVector<double> aux;
        while(!archivo_entrada.atEnd())
        {

            //Leo la linea y la proceso almacenandola en los vectores correspondientes
            QString Linea = archivo_entrada.readLine();
            QStringList divisiones = Linea.split( ',', QString::SkipEmptyParts );

            // Guardo las entradas
            for( int i = 0; i<tam_entradas; i++ ) {
                aux.push_back( divisiones.takeFirst().toDouble() );
            }
            vect_entradas->append( aux );
            aux.clear();
            // Guardo las salidas
            vect_salidas_deseadas->append( divisiones.takeFirst().toInt() );
            cant++;
        }
        //qDebug() << "Leidas " << cant << " entradas de entrenamiento";
        archivo_entrada.close();
    }
    if( cant > 0 )
    { return true; } else { return false; }
}

#endif

//Escribe el archivo con la salida incluyendo las entradas anteriormente leidas

static bool escribe_archivo_salida( QString direccion, matriz* vect_entradas, vector* vect_salidas)
{
    QFile archivo_salida(direccion);
    QString aux;

    if(archivo_salida.open(  QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
    {
        QTextStream out(&archivo_salida);
        for(int i=0;i<vect_entradas->size();i++)
        {
            //agrego al string todas las entradas
            for(int j=0;j<vect_entradas->at( i).size();j++)
            {
               aux.append(QString::number(vect_entradas->at(i).value(j)));
               aux.append( ", " );
            }

            //agrego luego la salida obtenida
            aux.append(QString::number(vect_salidas->value(i)));
            aux.append( "\n" );
            //Escribo el string en la linea del archivo

        }
        out<<aux;
        archivo_salida.close();
    }
    return true;
}


/*!
 * \brief valor_random
 * Funcion para generar un valor aleatorio entre min y max
 * \param min
 * \param max
 * \return
 */
static double valor_random(double min,double max)
{

    double aleatorio = ((double) qrand()) / (double) RAND_MAX;

    if (min>max)
    {
        double rango = min - max;
        return (aleatorio*rango) + max;
    }
    else
    {
        double rango = max - min;
        return (aleatorio*rango) + min;
    }
}

/*!
 * \brief mostrarVector
 * \param v
 */
static void mostrarVector( const vector v ) {
    qDebug() << v;
}

/*!
 * \brief mostrarMatriz
 * \param m
 */
static void mostrarMatriz( const matriz m ) {
    for( int i=0; i<m.size(); i++) {
        qDebug() << "Fila " << i << " " << m.at( i );
    }
}

/*!
 * \brief randomizarEntradas
 * \param tam_datos
 * \return
 */
static QVector<int> randomizarEntradas( int tam_datos ) {
    QVector<int> temp1;
    for( int i=0; i<tam_datos; i++ ) {
        temp1.append(i);
    }
    QVector<int> retorno;
    for( int i=0;i<tam_datos; i++ ) {
        int pos = qrand() % temp1.size();
        retorno.append( temp1.at( pos ) );
        temp1.remove( pos );
    }
    return retorno;
}

/*!
 * \brief generarArchivoAleatoriosPrueba
 * Escribe un archivo de salida con los datos de entradas agregando el porcentaje de variacion a cada entrada.
 * \param archivo_entrada Nombre del archivo de entrada
 * \param archivo_salida Nombre del archivo a escribir
 * \param cantidad_extras Cantidad de datos extras a generar por cada entrada
 * \param porcentaje_error Porcentaje de error a aplicar a la variación
 * \param tamano_entradas Cantidad de datos que poseen las entradas
 */
static void generarArchivoAleatoriosPruebaRadial( QString archivo_entrada, QString archivo_salida, int cantidad_extras, double porcentaje_variacion, int tamano_entradas ) {
    matriz entradas;
    vector salidas;
    matriz entradas_nuevas;
    leer_archivo_entrenamiento( archivo_entrada, &entradas, &salidas, tamano_entradas );
    for( int i=0; i<entradas.size(); i++ ) {

        //entradas_nuevas.append( entradas.at( i ) );
        salidas[i]=0;
        for( int j=0; j<cantidad_extras; j++ ) {
            vector temporal = entradas.at(i);

            double radio = valor_random( 0.0 , porcentaje_variacion);
            double angulo = valor_random( 0.0, 365.0 );

            temporal[0] = temporal.at(0) + radio * cos( angulo );
            temporal[1] = temporal.at(1) + radio * sin( angulo );

            //Guardo en el vector y la matriz nueva los nuevos valores variados
            salidas.append( 0 );
            entradas_nuevas.append( temporal );
        }

    }
    escribe_archivo_salida( archivo_salida, &entradas_nuevas, &salidas );
}

/*!
 * \brief generarArchivoAleatoriosPrueba
 * \param archivo_entrada
 * \param archivo_salida
 * \param cantidad_extras
 * \param porcentaje_variacion
 * \param tamano_entradas
 */

static void generarArchivoAleatoriosPrueba( QString archivo_entrada, QString archivo_salida, int cantidad_extras, double porcentaje_variacion, int tamano_entradas ) {
    matriz entradas;
    vector salidas;
    matriz entradas_nuevas;
    leer_archivo_entrenamiento( archivo_entrada, &entradas, &salidas, tamano_entradas );
    for( int i=0; i<entradas.size(); i++ ) {

        //entradas_nuevas.append( entradas.at( i ) );
        salidas[i]=0;
        for( int j=0; j<cantidad_extras; j++ ) {
            vector temporal = entradas.at(i);

            //for (int k = 0 ; k < entradas.at(i).size() ; k++){
            //            temporal[k] = valor_random( temporal.at(k)*(1.0 - porcentaje_variacion) , temporal.at(k)*(1.0 + porcentaje_variacion) );
            //}

            double radio =  valor_random( 0.0 , porcentaje_variacion);
            double angulo = valor_random( 0.0, 365.0 );

            temporal[0] = temporal.at(0) + radio * cos( angulo );
            temporal[1] = temporal.at(1) + radio * sin( angulo );
            temporal[2] = temporal.at(2) + radio * cos( angulo );

            //Guardo en el vector y la matriz nueva los nuevos valores variados
            salidas.append( 0 );
            entradas_nuevas.append( temporal );
        }

    }
    escribe_archivo_salida( archivo_salida, &entradas_nuevas, &salidas );
}


/*!
 * \brief generarArchivoAleatoriosEntrenamiento
 * \param archivo_entrada Nombre del archivo de entrada
 * \param archivo_salida Nombre del archivo a escribir
 * \param cantidad_extras Cantidad de datos extras a generar por cada entrada
 * \param porcentaje_error Porcentaje de error a aplicar a la variación
 * \param tamano_entradas Cantidad de datos que poseen las entradas
 */

static void generarArchivoAleatoriosEntrenamientoRadial( QString archivo_entrada, QString archivo_salida, int cantidad_extras, double porcentaje_variacion, int tamano_entradas ) {
    matriz entradas;
    vector salidas;
    matriz entradas_nuevas;
    vector salidas_nuevas;
    leer_archivo_entrenamiento( archivo_entrada, &entradas, &salidas, tamano_entradas );
    for( int i=0; i<entradas.size(); i++ ) {

        for( int j=0; j<cantidad_extras; j++ ) {
            vector temporal = entradas.at(i);

            double radio =  valor_random( 0.0 , porcentaje_variacion);
            double angulo = valor_random( 0.0, 365.0 );

            temporal[0] = temporal.at(0) + radio * cos( angulo );
            temporal[1] = temporal.at(1) + radio * sin( angulo );

            //Guardo en el vector y la matriz nueva los nuevos valores variados
            salidas_nuevas.append( salidas.at(i) );
            entradas_nuevas.append( temporal );
        }

    }
    escribe_archivo_salida( archivo_salida, &entradas_nuevas, &salidas_nuevas );
}


#ifndef GENERARARCHIVOALEATORIOENTRENAMIENTO
#define GENERARARCHIVOALEATORIOENTRENAMIENTO
/*!
 * \brief generarArchivoAleatoriosEntrenamiento
 * \param archivo_entrada
 * \param archivo_salida
 * \param cantidad_extras
 * \param porcentaje_variacion
 * \param tamano_entradas
 */
static void generarArchivoAleatoriosEntrenamiento( QString archivo_entrada, QString archivo_salida, int cantidad_extras, double porcentaje_variacion, int tamano_entradas ) {
    matriz entradas;
    vector salidas;
    matriz entradas_nuevas;
    vector salidas_nuevas;
    leer_archivo_entrenamiento( archivo_entrada, &entradas, &salidas, tamano_entradas );
    for( int i=0; i<entradas.size(); i++ ) {

        for( int j=0; j<cantidad_extras; j++ ) {
            vector temporal = entradas.at(i);

            //for (int k = 0 ; k < entradas.at(i).size() ; k++){
            //            temporal[k] = valor_random( temporal.at(k)*(1.0 - porcentaje_variacion) , temporal.at(k)*(1.0 + porcentaje_variacion) );
            //}

            double radio =  valor_random( 0.0 , porcentaje_variacion);
            double angulo = valor_random( 0.0, 365.0 );

            temporal[0] = temporal.at(0) + radio * cos( angulo );
            temporal[1] = temporal.at(1) + radio * sin( angulo );
            temporal[2] = temporal.at(2) + radio * cos( angulo );

            //Guardo en el vector y la matriz nueva los nuevos valores variados
            salidas_nuevas.append( salidas.at(i) );
            entradas_nuevas.append( temporal );
        }

    }
    escribe_archivo_salida( archivo_salida, &entradas_nuevas, &salidas_nuevas );
}

#endif

#ifndef STRINGAVECTOR
#define STRINGAVECTOR

static QVector<int> stringAQVector( QString datos, QString separador = " " ) {
    QVector<int> retorno;
    QVector<QString> temp = datos.split( separador, QString::KeepEmptyParts ).toVector();
    QVector<int> neuronas_por_capas;
    foreach( QString temp2, temp ) {
        retorno.append( temp2.toInt() );
    }
    return retorno;
}

static int max_x_matriz(int columna,int distancia_obtenida,int cant_col) {
    int i = columna;
    while (i <= (columna + distancia_obtenida) && i < cant_col)  {
        i++;
    }
    return i;
}

static int min_x_matriz(int columna,int distancia_obtenida) {
    int i = columna;
    while (i >= (columna - distancia_obtenida) && i > 0)  {
        i--;
    }
    return i;
}

static int max_y_matriz(int fila,int distancia_obtenida,int cant_fil) {
    int i = fila;
    while (i <= (fila + distancia_obtenida) && i < cant_col)  {
        i++;
    }
    return i;
}

static int min_y_matriz(int fila,int distancia_obtenida) {
    int i = fila;
    while (i >= (fila - distancia_obtenida) && i > 0)  {
        i--;
    }
    return i;
}


#endif

#endif // FUNCIONES_AUX_H
