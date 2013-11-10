#ifndef FFDWDH_H
#define FFDWDH_H

#include <QVector>
#include <QMap>
#include "TemplatePiezas.h"
#include "Plancha.h"
#include "poblacion.h"
#include "GenomaVidrio.h"

class FFDWDH {
public:
    FFDWDH();
    Pieza generarPieza(int pos);
    double evaluarGen( GenomaVidrio &Gen );
    void setearAltoPlancha(double alto) {_alto_plancha = alto;}
    void setearAnchoPlancha(double ancho) {_ancho_plancha = ancho;}
    void setearTemplates( QVector<TemplatePiezas> &informacion) { _informacion = informacion; }
    void regenerarOrden();
    void hacerCorte(int pos,Pieza pieza);



private:
    QVector<Plancha> _planchas;
    QVector<Pieza> _piezas;
    QVector<TemplatePiezas>  _informacion;
    double _alto_plancha,_ancho_plancha;
    QVector<int> _orden_plancha;


};

#endif // FFDWDH_H
