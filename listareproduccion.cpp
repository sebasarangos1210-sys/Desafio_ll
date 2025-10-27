#include "ListaReproduccion.h"

ListaReproduccion::ListaReproduccion(int capacidad)
    : numCanciones(0), capacidadMaxima(capacidad), nombre("") {
    canciones = new Cancion*[capacidadMaxima];
    for (int i = 0; i < capacidadMaxima; i++) {
        canciones[i] = nullptr;
    }
}

ListaReproduccion::ListaReproduccion(const ListaReproduccion& otra)
    : numCanciones(otra.numCanciones),
    capacidadMaxima(otra.capacidadMaxima),
    nombre(otra.nombre) {

    canciones = new Cancion*[capacidadMaxima];
    for (int i = 0; i < numCanciones; i++) {
        canciones[i] = otra.canciones[i];  // Copia el puntero, NO la canción
    }
    for (int i = numCanciones; i < capacidadMaxima; i++) {
        canciones[i] = nullptr;
    }
}

ListaReproduccion::~ListaReproduccion() {
    if (canciones != nullptr) {
        delete[] canciones;  // Solo elimina el arreglo, NO las canciones
        canciones = nullptr;
    }
}

bool ListaReproduccion::agregarCancion(Cancion* cancion) {
    if (cancion == nullptr || estaLlena()) {
        return false;
    }

    // Verificar que no esté repetida
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i] != nullptr &&
            canciones[i]->getId() == cancion->getId()) {
            return false;  // Ya existe
        }
    }

    canciones[numCanciones] = cancion;  // Solo guarda el puntero
    numCanciones++;
    return true;
}

bool ListaReproduccion::eliminarCancion(int idCancion) {
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i] != nullptr &&
            canciones[i]->getId() == idCancion) {

            // Desplazar elementos
            for (int j = i; j < numCanciones - 1; j++) {
                canciones[j] = canciones[j + 1];
            }
            canciones[numCanciones - 1] = nullptr;
            numCanciones--;
            return true;
        }
    }
    return false;
}

Cancion* ListaReproduccion::buscarCancion(int idCancion) const {
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i] != nullptr &&
            canciones[i]->getId() == idCancion) {
            return canciones[i];
        }
    }
    return nullptr;
}

bool ListaReproduccion::estaVacia() const {
    return numCanciones == 0;
}

bool ListaReproduccion::estaLlena() const {
    return numCanciones >= capacidadMaxima;
}

int ListaReproduccion::getNumCanciones() const {
    return numCanciones;
}

int ListaReproduccion::getCapacidadMaxima() const {
    return capacidadMaxima;
}

Cancion** ListaReproduccion::getCanciones() const {
    return canciones;
}

Cancion* ListaReproduccion::operator[](int indice) const {
    if (indice >= 0 && indice < numCanciones) {
        return canciones[indice];
    }
    return nullptr;
}

// Para "seguir otra lista" (funcionalidad IV.b)
ListaReproduccion& ListaReproduccion::operator+=(const ListaReproduccion& otra) {
    for (int i = 0; i < otra.numCanciones; i++) {
        agregarCancion(otra.canciones[i]);  // agregarCancion ya valida duplicados
    }
    return *this;
}

int ListaReproduccion::calcularMemoriaUsada() const {
    int total = sizeof(*this);
    total += sizeof(Cancion*) * capacidadMaxima;
    total += nombre.length();
    return total;
}
