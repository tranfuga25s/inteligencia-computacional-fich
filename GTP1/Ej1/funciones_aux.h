#ifndef FUNCIONES_AUX_H
#define FUNCIONES_AUX_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QStringList>
#include <QDebug>
#include <QTextStream>

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
                                        int tam_salida )
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
        qDebug() << "Leidas " << cant << " entradas de entrenamiento";
        archivo_entrada.close();
    }
    if( cant > 0 )
    { return true; } else { return false; }
}

//Escribe el archivo con la salida incluyendo las entradas anteriormente leidas

static bool escribe_archivo_salida( QString direccion, matriz* vect_entradas, vector* vect_salidas)
{
    QFile archivo_salida(direccion);
    if( !archivo_salida.exists() ) {
        qDebug() << "El archivo de salida no existe! " << direccion;
        return false;
    }
    QString aux;

    if(archivo_salida.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        for(int i=0;i<vect_entradas->size();i++)
        {
            //agrego al string todas las entradas
            for(int j=0;j<vect_entradas[i].size();j++)
            {
               aux.append(QString::number(vect_entradas->at(i).value(j)));
            }

            //agrego luego la salida obtenida
            aux.append(QString::number(vect_salidas->value(i)));

            //Escribo el string en la linea del archivo
            QTextStream out(&archivo_salida);
            out<<aux<<"endl";
        }

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

#endif // FUNCIONES_AUX_H
