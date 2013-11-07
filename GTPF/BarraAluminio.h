#ifndef BARRAALUMINIO_H
#define BARRAALUMINIO_H

class BarraAluminio {

    BarraAluminio();

    void setearLargo( double largo ) { _largo = largo; }
    double largoActual() { return largo; }
    bool acepta( double largo );
    void hacerCorte( double largo );

private:
    int _largo;
};

/*!
 *
 */
bool BarraAluminio::hacerCorte( double largo ) {
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

#endif // BARRAALUMINIO_H
