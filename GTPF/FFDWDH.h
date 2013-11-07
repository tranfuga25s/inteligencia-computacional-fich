#ifndef FFDWDH_H
#define FFDWDH_H

#include <QVector>
#include <QMap>
#include "Plancha.h"

class FFDWDH {
public:
    FFDWDH();
    Pieza generarPieza(int pos);
    double optimizar(QVector<int> Gen);
    void setearAltoPlancha(double alto) {_alto_plancha = alto;}
    void setearAnchoPlancha(double ancho) {_ancho_plancha = ancho;}
    void setearInformacion( QMap< int, QPair<double,double> > informacion) {_informacion = informacion;}
    void regenerarOrden();
    void hacerCorte(int pos,Pieza pieza);

private:
    QVector<Plancha> _planchas;
    QVector<Pieza> _piezas;
    QMap<int, QPair<double,double > > _informacion;
    double _alto_plancha,_ancho_plancha;
    QVector<int> _orden_plancha;
};

FFDWDH::FFDWDH()
{
    _planchas.clear();
    _piezas.clear();
    _informacion.clear();
    _alto_plancha = 0.0;
    _ancho_plancha = 0.0;
    _orden_plancha.clear();
}

Pieza FFDWDH::generarPieza(int pos)
{
    QPair<double,double> posiciones = _informacion.value(pos);
    return Pieza(posiciones.first,posiciones.second);
}

double FFDWDH::optimizar(QVector<int> Gen)
{
    //Recorro el gen y cargo las piezas generadas
    for (int g = 0 ; g < Gen.size() ; g++) {
        //A partir de la informacion del gen genero las piezas y las cargo en el vector
        _piezas.append(generarPieza(Gen.at(g)));
    }

    //Cargo la primera plancha
    Plancha Auxiliar;
    Auxiliar.setearAncho(_ancho_plancha);
    Auxiliar.setearAlto(_alto_plancha);
    _planchas.append(Auxiliar);
    regenerarOrden();

    for (int i = 0 ; i < _piezas.size() ; i++) {

        bool entro_existente = false;

        for( int pos_planchas = 0; pos_planchas<_planchas.size(); pos_planchas++ ) {

            if( _planchas.at( _orden_plancha.at( pos_planchas ) ).entraPieza( _piezas[i].ancho() ,_piezas[i].alto() )) {
                hacerCorte(pos_planchas,_piezas.at(i));
                entro_existente = true;
                pos_planchas = _planchas.size() + 1; // Salgo del for de barras
                regenerarOrden();
            }

        }

        if( !entro_existente ) {
            // Agrego una nueva barra a la lista de utilizadas
            Plancha plancha(_ancho_plancha,_alto_plancha);

            // Lo agergo a las consideradas
            _planchas.append( plancha );

            // genero el corte que no se pudo generar
            plancha.hacerCorte(_planchas.size() - 1 ,_piezas.at(i) );

            regenerarOrden();
        }

    }

    // Calculo la sumatoria de los largos actuales
    double sobrante = 0.0;
    for( int i=0; i<_planchas.size(); i++ ) {
        sobrante += _planchas.at( i ).areaDisponible();
    }

    return sobrante;

}

void FFDWDH::regenerarOrden()
{
    // Ordeno los largos
    QMap<double,int> orden;
    for( int i=0; i<_planchas.size(); i++ ) {
        orden.insert( _planchas.at( i ).areaDisponible(), i );
    }
    _orden_plancha.clear();
    foreach( int p, orden.values() ) {
        _orden_plancha.append( p );
    }
}

void FFDWDH::hacerCorte(int pos, Pieza pieza)
{
    //Creo la nueva plancha que me sobre
    Plancha Auxiliar(_planchas.at(pos).ancho() - pieza.ancho(),_planchas.at(pos).alto());
    _planchas.append(Auxiliar);
    //Redimensiono la actual segun lo que me sobra el la altura
    _planchas[pos].setearAlto( _planchas.at(pos).alto() - pieza.alto());
    _planchas[pos].setearAncho( _planchas.at(pos).ancho() - pieza.ancho());

    regenerarOrden();
}

#endif // FFDWDH_H
