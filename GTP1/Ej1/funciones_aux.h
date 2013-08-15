#ifndef FUNCIONES_AUX_H
#define FUNCIONES_AUX_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QStringList>
#include <QDebug>

typedef QVector<double> vector;
typedef QVector< QVector<double> > matriz;

/*!
 * \brief leer_archivo_entrenamiento
 * Recive la direccion de donde lee el archivo y el vector por direccion de los datos de entrada y el vector de salidas deseadas
 * \param direccion Archivo de datos a cargar
 * \param vect_entradas vector de entradas
 * \param vect_salidas_deseadas vector de salidas
 */
static bool leer_archivo_entrenamiento( QString direccion, matriz* vect_entradas, vector* vect_salidas_deseadas)
{

    QFile archivo_entrada( direccion );
    if( !archivo_entrada.exists() ) {
        qDebug() << "El archivo de entrada no existe! " << direccion;
        return false;
    }

    if(archivo_entrada.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int cant=0;
        vector aux(vect_entradas->size());

        while(!archivo_entrada.atEnd())
        {

            //Leo la linea y la proceso almacenandola en los vectores correspondientes
            QString Linea = archivo_entrada.readLine();
            QStringList divisiones = Linea.split( ',', QString::SkipEmptyParts );

            // Guardo las entradas
            for( int i = 0; i<vect_entradas->size(); i++ ) {
                aux.push_back( divisiones.takeFirst().toDouble() );
            }
            vect_entradas->push_back(aux);
            aux.clear();
            // Guardo las salidas
            vect_salidas_deseadas->push_back( divisiones.takeFirst().toDouble() );
            cant++;
        }
        qDebug() << "Leidas " << cant << " entradas de entrenamiento";
        archivo_entrada.close();
    }
    return true;
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
