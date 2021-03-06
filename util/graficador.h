#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <QWidget>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_scaleitem.h>
#include "funciones_aux.h"

class Graficador : public QWidget
{
    Q_OBJECT
public:
    Graficador( QWidget *parent = 0 );
    void setearTitulo( QString titulo );
    void setearTituloEjeX( QString titulo );
    void setearTituloEjeY( QString titulo );
    void agregarCurva( QVector<double> datos, QString nombre );
    void agregarCurva( QVector<double> x, QVector<double> y, QString nombre );
    void agregarPuntos( QVector<double> x, QVector<double> y, QString nombre );
    void agregarPuntos( matriz m1, QString nombre );
    void agregarPuntosClasificados( matriz entradas, vector salida, double limite_division = 0.0 );
    void agregarPuntosClasificados( matriz entradas, QVector<int> salida, double limite_division = 0.0 );
    void agregarPuntosClasificados( matriz entradas, matriz salida, double limite_division = 0.0 );
    void agregarPuntosClasificados( matriz entradas, QVector<int> salida, QVector<int> codificacion_salida );
    void agregarPuntosClasificados( matriz entradas, vector salida, QVector<int> codificacion_salida );
    void dibujarRecta( int num_recta, vector pesos, QString nombre );
    void setearEjesEnGrafico();
    void setearTamanoFijo();
    void setearPuntos( QVector<QPointF> puntos );
    void setearPuntos( QVector<double>  puntos , QVector<int> escala_tiempo );
    void setearPuntos( QVector<double> puntos, QVector<double> puntos2 );
    void setearPuntos( QVector<int> puntos, QVector<int> puntos2 );
    void setearParaSOM( QString nombre = "SOM" );
    void setearParaTrapezoide();
    void deshabilitarEscalado();
    void agregarTrapezoide( QVector<double> valores, QString nombre );

    void agregarCurva( int pos, QString nombre );
    void setearPuntos( int pos_curva, QVector<double> datos );

private:
    QwtPlot *myPlot;
    QwtLegend *leyenda;
    Qt::GlobalColor color;
    QwtSymbol::Style simbolo;
    void cambiarColor();
    void cambiarSimbolo();
    QHash<int, QwtPlotCurve*> *curvas;
    QwtPlotScaleItem *scaleItemX;
    QwtPlotScaleItem *scaleItemY;

};

#endif // GRAFICADOR_H
