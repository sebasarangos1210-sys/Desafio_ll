#ifndef FUENTEREPRODUCCION_H
#define FUENTEREPRODUCCION_H

#include "Sistema.h"
#include "ListaReproduccion.h"
#include "Cancion.h"

class FuenteReproduccion {
public:
    enum TipoFuente {
        ALEATORIA_SISTEMA,
        LISTA_FAVORITOS,
        LISTA_PERSONALIZADA
    };

private:
    Sistema* sistema;
    ListaReproduccion* listaReproduccion;
    TipoFuente tipoFuente;

    Cancion** cancionesReproducidas;
    int cantidadReproducidas;
    int capacidadReproducidas;

    int indiceActual;
    bool modoAleatorio;

    void redimensionarReproducidas();
    int generarIndiceAleatorio(int max);

public:
    FuenteReproduccion();
    FuenteReproduccion(Sistema* sistema);
    FuenteReproduccion(ListaReproduccion* lista);
    ~FuenteReproduccion();

    void establecerSistema(Sistema* sistema);
    void establecerListaReproduccion(ListaReproduccion* lista);

    Cancion* siguienteCancion();
    Cancion* cancionActual() const;
    bool haySiguiente() const;
    void reiniciar();

    Cancion* seleccionarCancionAleatoria();
    bool yaFueReproducida(int idCancion);

    void setModoAleatorio(bool activar);
    bool esModoAleatorio() const;

    TipoFuente getTipoFuente() const;
    int getCantidadCanciones() const;
    int getCantidadReproducidas() const;

    int calcularMemoriaUsada() const;
};

#endif
