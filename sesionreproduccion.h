#ifndef LISTAREPRODUCCION_H
#define LISTAREPRODUCCION_H

#include "Cancion.h"

class ListaReproduccion {
private:
    Cancion** canciones;
    int numCanciones;
    int capacidadMaxima;
    int indiceActual;
    bool modoAleatorio;
    bool modoRepetir;
    int* historial;
    int tamHistorial;
    int capacidadHistorial;

    void redimensionarCanciones();
    void redimensionarHistorial();
    int generarIndiceAleatorio() const;
    void agregarAlHistorial(int indice);

public:
    ListaReproduccion();
    ListaReproduccion(int capacidadMax);
    ListaReproduccion(const ListaReproduccion& otra);
    ~ListaReproduccion();

    bool agregarCancion(Cancion* cancion);
    bool eliminarCancion(int idCancion);
    Cancion* buscarCancion(int idCancion) const;
    bool contieneCancion(int idCancion) const;

    Cancion* obtenerCancionActual() const;
    Cancion* siguienteCancion();
    Cancion* cancionPrevia(int maxRetroceso);
    void reiniciarReproduccion();

    void activarModoAleatorio(bool activar);
    void activarModoRepetir(bool activar);
    bool esModoAleatorio() const;
    bool esModoRepetir() const;

    void limpiarHistorial();
    int* obtenerHistorial(int& tamanio) const;

    int getNumCanciones() const;
    int getCapacidadMaxima() const;
    int getIndiceActual() const;
    bool estaLlena() const;
    bool estaVacia() const;

    ListaReproduccion& operator=(const ListaReproduccion& otra);
    ListaReproduccion& operator+=(Cancion* cancion);
    ListaReproduccion& operator+=(const ListaReproduccion& otra);
    ListaReproduccion& operator-=(int idCancion);
    bool operator==(const ListaReproduccion& otra) const;
    Cancion* operator[](int indice) const;

    int calcularMemoriaUsada() const;
};

#endif
