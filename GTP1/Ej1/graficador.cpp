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
    QVector<double> nuevo;
    for(int i=0; i<datos.size(); i++ ) {
        nuevo.append( i );
    }

    agregarCurva( nuevo, datos, nombre );
}

void Graficador::agregarCurva( QVector<double> x, QVector<double> y, QString nombre )
{
    QwtPlotCurve *curve = new QwtPlotCurve( nombre );

    curve->setSamples( x, y );
    curve->setLegendAttribute( QwtPlotCurve::LegendShowLine );
    QBrush b = curve->brush();
    b.setColor( color );
    curve->setBrush( b );
    cambiarColor();

    curve->attach( myPlot );
    myPlot->setTitle( nombre );

    // Refresco el grafico
    myPlot->replot();
}

void Graficador::cambiarColor()
{
    switch( this->color ) {
    case Qt::red:         { this->color = Qt::green;       }
    case Qt::green:       { this->color = Qt::darkRed;     }
    case Qt::darkRed:     { this->color = Qt::darkGreen;   }
    case Qt::darkGreen:   { this->color = Qt::blue;        }
    case Qt::blue:        { this->color = Qt::darkBlue;    }
    case Qt::darkBlue:    { this->color = Qt::cyan;        }
    case Qt::cyan:        { this->color = Qt::darkCyan;    }
    case Qt::darkCyan:    { this->color = Qt::magenta;     }
    case Qt::magenta:     { this->color = Qt::darkMagenta; }
    case Qt::darkMagenta: { this->color = Qt::yellow;      }
    case Qt::yellow:      { this->color = Qt::darkYellow;  }
    case Qt::darkYellow:  { this->color = Qt::gray;        }
    case Qt::gray:        { this->color = Qt::darkGray;    }
    case Qt::darkGray:    { this->color = Qt::lightGray;   }
    case Qt::lightGray:   { this->color = Qt::red;         }
    }

}


