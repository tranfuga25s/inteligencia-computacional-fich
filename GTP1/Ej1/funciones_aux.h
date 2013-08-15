#ifndef FUNCIONES_AUX_H
#define FUNCIONES_AUX_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QTextStream>

/*
 *Recibe la direccion de donde lee el archivo
 *y el vector por direccion de los datos de entrada
 *y el vector de salidas deseadas
 *
 *Formato por linea "entrada1,entrada2,salida_deseada"
*/

static void leer_archivo_entrenamiento(QString direccion,QVector< QVector<double> >* vect_entradas_entrenamiento, QVector<double>* vect_salidas_deseadas)
{
    QFile archivo_entrada(direccion);

    if(archivo_entrada.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int i=0;
        QVector<double> aux;
        while(!archivo_entrada.atEnd())
        {

            QString Linea = archivo_entrada.readLine();

            //Entradas - Tendria que ser generico para mas de dos argumentos
            //Podria ser con el -1 que indica end en section

            aux.push_back(Linea.section(",",0).toDouble());
            aux.push_back(Linea.section(",",1).toDouble());

            vect_entradas_entrenamiento->push_back(aux);

            //Salidas ideales (-1 indica end section)
            vect_salidas_deseadas->push_back(Linea.section(",",-1).toDouble());

            i++;
        }

        archivo_entrada.close();
    }
}

//Escribe el archivo con la salida incluyendo las entradas anteriormente leidas

static void escribe_archivo_salida(QString direccion,QVector< QVector<double> >* vect_entradas,QVector<double>* vect_salidas)
{
    QFile archivo_salida(direccion);
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
}


//Para leer las entradas de prueba

static void leer_entradas_prueba(QString direccion,QVector< QVector<double> >* vect_entradas)
{
    QFile archivo_entrada(direccion);

    if(archivo_entrada.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int i=0;
        QVector<double> aux;
        while(!archivo_entrada.atEnd())
        {

            //Leo la linea y la proceso almacenandola en los vectores correspondientes
            QString Linea = archivo_entrada.readLine();

            //Entradas - Tendria que ser generico para mas de dos argumentos
            //Podria ser con el -1 que indica end en section

            aux.push_back(Linea.section(",",0).toDouble());
            aux.push_back(Linea.section(",",1).toDouble());

            vect_entradas->push_back(aux);

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
