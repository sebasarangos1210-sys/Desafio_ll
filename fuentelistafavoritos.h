#ifndef FUENTELISTAFAVORITOS_H
#define FUENTELISTAFAVORITOS_H

#include "ListaReproduccion.h"
#include "Cancion.h"

class FuenteListaFavoritos {
private:
    ListaReproduccion* listaFavoritos;
    int indiceActual;
    bool modoAleatorio;

public:
    FuenteListaFavoritos();
    FuenteListaFavoritos(ListaReproduccion* lista);
    ~FuenteListaFavoritos();

    Cancion* siguienteCancion();
    Cancion* cancionActual() const;
    bool haySiguiente() const;
    void reiniciar();
    void setModoAleatorio(bool activar);
    bool esModoAleatorio() const;
    int getCantidadCanciones() const;

    int calcularMemoriaUsada() const;
};

#endif
