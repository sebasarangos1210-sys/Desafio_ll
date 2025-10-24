#include "FuenteListaFavoritos.h"

// Generador de números pseudoaleatorios simple
static unsigned int semilla_favoritos = 555555555;

static void inicializarSemillaFavoritos() {
    semilla_favoritos = (unsigned int)(long long)&semilla_favoritos;
}

static int generarAleatorioFavoritos(int max) {
    semilla_favoritos = semilla_favoritos * 1103515245 + 12345;
    return (semilla_favoritos / 65536) % max;
}

FuenteListaFavoritos::FuenteListaFavoritos()
    : listaFavoritos(nullptr), indiceActual(0), modoAleatorio(false) {
    inicializarSemillaFavoritos();
}

FuenteListaFavoritos::FuenteListaFavoritos(ListaReproduccion* lista)
    : listaFavoritos(lista), indiceActual(0), modoAleatorio(false) {
    inicializarSemillaFavoritos();
}

FuenteListaFavoritos::~FuenteListaFavoritos() {
}

Cancion* FuenteListaFavoritos::siguienteCancion() {
    if (listaFavoritos == nullptr || listaFavoritos->estaVacia()) {
        return nullptr;
    }

    Cancion* cancion = nullptr;

    if (modoAleatorio) {
        int indiceAleatorio = generarAleatorioFavoritos(listaFavoritos->getNumCanciones());
        cancion = (*listaFavoritos)[indiceAleatorio];
        indiceActual = indiceAleatorio;
    } else {
        cancion = (*listaFavoritos)[indiceActual];
        indiceActual++;

        if (indiceActual >= listaFavoritos->getNumCanciones()) {
            indiceActual = 0; // Volver al inicio
        }
    }

    return cancion;
}

Cancion* FuenteListaFavoritos::cancionActual() const {
    if (listaFavoritos == nullptr || indiceActual < 0 ||
        indiceActual >= listaFavoritos->getNumCanciones()) {
        return nullptr;
    }

    return (*listaFavoritos)[indiceActual];
}

bool FuenteListaFavoritos::haySiguiente() const {
    if (listaFavoritos == nullptr) {
        return false;
    }

    return !listaFavoritos->estaVacia();
}

void FuenteListaFavoritos::reiniciar() {
    indiceActual = 0;
}

void FuenteListaFavoritos::setModoAleatorio(bool activar) {
    modoAleatorio = activar;
}

bool FuenteListaFavoritos::esModoAleatorio() const {
    return modoAleatorio;
}

int FuenteListaFavoritos::getCantidadCanciones() const {
    if (listaFavoritos == nullptr) {
        return 0;
    }

    return listaFavoritos->getNumCanciones();
}

int FuenteListaFavoritos::calcularMemoriaUsada() const {
    int total = sizeof(*this);
    return total;
}
