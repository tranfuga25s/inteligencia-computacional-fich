#include <QCoreApplication>
#include <QPointF>
#include <QStringList>
#include "../../../util/funciones_aux.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString nombre_archivo;
    QVector<QPointF> centro;
    double radio = 0.0;
    int cant_puntos = 0;

    QStringList parametros = a.arguments();

    // Busco el nombre del archivo
    if( parametros.filter( "archivo" ).size() != 0 ) {
        QString temp = parametros.filter( "archivo" ).first();
        QStringList temp2 = temp.split("=");
        temp2.pop_front();
        nombre_archivo = temp2.first();
    } else {
        nombre_archivo = "circulo.csv";
    }

    if( parametros.filter( "cantidad_puntos" ).size() != 0 ) {
        QString temp = parametros.filter( "cantidad_puntos" ).first();
        QStringList temp2 = temp.split("=");
        temp2.pop_front();
        cant_puntos = temp2.first().toInt();
    } else {
        qDebug() << "No se especifico el parametro cantidad_puntos, utilizando 100";
        cant_puntos = 100;
    }

    // Busco el radio
    if( parametros.filter( "centro" ).size() != 0 ) {
        QString temp = parametros.filter( "centro" ).first();
        QStringList temp2 = temp.split("=");
        temp2.pop_front();
        // Busco el punto del centro
        QStringList vert = temp2.first().split( ";" );
        foreach( QString pun, vert ) {
            QStringList coordenada = pun.split(",");
            QPointF punto;
            punto.setX( coordenada.first().toDouble() );
            coordenada.pop_front();
            punto.setY( coordenada.first().toDouble() );
            centro.append( punto );
        }
    } else {
        qDebug() << "No se especifico el centro del circulo!";
        abort();
    }

    // Busco el radio
    if( parametros.filter( "radio" ).size() != 0 ) {
        QString temp = parametros.filter( "radio" ).first();
        QStringList temp2 = temp.split("=");
        temp2.pop_front();
        // Busco el punto del centro
        radio = temp2.first().toDouble();
    } else {
        qDebug() << "No se especifico el radio del circulo!";
        abort();
    }

    QVector<QPointF> puntos;
    qDebug() << "Generando puntos ";
    while( cant_puntos > 0 ) {
        QPointF pt;
        double radio_pt = valor_random( 0.0, radio );
        double angulo_pt = valor_random( 0.0, 365.0 );

        pt.setX( centro.at(0).x() + radio_pt * cos( angulo_pt ) );
        pt.setY( centro.at(0).y() + radio_pt * sin( angulo_pt ) );
        puntos.append( pt );
        cant_puntos--;
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
