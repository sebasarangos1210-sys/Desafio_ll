#ifndef SESIONREPRODUCCION_H
#define SESIONREPRODUCCION_H

#include "FuenteReproduccion.h"

class SesionReproduccion {
private:
    FuenteReproduccion* fuente;
    bool repetir;
    bool enReproduccion;

public:
    SesionReproduccion();
    SesionReproduccion(FuenteReproduccion* fuenteReproduccion);
    ~SesionReproduccion();

    void iniciar();
    void detener();
    bool siguiente();
    bool anterior();

    void setModoRepetir(bool activar);
    bool esModoRepetir() const;
    bool estaEnReproduccion() const;

    FuenteReproduccion* getFuente() const;
    void setFuente(FuenteReproduccion* fuenteReproduccion);
    int calcularMemoriaUsada() const;
};

#endif
