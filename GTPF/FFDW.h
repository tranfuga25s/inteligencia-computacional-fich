#ifndef FFDW_H
#define FFDW_H

#include "BarraAluminio.h"
#include "templatealuminio.h"

#include <QVector>
#include <QMap>

/*
  Optimizador para funciones de corte de aluminio
 */
class FFDW {

public:
    FFDW();

    double optimizar( QVector<int> gen );

    void setearTemplates( QVector<TemplateAluminio> templates ) { _templates = templates; }

    void setearLargoBarraOriginal( double largo ) { _largo_barra_original = largo; }
    double largoBarraOriginal() const { return _largo_barra_original; }

private:
    QVector<BarraAluminio> _barras;
    QVector<TemplateAluminio> _templates;

    QVector<int> _orden_barras;

    double _largo_barra_original;

    void regenerarOrden();

};


FFDW::FFDW()
{
    _largo_barra_original = 0.0;
    _barras.clear();
    _orden_barras.clear();
}

double FFDW::optimizar( QVector<int> gen )
{
    // Inicializo con al primera barra de aluminio
    BarraAluminio primera;
    primera.setearLargo( _largo_barra_original );
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

            // Lo agergo a las consideradas
            _barras.append( barra );

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
        orden.insert( _barras.at( i ).largoActual(), i );
    }
    _orden_barras.clear();
    foreach( int p, orden.values() ) {
        _orden_barras.append( p );
    }
}

#endif // FFDW_H
