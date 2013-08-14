#include <QCoreApplication>
#include <QDebug>
#include <QTime>

int main(int argc, char *argv[])
{
    QCoreApplication a( argc, argv );

    //Inicializo con una semilla aleatoria para la generacion de Aleatorios
    qsrand(QTime::currentTime().msec());
    
    // Cargo los datos de los archivos que corresponda

    return a.exec();
}
