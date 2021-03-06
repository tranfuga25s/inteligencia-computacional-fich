#include <QCoreApplication>

#include <QPointF>
#include <QFile>
#include <QVector>
#include <QStringList>
#include <QDebug>
#include <QPointF>
#include <QPolygonF>
#include "cfloat"
#include "../../../util/funciones_aux.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString nombre_archivo;
    QVector<QPointF> vertices;
    int cant_puntos = 0;
    double max_x, max_y, min_x, min_y;
    max_y = max_x = DBL_MAX * (-1.0);
    min_y = min_x = DBL_MAX;

    QStringList parametros = a.arguments();
/*    foreach( QString parametro, parametros ) {
        qDebug() << parametro;
    }*/

    // Busco el nombre del archivo
    if( parametros.filter( "archivo" ).size() != 0 ) {
        QString temp = parametros.filter( "archivo" ).first();
        QStringList temp2 = temp.split("=");
        temp2.pop_front();
        nombre_archivo = temp2.first();
    } else {
        nombre_archivo = "../t.csv";
    }

    if( parametros.filter( "cantidad_puntos" ).size() != 0 ) {
        QString temp = parametros.filter( "cantidad_puntos" ).first();
        QStringList temp2 = temp.split("=");
        temp2.pop_front();
        cant_puntos = temp2.first().toInt();
    } else {
        qDebug() << "NO se especifico el parametro cantidad_puntos, utilizando 100";
        cant_puntos = 2000;
    }

    // Busco el radio
    if( parametros.filter( "vertices" ).size() != 0 ) {
        QString temp = parametros.filter( "vertices" ).first();
        QStringList temp2 = temp.split("=");
        temp2.pop_front();
        QStringList vert = temp2.first().split( ";" );
        foreach( QString pun, vert ) {
            QStringList coordenada = pun.split(",");
            QPointF punto;
            double x = coordenada.first().toDouble();
            if( x > max_x ) { max_x = x; }
            if( x < min_x ) { min_x = x; }
            punto.setX( x );
            coordenada.pop_front();
            double y = coordenada.first().toDouble();
            if( y > max_y ) { max_y = y; }
            if( y < min_y ) { min_y = y; }
            punto.setY( y );
            vertices.append( punto );
        }
    } else {
        qDebug() << "No se especificaron los vertices de la T! utilizando rpedeterminados";
        vertices << QPointF(  0.25,  0.5 )
                 << QPointF(  1.0 ,  0.5 )
                 << QPointF(  1.0 ,  1.0)
                 << QPointF( -1.0 ,  1.0 )
                 << QPointF( -1.0 ,  0.5 )
                 << QPointF( -0.25 ,  0.5 )
                 << QPointF( -0.25 , -1.0 )
                 << QPointF(  0.25 , -1.0 );
                max_x = 1.0;
                max_y = 1.0;
                min_x = -1.0;
                min_y = -1.0;
    }

    // Genero el poligono para comprobar la posicion
    QPolygonF poligono;
    foreach( QPointF p, vertices ) {
        poligono << p;
    }

    QVector<QPointF> puntos;
    qDebug() << "Generando puntos ";
    while( cant_puntos > 0 ) {
        QPointF pt;
        pt.setX( valor_random( min_x, max_x ) );
        pt.setY( valor_random( min_y, max_y ) );
        if( poligono.containsPoint( pt, Qt::OddEvenFill ) ) {
            puntos.append( pt );
            cant_puntos--;
        }


    }



    // Escribo el archio de salida
    QFile archivo( nombre_archivo );
    if( archivo.open( QIODevice::Truncate | QIODevice::Text | QIODevice::WriteOnly ) ) {
        QTextStream out( &archivo );
        foreach( QPointF p, puntos ) {
            out << p.x() << ", " << p.y() << "\n";
        }
        archivo.flush();
        archivo.close();
        qDebug() << "archivo escrito: " << archivo.fileName();
    } else {
        qDebug() << "No se pudo abrir el archivo de salida!";
    }

    return 0;
}
