﻿#ifndef FUNCIONES_AUX_H
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
            vect_salidas_deseadas->append( divisiones.takeFirst().toDouble() );
            cant++;
        }
        //qDebug() << "Leidas " << cant << " entradas de entrenamiento";
        archivo_entrada.close();
    }
    if( cant > 0 )
    { return true; } else { return false; }
}

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
            for(int j=0;j<vect_entradas->at(i).size();j++)
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
    //Cuida que no haya problemas si ingresan las entradas invertidas
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
 * \brief generarArchivoAleatoriosEntrenamiento
 * \param archivo_entrada
 * \param archivo_salida
 * \param cantidad_extras
 * \param porcentaje_error
 */

static void generarArchivoAleatoriosEntrenamiento( QString archivo_entrada, QString archivo_salida, int cantidad_datos, double porcentaje_variacion ) {
    matriz entradas;
    vector salidas;
    matriz entradas_nuevas;
    vector salidas_nuevas;
    leer_archivo_entrenamiento( archivo_entrada, &entradas, &salidas, 3, 1);

    int generar = floor( cantidad_datos / entradas.size() );
    //qDebug() << generar;

    for( int i=0; i<entradas.size(); i++ ) {

        for( int j=0; j<generar; j++ ) {
            vector temporal = entradas.at(i);

            for (int k = 0 ; k < temporal.size() ; k++){
                        temporal[k] = valor_random( temporal.at(k)*(1.0 - porcentaje_variacion) , temporal.at(k)*(1.0 + porcentaje_variacion) );
            }

            //Guardo en el vector y la matriz nueva los nuevos valores variados
            salidas_nuevas.append( salidas.at(i) );
            entradas_nuevas.append( temporal );
        }

    }

    escribe_archivo_salida( archivo_salida, &entradas_nuevas, &salidas_nuevas );
}

#endif // FUNCIONES_AUX_H
