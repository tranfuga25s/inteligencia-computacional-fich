#ifndef REDNEURONAL_H
#define REDNEURONAL_H

#include <QObject>
#include <capaneuronal.h>
#include "funciones_aux.h"

class RedNeuronal
{
public:
    RedNeuronal( int cant_capas, QVector<int> cantidad_neuronas, int cant_entradas);
    RedNeuronal();//Constructor Vacio
    int cantidadCapas() { return capas.size(); }

    void setearTasaAprendizaje( double tasa );
    //void setearMomento(double momento);
    //double getMomento() { return capas[0]->getNeuronas()[0]->tasaMomento(); }

    RedNeuronal& operator = (RedNeuronal const &red) {
        capas = red.capas;
        codif_salidas = red.codif_salidas;
        return *this;
    }

    void inicializarPesos();
    int cantidadPesos();
    void setearPesos(QVector<double> pesos);

    vector forwardPass( vector entradas );//forward pass

    void setearCodificacion( QVector<int> codif );
    QVector<int> mostrarCodificacionSalida() { return codif_salidas; }

    int mapeadorSalidas( vector salidas );
    vector mapeadorInverso(double valor );

    void mostrarPesos( QTextStream &pesos );
    
private:
    QVector<CapaNeuronal *> capas;
    QVector<int> codif_salidas;
    
};

#endif // REDNEURONAL_H
