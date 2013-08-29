#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <QWidget>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

class Graficador : public QWidget
{
    Q_OBJECT
public:
    Graficador( QWidget *parent = 0 );
    void setearTitulo( QString titulo );
    void agregarCurva( QVector<double> datos, QString nombre );
    void agregarCurva( QVector<double> x, QVector<double> y, QString nombre );

private:
    QwtPlot *myPlot;
    int color;
    void cambiarColor();

};

#endif // GRAFICADOR_H
