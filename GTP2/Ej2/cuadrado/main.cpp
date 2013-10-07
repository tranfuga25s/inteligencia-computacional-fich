#include <QCoreApplication>

#include <QFile>
#include <QStringList>
#include <QString>
#include <QVector>
#include <QPoint>
#include <cfloat>
#include <../../../util/funciones_aux.h>

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
        QString temp = parametros.filter( "--archivo" ).first();
        QStringList temp2 = temp.split("=");
        temp2.pop_front();
        nombre_archivo = temp2.first();
    } else {
        nombre_archivo = "../cuadrado.csv";
    }

    if( parametros.filter( "cantidad_puntos" ).size() != 0 ) {
        QString temp = parametros.filter( "cantidad_puntos" ).first();
        QStringList temp2 = temp.split("=");
        temp2.pop_front();
        cant_puntos = temp2.first().toInt();
    } else {
        qDebug() << "NO se especifico el parametro cantidad_puntos, utilizando 500";
        cant_puntos = 500;
    }

    // Busco el radio
    if( parametros.filter( "vertices" ).size() != 0 ) {
        QString temp = parametros.filter( "--vertices" ).first();
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
        qDebug() << "No se especificaron los vertices del rectangulo! usando predeterminados";
        vertices << QPointF( 1.0, -1.0 )
                 << QPointF( 1.0, 1.0 )
                 << QPointF( -1.0, 1.0 )
                 << QPointF( -1.0, -1.0 );
        max_x = max_y = 1.0;
        min_x = min_y = -1.0;
    }

    QVector<QPointF> puntos;
    qDebug() << "Generando puntos ";
    while( cant_puntos > 0 ) {
        QPointF pt;
        pt.setX( valor_random( min_x, max_x ) );
        pt.setY( valor_random( min_y, max_y ) );
        puntos.append( pt );
        cant_puntos--;
    }

    // Escribo el archio de salida
    QFile archivo( nombre_archivo );
    if( archivo.open( QIODevice::Truncate | QIODevice::Text | QIODevice::WriteOnly ) ) {
        QTextStream out( &archivo );
        int contador = 0;
        foreach( QPointF p, puntos ) {
            out << p.x() << ", " << p.y() << "\n";
            contador++;
        }
        qDebug() << "Escritos " << contador << " puntos ";
        archivo.flush();
        archivo.close();
        qDebug() << "archivo escrito: " << archivo.fileName();
    } else {
        qDebug() << "No se pudo abrir el archivo de salida!";
    }

    return 0;
}
