#include "redneuronalradial.h"

RedNeuronalRadial::RedNeuronalRadial(int cantidad_neuronas_radiales, int cantidad_neuronas_normales, int cantidad_entradas , int cant_clases)
{
    if( cantidad_neuronas_radiales != 0 ) {
        _capaRadial = new CapaNeuronalRadial( cantidad_neuronas_radiales, cantidad_entradas );
    }
    if( cantidad_neuronas_normales != 0 ) {
        _capaNeuronas = new CapaNeuronal( cantidad_neuronas_normales, cantidad_neuronas_radiales );
    }
    _datos_originales = new QVector<QPointF>();
    _clases_originales = new QVector<int>();
    _cantidad_clases = cant_clases;
}

void RedNeuronalRadial::setearTasaAprendizaje( double tasa )
{
    _capaNeuronas->setearTasaAprendizaje( tasa );
    _capaRadial->setearTasaAprendizaje( tasa );
}

void RedNeuronalRadial::setearMomento( double momento )
{
    _capaNeuronas->setearMomento( momento );
    _capaRadial->setearMomento( momento );
}

/*!
 * \brief RedNeuronalRadial::setearDatosOriginales
 * Guarda en el vector interno los datos para generar la clasificacion de los centroides
 * \param entradas Puntos originales
 * \param clases Identificador de la case segun el patron de el otro parametro.
 */
void RedNeuronalRadial::setearDatosOriginales( QVector<QPointF> *entradas, QVector<int> *clases )
{
   _datos_originales = entradas;
   _clases_originales = clases;
}

/*!
 * \brief RedNeuronalRadial::buscarCentroides
 */
void RedNeuronalRadial::buscarCentroides()
{
    _capaRadial->setearCantidadClases( _cantidad_clases );
    _capaRadial->buscarCentroides( *_datos_originales );
}

/*!
 * \brief RedNeuronalRadial::entrenarCapaNeuronalComun
 * \param entrada
 * \param clase
 */
void RedNeuronalRadial::entrenarCapaNeuronalComun( QVecto<double> entrada, int clase )
{
    QVector<double> temporal = _capaRadial->getSalidas( entrada );
    _capaNeuronas->entrenar( temporal, clase );
}

/*!
 * \brief RedNeuronalRadial::probarPatron
 * \param patron
 * \return
 */
int RedNeuronalRadial::probarPatron( QVector<double> patron )
{
    return _capaNeuronas->evaluarCodificado( _capaRadial->getSalidas( patron ) );
}
