#ifndef BARRAALUMINIO_H
#define BARRAALUMINIO_H

class BarraAluminio {

public:
    BarraAluminio();
    BarraAluminio(const BarraAluminio &b );
    BarraAluminio(BarraAluminio &b);

    void setearLargo( double largo ) { _largo = largo; }
    double largoActual() const { return _largo; }
    bool acepta( double largo ) const;
    void hacerCorte( double largo );

private:
    int _largo;

};

bool BarraAluminio::acepta( double largo ) const {
    if( _largo < largo ) {
        return false;
    } else if( _largo - largo > 0 ) {
        return true;
    }
    return false;
}

void BarraAluminio::hacerCorte( double largo ) {
    _largo -= largo;
}

BarraAluminio::BarraAluminio(const BarraAluminio &b)
{
    this->_largo = b.largoActual();
}

BarraAluminio::BarraAluminio(BarraAluminio &b)
{
    this->_largo = b.largoActual();
}

#endif // BARRAALUMINIO_H
