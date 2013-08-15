#include <QCoreApplication>
#include <QDebug>
#include <QTime>
#include <QDir>
#include <QVector>
#include <QSettings>

typedef QVector<double> vector;
typedef QVector< QVector<double> > matriz;

#include "funciones_aux.h"
#include "neurona.h"

/*!
 * \brief main
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char *argv[])
{
    QCoreApplication a( argc, argv );

    //Inicializo con una semilla aleatoria para la generacion de Aleatorios
    qsrand(QTime::currentTime().msec());

    // Cargo los parametros del ejercicio
    QSettings parametros( "parametros.cfg", QSettings::IniFormat );
    
    // Cargo los datos de los archivos que corresponda
    matriz entradas( parametros.value( "cant_entradas" ).toInt() );
    vector salidas( parametros.value( "cant_salidas" ).toInt() );

    QString archivo = QCoreApplication::applicationDirPath().append( QDir::separator() ).append( parametros.value( "archivo" ).toString() );
    qWarning() << archivo;
    if( ! leer_archivo_entrenamiento( archivo, &entradas, &salidas) ) {
        qDebug() << "No se pudo encontrar el archivo de entrenamiento! cancelando!";
        abort();
    }

    Neurona n( 0, entradas.size() );
    n.setearTasaAprendizaje( 0.25 );

    return 0;
}
