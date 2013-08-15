#ifndef FUNCIONES_AUX_H
#define FUNCIONES_AUX_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QStringList>
#include <QDebug>
/*

Recive la direccion de donde lee el archivo
y el vector por direccion de los datos de entrada
y el vector de salidas deseadas

*/

static void leer_archivo_entrenamiento(QString direccion,QVector< QVector<double> >* vect_entradas, QVector< QVector<double> >* vect_salidas_deseadas)
{

    QFile archivo_entrada(direccion);
    if( !archivo_entrada.exists() ) {
        qDebug() << "El archivo de entrada no existe! " << direccion;
    }

    if(archivo_entrada.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int cant=0;
        QVector<double> aux(vect_entradas->size());
        QVector<double> aux2(vect_salidas_deseadas->size());
        while(!archivo_entrada.atEnd())
        {

            //Leo la linea y la proceso almacenandola en los vectores correspondientes
            QString Linea = archivo_entrada.readLine();
            QStringList divisiones = Linea.split( ',', QString::SkipEmptyParts );

            for( int i = 0; i<vect_entradas->size(); i++ ) {
                aux.push_back( divisiones.takeFirst().toDouble() );
            }
            vect_entradas->push_back(aux);
            aux.clear();
            for( int i = 0; i<vect_salidas_deseadas->size(); i++ ) {
                aux2.push_back( divisiones.takeFirst().toDouble() );
            }
            vect_salidas_deseadas->push_back(aux2);
            aux2.clear();
            cant++;
        }
        qDebug() << "Leidas " << cant << " entradas de entrenamiento";
        archivo_entrada.close();
    }
}

//Funcion para generar un valor aleatorio entre min y max

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



#endif // FUNCIONES_AUX_H
