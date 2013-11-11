#include "FFDWDH.h"

#include "GenomaVidrio.h"

FFDWDH::FFDWDH()
{
    _planchas.clear();
    _piezas.clear();
    _informacion.clear();
    _alto_plancha = 0.0;
    _ancho_plancha = 0.0;
    _orden_plancha.clear();
    _informacion.clear();

}

Pieza FFDWDH::generarPieza(int pos)
{
    return Pieza(_informacion.value(pos).ancho(),_informacion.value(pos).alto());
}

double FFDWDH::evaluarGen( GenomaVidrio &Gen )
{
    _planchas.clear();
    _piezas.clear();

    //Recorro el gen y cargo las piezas generadas
    QVector<int> gen = Gen.getGenotipo(); // Ordenes de corte
    this->setearTemplates( Gen.getFenotipo() ); // templates para el tamaño del corte generados en el genoma
                                          // para los templates generados por mutacion o cruza

    for (int g = 0 ; g < gen.size() ; g++) {
        //A partir de la informacion del gen genero las piezas y las cargo en el vector
        _piezas.append( generarPieza( gen.at( g ) ) );
    }

    //Cargo la primera plancha
    Plancha Auxiliar( _ancho_plancha, _alto_plancha );
    _planchas.append( Auxiliar );
    regenerarOrden();

    //Recorro todas las piezas
    for (int i = 0 ; i < _piezas.size() ; i++) {

        bool entro_existente = false;

        //Me fijo si mi pieza se puede recortar de una plancha existente
        for( int pos_planchas = 0; pos_planchas<_planchas.size(); pos_planchas++ ) {
            int posicion = _orden_plancha.at( pos_planchas );
            if( _planchas.at(posicion).entraPieza( _piezas.at(i))) {
                hacerCorte(pos_planchas,_piezas.at(i));
                entro_existente = true;
                pos_planchas = _planchas.size() + 1; // Salgo del for de barras
                regenerarOrden();
            }

        }

        //Agrego una nueva plancha de fabrica porque no me entra en ninguna
        if( !entro_existente ) {
            // Agrego una nueva plancha a la lista de utilizadas
            Plancha plancha(_ancho_plancha,_alto_plancha);

            // Lo agergo a las consideradas
            _planchas.append( plancha );

            // genero el corte que no se pudo generar
            hacerCorte(_planchas.size() - 1 ,_piezas.at(i) );

            regenerarOrden();
        }

        regenerarOrden();

    }

    // Calculo la sumatoria de los largos actuales
    double sobrante = 0.0;
    for( int i=0; i<_planchas.size(); i++ ) {
        sobrante += _planchas.at( i ).areaDisponible();
    }

    //if (sobrante < 0 ) {abort();}

    return sobrante;

}

void FFDWDH::regenerarOrden()
{
    // Ordeno los largos
    QMap<double,int> orden;
    for( int i=0; i<_planchas.size(); i++ ) {
        orden.insertMulti( _planchas.at( i ).areaDisponible(), i );
    }
    _orden_plancha.clear();
    foreach( int p, orden.values() ) {
        _orden_plancha.append( p );
    }
}

void FFDWDH::hacerCorte( int pos, Pieza pieza )
{
    //ACA CONSTATAR SI ESTOS SERIAN LOS CASOS
    //FALTARIA EL CASO EN QUE NO ENTRA EN NINGUNA DE LAS PLACAS

    //Caso que tengo dos sobrantes a partir del corte de la pieza
    if((_planchas.at(pos).ancho() - pieza.ancho()) > 0 && (_planchas.at(pos).alto() - pieza.alto()) > 0) {
            //Creo la nueva plancha que me sobre
            Plancha Auxiliar(_planchas.at(pos).ancho() - pieza.ancho(),_planchas.at(pos).alto());
            _planchas.append(Auxiliar);

            //Redimensiono la actual segun lo que me sobra el la altura
            _planchas[pos].setearAlto( _planchas.at(pos).alto() - pieza.alto());
            _planchas[pos].setearAncho( pieza.ancho());
    }
    else
    {
        //Casos que tengo un sobrante despues del corte
        if((_planchas.at(pos).alto() - pieza.alto()) > 0) {
            //Redimensiono la actual segun lo que me sobra el la altura
            _planchas[pos].setearAlto( _planchas.at(pos).alto() - pieza.alto());
            _planchas[pos].setearAncho( pieza.ancho());
        }
        else
        {
            //Caso que la pieza ocupa toda la plancha y no sobra nada
            _planchas.remove(pos);
        }
    }

    regenerarOrden();
}

