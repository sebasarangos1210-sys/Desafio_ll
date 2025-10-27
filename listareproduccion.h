#ifndef LISTAREPRODUCCION_H
#define LISTAREPRODUCCION_H

#include "Cancion.h"
#include <string>
using namespace std;

class ListaReproduccion {
private:
    Cancion** canciones;
    int numCanciones;
    int capacidadMaxima;
    string nombre;

    void redimensionar();

public:
    ListaReproduccion(int capacidad = 10000);
    ListaReproduccion(const ListaReproduccion& otra);
    ~ListaReproduccion();

    bool agregarCancion(Cancion* cancion);
    bool eliminarCancion(int idCancion);
    void vaciar();  // Vaciar toda la lista
    void limpiar();
    Cancion* buscarCancion(int idCancion) const;
    bool estaVacia() const;
    bool estaLlena() const;

    int getNumCanciones() const;
    int getCapacidadMaxima() const;
    Cancion** getCanciones() const;

    // Sobrecarga para acceso por índice
    Cancion* operator[](int indice) const;

    // Sobrecarga para combinar listas (seguir otra lista)
    ListaReproduccion& operator+=(const ListaReproduccion& otra);

    int calcularMemoriaUsada() const;
};

#endif
