#ifndef FUNCIONES_AUX_H
#define FUNCIONES_AUX_H

#include <QObject>
#include <QFile>
#include <QVector>

/*

Recive la direccion de donde lee el archivo
y el vector por direccion de los datos de entrada
y el vector de salidas deseadas

*/

static void leer_archivo_entrenamiento(QString direccion,QVector< QVector<double> >* vect_entradas, QVector<double>* vect_salidas_deseadas)
{
    QFile archivo_entrada(direccion);

    if(archivo_entrada.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int i=0;
        QVector<double> aux(2);
        while(!archivo_entrada.atEnd())
        {

            //Leo la linea y la proceso almacenandola en los vectores correspondientes
            QString Linea = archivo_entrada.readLine();

            aux[0]=Linea.section(",",0).toDouble();
            aux[1]=Linea.section(",",1).toDouble();
            vect_entradas->push_back(aux);

            vect_salidas_deseadas->push_back(Linea.section(",",2).toDouble());
            i++;
        }

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
