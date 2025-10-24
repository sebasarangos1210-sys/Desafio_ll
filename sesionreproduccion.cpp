#include "ListaReproduccion.h"
#include <cstdlib>
#include <ctime>

ListaReproduccion::ListaReproduccion()
    : canciones(nullptr), numCanciones(0), capacidadMaxima(10000),
    indiceActual(0), modoAleatorio(false), modoRepetir(false),
    historial(nullptr), tamHistorial(0), capacidadHistorial(10) {
    canciones = new Cancion*[capacidadMaxima];
    for (int i = 0; i < capacidadMaxima; i++) {
        canciones[i] = nullptr;
    }

    historial = new int[capacidadHistorial];
    srand(time(0));
}

ListaReproduccion::ListaReproduccion(int capacidadMax)
    : canciones(nullptr), numCanciones(0), capacidadMaxima(capacidadMax),
    indiceActual(0), modoAleatorio(false), modoRepetir(false),
    historial(nullptr), tamHistorial(0), capacidadHistorial(10) {
    if (capacidadMaxima <= 0) {
        capacidadMaxima = 10000;
    }

    canciones = new Cancion*[capacidadMaxima];
    for (int i = 0; i < capacidadMaxima; i++) {
        canciones[i] = nullptr;
    }

    historial = new int[capacidadHistorial];
    srand(time(0));
}

ListaReproduccion::ListaReproduccion(const ListaReproduccion& otra)
    : numCanciones(otra.numCanciones), capacidadMaxima(otra.capacidadMaxima),
    indiceActual(otra.indiceActual), modoAleatorio(otra.modoAleatorio),
    modoRepetir(otra.modoRepetir), tamHistorial(otra.tamHistorial),
    capacidadHistorial(otra.capacidadHistorial) {

    canciones = new Cancion*[capacidadMaxima];
    for (int i = 0; i < numCanciones; i++) {
        if (otra.canciones[i] != nullptr) {
            canciones[i] = otra.canciones[i];
        } else {
            canciones[i] = nullptr;
        }
    }
    for (int i = numCanciones; i < capacidadMaxima; i++) {
        canciones[i] = nullptr;
    }

    historial = new int[capacidadHistorial];
    for (int i = 0; i < tamHistorial; i++) {
        historial[i] = otra.historial[i];
    }
}

ListaReproduccion::~ListaReproduccion() {
    if (canciones != nullptr) {
        delete[] canciones;
        canciones = nullptr;
    }

    if (historial != nullptr) {
        delete[] historial;
        historial = nullptr;
    }
}

void ListaReproduccion::redimensionarCanciones() {
    int nuevaCapacidad = capacidadMaxima * 2;
    if (nuevaCapacidad > 10000) {
        nuevaCapacidad = 10000;
    }

    Cancion** nuevoArreglo = new Cancion*[nuevaCapacidad];

    for (int i = 0; i < numCanciones; i++) {
        nuevoArreglo[i] = canciones[i];
    }

    for (int i = numCanciones; i < nuevaCapacidad; i++) {
        nuevoArreglo[i] = nullptr;
    }

    delete[] canciones;
    canciones = nuevoArreglo;
    capacidadMaxima = nuevaCapacidad;
}

void ListaReproduccion::redimensionarHistorial() {
    int nuevaCapacidad = capacidadHistorial * 2;
    int* nuevoHistorial = new int[nuevaCapacidad];

    for (int i = 0; i < tamHistorial; i++) {
        nuevoHistorial[i] = historial[i];
    }

    delete[] historial;
    historial = nuevoHistorial;
    capacidadHistorial = nuevaCapacidad;
}

int ListaReproduccion::generarIndiceAleatorio() const {
    if (numCanciones == 0) return -1;
    return rand() % numCanciones;
}

void ListaReproduccion::agregarAlHistorial(int indice) {
    if (modoRepetir && tamHistorial > 0 && historial[tamHistorial - 1] == indice) {
        return;
    }

    if (tamHistorial >= capacidadHistorial) {
        redimensionarHistorial();
    }

    historial[tamHistorial] = indice;
    tamHistorial++;
}

bool ListaReproduccion::agregarCancion(Cancion* cancion) {
    if (cancion == nullptr || numCanciones >= capacidadMaxima) {
        return false;
    }

    if (contieneCancion(cancion->getId())) {
        return false;
    }

    if (numCanciones >= capacidadMaxima && capacidadMaxima < 10000) {
        redimensionarCanciones();
    }

    canciones[numCanciones] = cancion;
    numCanciones++;
    return true;
}

bool ListaReproduccion::eliminarCancion(int idCancion) {
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i] != nullptr && canciones[i]->getId() == idCancion) {
            for (int j = i; j < numCanciones - 1; j++) {
                canciones[j] = canciones[j + 1];
            }
            canciones[numCanciones - 1] = nullptr;
            numCanciones--;

            if (indiceActual >= numCanciones && numCanciones > 0) {
                indiceActual = numCanciones - 1;
            }

            return true;
        }
    }
    return false;
}

Cancion* ListaReproduccion::buscarCancion(int idCancion) const {
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i] != nullptr && canciones[i]->getId() == idCancion) {
            return canciones[i];
        }
    }
    return nullptr;
}

bool ListaReproduccion::contieneCancion(int idCancion) const {
    return buscarCancion(idCancion) != nullptr;
}

Cancion* ListaReproduccion::obtenerCancionActual() const {
    if (numCanciones == 0 || indiceActual < 0 || indiceActual >= numCanciones) {
        return nullptr;
    }
    return canciones[indiceActual];
}

Cancion* ListaReproduccion::siguienteCancion() {
    if (numCanciones == 0) {
        return nullptr;
    }

    if (modoRepetir) {
        agregarAlHistorial(indiceActual);
        return canciones[indiceActual];
    }

    if (modoAleatorio) {
        indiceActual = generarIndiceAleatorio();
    } else {
        indiceActual++;
        if (indiceActual >= numCanciones) {
            indiceActual = 0;
        }
    }

    agregarAlHistorial(indiceActual);
    return canciones[indiceActual];
}

Cancion* ListaReproduccion::cancionPrevia(int maxRetroceso) {
    if (numCanciones == 0 || tamHistorial <= 1) {
        return nullptr;
    }

    int retrocesos = (tamHistorial > maxRetroceso) ? maxRetroceso : tamHistorial - 1;

    if (retrocesos > 0) {
        tamHistorial -= retrocesos;
        indiceActual = historial[tamHistorial - 1];
        return canciones[indiceActual];
    }

    return nullptr;
}

void ListaReproduccion::reiniciarReproduccion() {
    indiceActual = 0;
    limpiarHistorial();
}

void ListaReproduccion::activarModoAleatorio(bool activar) {
    modoAleatorio = activar;
}

void ListaReproduccion::activarModoRepetir(bool activar) {
    modoRepetir = activar;
}

bool ListaReproduccion::esModoAleatorio() const {
    return modoAleatorio;
}

bool ListaReproduccion::esModoRepetir() const {
    return modoRepetir;
}

void ListaReproduccion::limpiarHistorial() {
    tamHistorial = 0;
}

int* ListaReproduccion::obtenerHistorial(int& tamanio) const {
    tamanio = tamHistorial;
    if (tamHistorial == 0) {
        return nullptr;
    }

    int* copia = new int[tamHistorial];
    for (int i = 0; i < tamHistorial; i++) {
        copia[i] = historial[i];
    }
    return copia;
}

int ListaReproduccion::getNumCanciones() const {
    return numCanciones;
}

int ListaReproduccion::getCapacidadMaxima() const {
    return capacidadMaxima;
}

int ListaReproduccion::getIndiceActual() const {
    return indiceActual;
}

bool ListaReproduccion::estaLlena() const {
    return numCanciones >= capacidadMaxima;
}

bool ListaReproduccion::estaVacia() const {
    return numCanciones == 0;
}

ListaReproduccion& ListaReproduccion::operator=(const ListaReproduccion& otra) {
    if (this != &otra) {
        if (canciones != nullptr) {
            delete[] canciones;
        }
        if (historial != nullptr) {
            delete[] historial;
        }

        numCanciones = otra.numCanciones;
        capacidadMaxima = otra.capacidadMaxima;
        indiceActual = otra.indiceActual;
        modoAleatorio = otra.modoAleatorio;
        modoRepetir = otra.modoRepetir;
        tamHistorial = otra.tamHistorial;
        capacidadHistorial = otra.capacidadHistorial;

        canciones = new Cancion*[capacidadMaxima];
        for (int i = 0; i < numCanciones; i++) {
            canciones[i] = otra.canciones[i];
        }
        for (int i = numCanciones; i < capacidadMaxima; i++) {
            canciones[i] = nullptr;
        }

        historial = new int[capacidadHistorial];
        for (int i = 0; i < tamHistorial; i++) {
            historial[i] = otra.historial[i];
        }
    }
    return *this;
}

ListaReproduccion& ListaReproduccion::operator+=(Cancion* cancion) {
    agregarCancion(cancion);
    return *this;
}

ListaReproduccion& ListaReproduccion::operator+=(const ListaReproduccion& otra) {
    for (int i = 0; i < otra.numCanciones; i++) {
        if (otra.canciones[i] != nullptr) {
            agregarCancion(otra.canciones[i]);
        }
    }
    return *this;
}

ListaReproduccion& ListaReproduccion::operator-=(int idCancion) {
    eliminarCancion(idCancion);
    return *this;
}

bool ListaReproduccion::operator==(const ListaReproduccion& otra) const {
    if (numCanciones != otra.numCanciones) {
        return false;
    }

    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i] == nullptr || otra.canciones[i] == nullptr) {
            if (canciones[i] != otra.canciones[i]) {
                return false;
            }
        } else if (*canciones[i] != *otra.canciones[i]) {
            return false;
        }
    }

    return true;
}

Cancion* ListaReproduccion::operator[](int indice) const {
    if (indice >= 0 && indice < numCanciones) {
        return canciones[indice];
    }
    return nullptr;
}

int ListaReproduccion::calcularMemoriaUsada() const {
    int total = sizeof(*this);
    total += sizeof(Cancion*) * capacidadMaxima;
    total += sizeof(int) * capacidadHistorial;
    return total;
}
