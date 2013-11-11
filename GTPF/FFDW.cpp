#include "FFDW.h"

#include "GenomaAluminio.h"

FFDW::FFDW()
{
    _largo_barra_original = 0.0;
    _barras.clear();
    _orden_barras.clear();
}

double FFDW::evaluarGen( const GenomaAluminio &Gen )
{
    //Recorro el gen y cargo las piezas generadas
    QVector<int> gen = Gen.getGenotipo(); // Ordenes de corte
    setearTemplates( Gen.getFenotipo() ); // templates para el tamaño del corte generados en el genoma
                                          // para los templates generados por mutacion o cruza

    // Inicializo con al primera barra de aluminio
    _barras.clear();
    BarraAluminio primera;
    primera.setearLargo( _largo_barra_original );
    _barras.append( primera );
    regenerarOrden();

    // Recorro todos los elementos del gen
    for( int pos_gen = 0; pos_gen < gen.size(); pos_gen++ ) {

        // Busco el largo del elemento a cortar
        double longitud = _templates.at( gen.at( pos_gen ) ).largo();

        bool entro_existente = false;

        for( int pos_barras = 0; pos_barras<_barras.size(); pos_barras++ ) {
            int pos_barra = _orden_barras.at( pos_barras );
            if( _barras.at( pos_barra ).acepta( longitud ) ) {

                _barras[pos_barra].hacerCorte( longitud );

                //Que pasa si me da 0 la resta, no habria que eliminarla para que no queden invalidas?
                if((_barras[pos_barra].largoActual() - longitud) == 0) {_barras.remove(pos_barra);}

                entro_existente = true;
                pos_barras = _barras.size() + 1; // Salgo del for de barras
                regenerarOrden();
            }

        }

        if( !entro_existente ) {
            // Agrego una nueva barra a la lista de utilizadas
            BarraAluminio barra;
            barra.setearLargo( _largo_barra_original );

            // genero el corte que no se pudo generar
            barra.hacerCorte( longitud );

            //Que pasa si me da 0 la resta, no habria que eliminarla para que no queden invalidas?
            if((barra.largoActual() - longitud) != 0)
            {
                // Lo agergo a las consideradas
                _barras.append( barra );
            }

            regenerarOrden();
        }


    } // Fin for gen

    // Calculo la sumatoria de los largos actuales
    double sobrante = 0.0;
    for( int i=0; i<_barras.size(); i++ ) {
        sobrante += _barras.at( i ).largoActual();
    }
    return sobrante;
}

void FFDW::regenerarOrden()
{
    // Ordeno los largos
    QMap<double,int> orden;
    for( int i=0; i<_barras.size(); i++ ) {
        orden.insertMulti( _barras.at( i ).largoActual(), i );
    }
    _orden_barras.clear();
    foreach( int p, orden.values() ) {
        _orden_barras.append( p );
    }
}
