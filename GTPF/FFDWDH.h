#ifndef FFDWDH_H
#define FFDWDH_H

#include <QVector>

//!
//! \brief The ColumnaPlancha class
//! Clase que modela la columna de corte
//!

class ColumnaPlancha {
public:
    ColumnaPlancha();
    double ancho() {return _ancho;}
    double alto() {return _alto;}
    void setearAlto(double alto) {_alto = alto;}
    void setearAncho(double ancho) {_ancho = ancho;}

private:
    double _ancho = 0.0;
    double _alto = 0.0;
};


//!
//! \brief FFDWDH
//! Devuelve el area sobrante segun el orden en que estaban las piezas en el gen
//! Es fundamenta controlar si hay que usar una nueva plancha o no de esa manera
//! es posible medir que tan buena es la secuencia de corte
//! \param Piezas
//! \param Ancho_plancha
//! \param Alto_plancha
//! \return
//!

static double FFDWDH(QVector<PiezaCorte> Piezas, double Ancho_plancha, double Alto_plancha) {

    //Vector que contiene las columnas de la plancha
    QVector<ColumnaPlancha> columnas;

    //Cargo la primera columna
    ColumnaPlancha Auxiliar;
    //El ancho de la primera columna me lo da la primera pieza de la cadena ordenada "Piezas"
    Auxiliar.setearAncho(Piezas[0].ancho());
    //El alto si es el de la plancha
    Auxiliar.setearAlto(Alto_plancha);

    columnas.append(Auxiliar);

    double Area_plancha = Ancho_plancha * Alto_plancha;
    QVector<double> area_sobrante_columnas;

    int j = 0;

    for (int i = 0; i< Piezas.size(); i++) {
        while (Piezas[i].ancho > columnas.at(j).ancho() ||Piezas[i].alto > columnas.at(j).alto()) {
            //Calcular el area sobrante de la columna
            double calc_aux = (columnas.at(j).ancho() * columnas.at(j).alto()); //Estaria bien??
            area_sobrante_columnas.append(calc_aux);

            //Controlar si necesito una nueva plancha de vidrio

            //Si no puedo colocar ninguna pieza mas en la columna creo otra
            Auxiliar.setearAncho(Piezas[i].ancho());
            Auxiliar.setearAlto(Alto_plancha);
            columnas.append(Auxiliar);
            j++;
        }
        columnas[j].setearAncho( columnas[j].ancho() - Piezas[i].ancho() ); //???
        columnas[j].setearAlto( columnas[j].alto() - Piezas[i].alto() );
    }

    //Sumo la totalidad del area sobrante y lo devuelvo como fitness
    double area_sobrante = 0.0;
    for (int i = 0; i< area_sobrante_columnas.size(); i++) {
        area_sobrante += area_sobrante_columnas.at(i);
    }

    return area_sobrante;

}

#endif // FFDWDH_H
