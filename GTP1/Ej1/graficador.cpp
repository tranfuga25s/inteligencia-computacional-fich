#include "graficador.h"

#include <QLayout>
#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_symbol.h>

Graficador::Graficador(QWidget *parent) :
    QWidget(parent)
{
    myPlot = new QwtPlot( this );
    if( this->layout() == 0 ) {
        this->setLayout( new QGridLayout( this ) );
    }
    this->layout()->addWidget( myPlot );
    color = Qt::blue;
    simbolo = QwtSymbol::Diamond;

    leyenda = new QwtLegend( myPlot );
    myPlot->insertLegend( leyenda, QwtPlot::RightLegend );

    this->curvas = new QHash<int,QwtPlotCurve*>();
}

/*!
 * \brief Graficador::setearTitulo
 * \param titulo
 */
void Graficador::setearTitulo(QString titulo)
{
    myPlot->setTitle( titulo );
}

void Graficador::setearTituloEjeX( QString titulo )
{
    myPlot->setAxisTitle( QwtPlot::xBottom, titulo );
}

void Graficador::setearTituloEjeY( QString titulo )
{
    myPlot->setAxisTitle( QwtPlot::yLeft, titulo );
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
    QPen p = curve->pen();
    p.setColor( color );
    curve->setPen( p );
    cambiarColor();

    curve->attach( myPlot );

    // Refresco el grafico
    myPlot->replot();
}

void Graficador::agregarPuntos( QVector<double> x, QVector<double> y, QString nombre ){

    QwtPlotCurve *curve = new QwtPlotCurve( nombre );

    curve->setSamples( x, y );
    curve->setRenderHint(QwtPlotItem::RenderAntialiased);
    curve->setLegendAttribute(QwtPlotCurve::LegendShowLine , true);
    cambiarColor();
    cambiarSimbolo();
    curve->setStyle( QwtPlotCurve::Dots );
    curve->setSymbol( new QwtSymbol( (QwtSymbol::Style)this->simbolo,
                                     QBrush( (Qt::GlobalColor)this->color ),
                                     QPen( Qt::NoPen ),
                                     QSize( 8, 8 ) ) );

    curve->attach( myPlot );

    // Refresco el grafico
     myPlot->replot();
}

void Graficador::agregarPuntos( matriz m1, QString nombre ) {

    vector x, y;
    for(int j=0; j<m1.size(); j++ ) {
        x.append( m1.at(j).at(0) );
        y.append( m1.at(j).at(1) );
    }
    agregarPuntos( x, y, nombre );
}

void Graficador::dibujarRecta( int num_recta, vector pesos, QString nombre ) {

    if( curvas->contains( num_recta ) ) {
        QwtPlotCurve *curva = curvas[num_recta];
    } else {
        QwtPlotCurve *curva = new QwtPlotCurve( nombre );
        curvas->insert( num_curva, curva );
        curva->attach( myPlot );
    }

    double min = myPlot->getMin();
    double max = myPlot->getMax();

    y1 = ( pesos.at( 0 ) / pesos.at( 2 ) ) - ( pesos.at( 1 ) / pesos.at(2) ) * min;
    y2 = ( pesos.at( 0 ) / pesos.at( 2 ) ) - ( pesos.at( 1 ) / pesos.at(2) ) * max;
    vector x;
    x.append( min ).append( max );
    vector y;
    y.append( y1 ).append( y2 );
    curva->setSamples( x, y );
    myPlot->replot();
}

void Graficador::cambiarColor()
{
    switch( this->color ) {
    case Qt::red:         { this->color = Qt::green; break;      }
    case Qt::green:       { this->color = Qt::darkRed; break;     }
    case Qt::darkRed:     { this->color = Qt::darkGreen; break;   }
    case Qt::darkGreen:   { this->color = Qt::blue;  break;       }
    case Qt::blue:        { this->color = Qt::darkBlue;  break;   }
    case Qt::darkBlue:    { this->color = Qt::cyan;  break;       }
    case Qt::cyan:        { this->color = Qt::darkCyan;  break;   }
    case Qt::darkCyan:    { this->color = Qt::magenta;  break;    }
    case Qt::magenta:     { this->color = Qt::darkMagenta; break; }
    case Qt::darkMagenta: { this->color = Qt::yellow;  break;     }
    case Qt::yellow:      { this->color = Qt::darkYellow; break;  }
    case Qt::darkYellow:  { this->color = Qt::gray; break;        }
    case Qt::gray:        { this->color = Qt::darkGray;  break;   }
    case Qt::darkGray:    { this->color = Qt::lightGray;  break;  }
    case Qt::lightGray:   { this->color = Qt::red;  break;        }
    }

}

void Graficador::cambiarSimbolo() {
    switch( this->simbolo ) {
        case QwtSymbol::Cross:   { this->simbolo = QwtSymbol::Diamond;  break;   }
        case QwtSymbol::Diamond: { this->simbolo = QwtSymbol::DTriangle;  break; }
        case QwtSymbol::DTriangle: { this->simbolo = QwtSymbol::Cross; break; }
    }
}
