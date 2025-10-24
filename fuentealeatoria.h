#ifndef FUENTEALEATORIA_H
#define FUENTEALEATORIA_H

#include "Sistema.h"
#include "Cancion.h"

class FuenteAleatoria {
private:
    Sistema* sistema;
    Cancion** cancionesReproducidas;
    int cantidadReproducidas;
    int capacidadReproducidas;

    void redimensionarReproducidas();

public:
    FuenteAleatoria();
    FuenteAleatoria(Sistema* sistema);
    ~FuenteAleatoria();

    Cancion* siguienteCancion();
    bool haySiguiente();
    void reiniciar();
    Cancion* seleccionarCancionAleatoria();
    bool yaFueReproducida(int idCancion);

    int calcularMemoriaUsada() const;
};

#endif
