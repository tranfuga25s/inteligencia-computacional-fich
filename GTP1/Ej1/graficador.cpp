#include "graficador.h"

#include <QLayout>
#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_symbol.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_scaleitem.h>
#include <qwt_scale_widget.h>

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

    this->curvas = new QVector<QwtPlotCurve*>();
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

/*!
 * \brief Graficador::dibujarRecta
 * \param num_recta
 * \param pesos
 * \param nombre
 */
void Graficador::dibujarRecta( int num_recta, vector pesos, QString nombre ) {

    QwtPlotCurve *curva;
    if( curvas->size() >= num_recta ) {
        curva = curvas->value( num_recta );
    } else {
        curva = new QwtPlotCurve( nombre );
        curvas->append( curva );
        curva->attach( myPlot );
    }


    double min = myPlot->axisScaleDiv( QwtPlot::xBottom )->lowerBound();

    double max = myPlot->axisScaleDiv( QwtPlot::xBottom )->upperBound();

    double y1 = ( pesos.value( 0 ) / pesos.at( 2 ) ) - ( ( pesos.at( 1 ) / pesos.at(2) ) * min );
    double y2 = ( pesos.at( 0 ) / pesos.at( 2 ) ) - ( ( pesos.at( 1 ) / pesos.at(2) ) * max );
    vector x;
    x.append( min );
    x.append( max );
    vector y;
    y.append( y1 );
    y.append( y2 );
    curva->setSamples( x, y );

    curva->attach( myPlot );
    qDebug() << x << ", "<< y << " Recta dibujada";
    myPlot->replot();
}

void Graficador::setearEjesEnGrafico()
{
    scaleItemX = new QwtPlotScaleItem( QwtScaleDraw::RightScale, 0.0 );
    scaleItemX->setFont( myPlot->axisWidget( QwtPlot::yLeft )->font() );
    scaleItemX->attach( myPlot );

    myPlot->enableAxis( QwtPlot::yLeft, false );

    scaleItemY = new QwtPlotScaleItem( QwtScaleDraw::BottomScale, 0.0 );
    scaleItemY->setFont( myPlot->axisWidget( QwtPlot::xBottom )->font() );
    scaleItemY->attach( myPlot );

    myPlot->enableAxis( QwtPlot::xBottom, false );
}

void Graficador::cambiarColor()
{
    switch( this->color ) {
    case Qt::red:         { this->color = Qt::green; break;       }
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
    case Qt::lightGray:   { this->color = Qt::black;  break;      }
    case Qt::black:       { this->color = Qt::white;  break;      }
    case Qt::white:       { this->color = Qt::red;  break;        }
    default:              { this->color = Qt::red;  break;        }
    }

}

void Graficador::cambiarSimbolo() {
    switch( this->simbolo ) {
        case QwtSymbol::Cross:     { this->simbolo = QwtSymbol::Diamond;    break; }
        case QwtSymbol::Diamond:   { this->simbolo = QwtSymbol::DTriangle;  break; }
        case QwtSymbol::DTriangle: { this->simbolo = QwtSymbol::Cross;      break; }
        case QwtSymbol::Triangle:  { this->simbolo = QwtSymbol::UTriangle;  break; }
        case QwtSymbol::UTriangle: { this->simbolo = QwtSymbol::LTriangle;  break; }
        case QwtSymbol::LTriangle: { this->simbolo = QwtSymbol::RTriangle;  break; }
        case QwtSymbol::RTriangle: { this->simbolo = QwtSymbol::XCross;     break; }
        case QwtSymbol::XCross:    { this->simbolo = QwtSymbol::HLine;      break; }
        case QwtSymbol::HLine:     { this->simbolo = QwtSymbol::Ellipse;    break; }
        case QwtSymbol::Rect:      { this->simbolo = QwtSymbol::VLine;      break; }
        case QwtSymbol::VLine:     { this->simbolo = QwtSymbol::Star1;      break; }
        case QwtSymbol::Star1:     { this->simbolo = QwtSymbol::Star2;      break; }
        case QwtSymbol::Star2:     { this->simbolo = QwtSymbol::Hexagon;    break; }
        case QwtSymbol::Hexagon:   { this->simbolo = QwtSymbol::Cross;      break; }
        default:                   { this->simbolo = QwtSymbol::Diamond;    break; }
    }
}
