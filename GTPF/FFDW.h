#ifndef FFDW_H
#define FFDW_H

#include "BarraAluminio.h"
#include "templatealuminio.h"
#include "GenomaAluminio.h"

#include <QVector>
#include <QMap>

/*
  Optimizador para funciones de corte de aluminio
 */
class FFDW {

public:
    FFDW();

    double optimizar(GenomaAluminio &Gen );

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




#endif // FFDW_H
