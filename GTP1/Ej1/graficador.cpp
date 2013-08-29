#include "graficador.h"

#include <QLayout>

Graficador::Graficador(QWidget *parent) :
    QWidget(parent)
{
    myPlot = new QwtPlot( this );
    if( this->layout() == 0 ) {
        this->setLayout( new QGridLayout( this ) );
    }
    this->layout()->addWidget( myPlot );
    color = Qt::blue;
}

/*!
 * \brief Graficador::setearTitulo
 * \param titulo
 */
void Graficador::setearTitulo(QString titulo)
{
    myPlot->setTitle( titulo );
}

void Graficador::agregarCurva( QVector<double> datos, QString nombre )
{
    QwtPlotCurve *curve = new QwtPlotCurve( nombre );

    QVector<double> nuevo;
    for(int i=0; i<datos.size(); i++ ) {
        nuevo.append( i );
    }

    curve->setSamples( nuevo, datos );
    curve->setLegendAttribute( QwtPlotCurve::LegendShowLine );
    QBrush b = curve->brush();
    b.setColor( color );
    curve->setBrush( b );
    cambiarColor();

    curve->attach( myPlot );

    // Refresco el grafico
    myPlot->replot();
}

void Graficador::agregarCurva( QVector<double> x, QVector<double> y, QString nombre )
{
    QwtPlotCurve *curve1 = new QwtPlotCurve( nombre );

    curve1->setSamples( x, y );
    curve->setLegendAttribute( QwtPlotCurve::LegendShowLine );
    QBrush b = curve->brush();
    b.setColor( color );
    curve->setBrush( b );
    cambiarColor();

    curve1->attach( myPlot );

    // Refresco el grafico
    myPlot->replot();
}

void Graficador::cambiarColor()
{
    switch( this->color ) {
    case Qt::red:         { color = Qt::green;       }
    case Qt::green:       { color = Qt::darkRed;     }
    case Qt::darkRed:     { color = Qt::darkGreen;   }
    case Qt::darkGreen:   { color = Qt::blue;        }
    case Qt::blue:        { color = Qt::darkBlue;    }
    case Qt::darkBlue:    { color = Qt::cyan;        }
    case Qt::cyan:        { color = Qt::darkCyan;    }
    case Qt::darkCyan:    { color = Qt::magenta;     }
    case Qt::magenta:     { color = Qt::darkMagenta; }
    case Qt::darkMagenta: { color = Qt::yellow;      }
    case Qt::yellow:      { color = Qt::darkYellow;  }
    case Qt::darkYellow:  { color = Qt::gray;        }
    case Qt::gray:        { color = Qt::darkGray;    }
    case Qt::darkGray:    { color = Qt::lightGray;   }
    case Qt::lightGray:   { color = Qt::red;         }
    }

}


