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

    this->curvas = new QHash<int, QwtPlotCurve*>();
}

/*!
 * \brief Graficador::setearTitulo
 * \param titulo
 */
void Graficador::setearTitulo(QString titulo)
{
    myPlot->setTitle( titulo );
    this->setWindowTitle( titulo );
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
 * \brief Graficador::agregarPuntosClasificados
 * Clasifica todas las entradas en 2 grupos ( -1 y +1 ) y las grafica
 * \param entradas Matriz de entradas
 * \param salidas Vector de salidas
 */
void Graficador::agregarPuntosClasificados( matriz entradas, vector salida, double limite_division )
{
    matriz m1,m2;
    for( int i=0; i<entradas.size(); i++ ) {
        if( salida.at( i ) <= limite_division ) {
            m1.append( entradas.at( i ) );
        } else {
            m2.append( entradas.at( i ) );
        }
    }
    if( limite_division == 0.0 ) {
        agregarPuntos( m1, "Entradas -1" );
        agregarPuntos( m2, "Entradas +1" );
    } else {
        if( m1.size() > 0 )
            agregarPuntos( m1, QString( "Entradas %1" ).arg( limite_division-limite_division ) );

        if( m2.size() > 0 )
            agregarPuntos( m2, QString( "Entradas %1" ).arg( limite_division+limite_division ) );

    }
}

/*!
 * \brief Graficador::agregarPuntosClasificados
 * Clasifica todas las entradas en 2 grupos ( -1 y +1 ) y las grafica
 * \param entradas Matriz de entradas
 * \param salidas Vector de salidas
 */
void Graficador::agregarPuntosClasificados( matriz entradas, matriz salida, double limite_division )
{
    matriz m1,m2;
    for( int i=0; i<entradas.size(); i++ ) {
        if( salida.at( i ).at( 0 ) <= limite_division ) {
            m1.append( entradas.at( i ) );
        } else {
            m2.append( entradas.at( i ) );
        }
    }
    if( limite_division == 0.0 ) {
        agregarPuntos( m1, "Entradas -1" );
        agregarPuntos( m2, "Entradas +1" );
    } else {
        if( m1.size() > 0 )
            agregarPuntos( m1, QString( "Entradas %1" ).arg( limite_division-limite_division ) );

        if( m2.size() > 0 )
            agregarPuntos( m2, QString( "Entradas %1" ).arg( limite_division+limite_division ) );
    }
}

/*!
 * \brief Graficador::agregarPuntosClasificados
 * Clasifica todas las entradas en 2 grupos ( -1 y +1 ) y las grafica
 * \param entradas Matriz de entradas
 * \param salidas Vector de salidas
 */
void Graficador::agregarPuntosClasificados( matriz entradas, QVector<int> salida, double limite_division )
{
    matriz m1,m2;
    for( int i=0; i<entradas.size(); i++ ) {
        if( salida.at( i ) <= limite_division ) {
            m1.append( entradas.at( i ) );
        } else {
            m2.append( entradas.at( i ) );
        }
    }
    if( limite_division == 0.0 ) {
        agregarPuntos( m1, "Entradas -1" );
        agregarPuntos( m2, "Entradas +1" );
    } else {
        if( m1.size() > 0 )
            agregarPuntos( m1, QString( "Entradas %1" ).arg( limite_division-limite_division ) );

        if( m2.size() > 0 )
            agregarPuntos( m2, QString( "Entradas %1" ).arg( limite_division+limite_division ) );
    }
}

/*!
 * \brief Graficador::agregarPuntosClasificados
 * Clasifica todas las entradas en 2 grupos ( -1 y +1 ) y las grafica
 * \param entradas Matriz de entradas
 * \param salidas Vector de salidas
 */
void Graficador::agregarPuntosClasificados( matriz entradas, QVector<int> salida, QVector<int> codificacion_salida )
{
    QVector<matriz> superentrada( codificacion_salida.size() );
    for( int i=0; i<entradas.size(); i++ ) {
        superentrada[salida.at(i)].append( entradas.at(i) );
    }
    for( int j=0; j<codificacion_salida.size(); j++ ) {
        agregarPuntos( superentrada.at( j ), QString( "Clase %1" ).arg( codificacion_salida.at(j) ) );
    }
}

/*!
 * \brief Graficador::agregarPuntosClasificados
 * Clasifica todas las entradas en 2 grupos ( -1 y +1 ) y las grafica
 * \param entradas Matriz de entradas
 * \param salidas Vector de salidas
 */
void Graficador::agregarPuntosClasificados( matriz entradas, vector salida, QVector<int> codificacion_salida )
{
    QVector<matriz> superentrada( codificacion_salida.size() );
    for( int i=0; i<entradas.size(); i++ ) {
        superentrada[salida.at(i)].append( entradas.at(i) );
    }
    for( int j=0; j<codificacion_salida.size(); j++ ) {
        if( superentrada.at( j ).size() > 0 ) {
            agregarPuntos( superentrada.at( j ), QString( "Clase %1" ).arg( codificacion_salida.at(j) ) );
        }
    }
}

/*!
 * \brief Graficador::dibujarRecta
 * \param num_recta Numero de recta a redibujar. Si es cero dibuja una nueva recta.
 * \param pesos
 * \param nombre
 */
void Graficador::dibujarRecta( int num_recta, vector pesos, QString nombre ) {

    QwtPlotCurve *curva = 0;
    if( curvas->contains( num_recta ) && num_recta != 0 ) {
        curva = curvas->operator []( num_recta ); /// ??? WTF ???
    } else {
        curva = new QwtPlotCurve( nombre );
        curvas->insert( num_recta, curva );
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
    curva->setRenderHint( QwtPlotItem::RenderAntialiased );
    curva->setLegendAttribute(QwtPlotCurve::LegendShowLine , true);
    cambiarColor();
    curva->setPen( QPen( color ) );

    curva->attach( myPlot );
        //qDebug() << x << ", "<< y << " Recta dibujada";
    myPlot->replot();
}

/*!
 * \brief Graficador::setearEjesEnGrafico
 * Coloca los ejes xbottom y yleft en el medio del grafico
 */
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

/*!
 * \brief Graficador::setearTamanoFijo
 * No permite que los ejes sean redimensionados al ingresar una nueva curva
 */
void Graficador::setearTamanoFijo()
{
    myPlot->setAxisAutoScale( QwtPlot::xBottom, false );
    myPlot->setAxisAutoScale( QwtPlot::yLeft, false );
}

void Graficador::setearPuntos( QVector<QPointF> puntos )
{
    // Busco la curva
    QwtPlotCurve *curva = curvas->value( 0 );
    if( curva != 0 ) {
        curva->setSamples( puntos );
        myPlot->replot();
    } else {
        abort();
    }
}

void Graficador::setearPuntos( QVector<double> puntos, QVector<int> escala_tiempo )
{
    QVector<QPointF> datos;
    for( int i=0; i<puntos.size(); i++ ) {
        datos.append( QPointF( escala_tiempo.at(i), puntos.at(i) ) );
    }
    this->setearPuntos( datos );
}

void Graficador::setearParaSOM( QString nombre )
{
    if( curvas->size() == 0 ) {
        QwtPlotCurve *curva = new QwtPlotCurve( nombre );
        curvas->insert( 0, curva );
        curva->setRenderHint( QwtPlotItem::RenderAntialiased );
        curva->setLegendAttribute( QwtPlotCurve::LegendShowLine , true );
        cambiarColor();
        curva->setPen( QPen( color ) );
        curva->setSymbol( new QwtSymbol( QwtSymbol::Hexagon,
                                         QBrush( (Qt::GlobalColor)this->color ),
                                         QPen( Qt::NoPen ),
                                         QSize( 8, 8 ) ) );
        curva->attach( myPlot );
        setearEjesEnGrafico();

    }

}

void Graficador::deshabilitarEscalado() {
    myPlot->setAxisAutoScale( QwtPlot::xBottom, false );
    myPlot->setAxisAutoScale( QwtPlot::yLeft, false );
    myPlot->setAxisScale( QwtPlot::xBottom, -1.1, 1.1 );
    myPlot->setAxisScale( QwtPlot::yLeft  , -1.1, 1.1 );
}

void Graficador::cambiarColor()
{
    switch( this->color ) {
    case Qt::red:         { this->color = Qt::green; break;       }
    case Qt::green:       { this->color = Qt::darkRed; break;     }
    case Qt::darkRed:     { this->color = Qt::darkGreen; break;   }
    case Qt::darkGreen:   { this->color = Qt::darkBlue;  break;   }
    case Qt::blue:        { this->color = Qt::red;  break;        }
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
        case QwtSymbol::DTriangle: { this->simbolo = QwtSymbol::Triangle;   break; }
        case QwtSymbol::Triangle:  { this->simbolo = QwtSymbol::UTriangle;  break; }
        case QwtSymbol::UTriangle: { this->simbolo = QwtSymbol::LTriangle;  break; }
        case QwtSymbol::LTriangle: { this->simbolo = QwtSymbol::RTriangle;  break; }
        case QwtSymbol::RTriangle: { this->simbolo = QwtSymbol::XCross;     break; }
        case QwtSymbol::XCross:    { this->simbolo = QwtSymbol::HLine;      break; }
        case QwtSymbol::HLine:     { this->simbolo = QwtSymbol::Ellipse;    break; }
        case QwtSymbol::Ellipse:   { this->simbolo = QwtSymbol::VLine;      break; }
        case QwtSymbol::VLine:     { this->simbolo = QwtSymbol::Star1;      break; }
        case QwtSymbol::Star1:     { this->simbolo = QwtSymbol::Star2;      break; }
        case QwtSymbol::Star2:     { this->simbolo = QwtSymbol::Hexagon;    break; }
        case QwtSymbol::Hexagon:   { this->simbolo = QwtSymbol::Cross;      break; }
        default:                   { this->simbolo = QwtSymbol::Diamond;    break; }
    }
}
