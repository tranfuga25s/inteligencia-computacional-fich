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


#endif // BARRAALUMINIO_H
