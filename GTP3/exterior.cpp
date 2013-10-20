#include "exterior.h"

Exterior::Exterior(QObject *parent) :
    QObject(parent)
{
    _ultimo_cambio = 0;
    _cant_seg = 1;
    _max = 23.0;
    _min = 19.0;
    _ultima_temp = _min;
}

double Exterior::getTemperatura( int segundo )
{
    if( segundo > _ultimo_cambio + _cant_seg ) {
        _ultimo_cambio = segundo;
        if( _historico.at( _historico.size() - 1 ) == _max ) {
            _ultima_temp = _min;
        } else {
            _ultima_temp = _max;
        }
    }
    _historico.append( _ultima_temp );
    return _ultima_temp;
}
