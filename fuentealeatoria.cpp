#include "FuenteAleatoria.h"

// Generador de números pseudoaleatorios simple
static unsigned int semilla_aleatoria = 1;

static void inicializarSemilla() {
    // Usar dirección de memoria como semilla (varía en cada ejecución)
    semilla_aleatoria = (unsigned int)(long long)&semilla_aleatoria;
}

static int generarAleatorio(int max) {
    semilla_aleatoria = semilla_aleatoria * 1103515245 + 12345;
    return (semilla_aleatoria / 65536) % max;
}

FuenteAleatoria::FuenteAleatoria()
    : sistema(nullptr), cancionesReproducidas(nullptr),
    cantidadReproducidas(0), capacidadReproducidas(100) {
    cancionesReproducidas = new Cancion*[capacidadReproducidas];
    for (int i = 0; i < capacidadReproducidas; i++) {
        cancionesReproducidas[i] = nullptr;
    }
    inicializarSemilla();
}

FuenteAleatoria::FuenteAleatoria(Sistema* sistema)
    : sistema(sistema), cancionesReproducidas(nullptr),
    cantidadReproducidas(0), capacidadReproducidas(100) {
    cancionesReproducidas = new Cancion*[capacidadReproducidas];
    for (int i = 0; i < capacidadReproducidas; i++) {
        cancionesReproducidas[i] = nullptr;
    }
    inicializarSemilla();
}

FuenteAleatoria::~FuenteAleatoria() {
    if (cancionesReproducidas != nullptr) {
        delete[] cancionesReproducidas;
        cancionesReproducidas = nullptr;
    }
}

void FuenteAleatoria::redimensionarReproducidas() {
    int nuevaCapacidad = capacidadReproducidas * 2;
    Cancion** nuevoArreglo = new Cancion*[nuevaCapacidad];

    for (int i = 0; i < cantidadReproducidas; i++) {
        nuevoArreglo[i] = cancionesReproducidas[i];
    }

    for (int i = cantidadReproducidas; i < nuevaCapacidad; i++) {
        nuevoArreglo[i] = nullptr;
    }

    delete[] cancionesReproducidas;
    cancionesReproducidas = nuevoArreglo;
    capacidadReproducidas = nuevaCapacidad;
}

Cancion* FuenteAleatoria::siguienteCancion() {
    if (sistema == nullptr || !haySiguiente()) {
        return nullptr;
    }

    Cancion* cancion = seleccionarCancionAleatoria();

    if (cancion != nullptr) {
        if (cantidadReproducidas >= capacidadReproducidas) {
            redimensionarReproducidas();
        }

        cancionesReproducidas[cantidadReproducidas] = cancion;
        cantidadReproducidas++;
    }

    return cancion;
}

bool FuenteAleatoria::haySiguiente() {
    if (sistema == nullptr) {
        return false;
    }

    int totalCanciones = sistema->getTotalCanciones();
    return cantidadReproducidas < totalCanciones;
}

void FuenteAleatoria::reiniciar() {
    cantidadReproducidas = 0;
    for (int i = 0; i < capacidadReproducidas; i++) {
        cancionesReproducidas[i] = nullptr;
    }
}

Cancion* FuenteAleatoria::seleccionarCancionAleatoria() {
    if (sistema == nullptr) {
        return nullptr;
    }

    int totalCanciones = 0;
    Cancion** todasCanciones = sistema->obtenerTodasCanciones(totalCanciones);

    if (todasCanciones == nullptr || totalCanciones == 0) {
        return nullptr;
    }

    int intentos = 0;
    int maxIntentos = totalCanciones * 2;
    Cancion* cancionSeleccionada = nullptr;

    while (intentos < maxIntentos) {
        int indiceAleatorio = generarAleatorio(totalCanciones);
        Cancion* candidata = todasCanciones[indiceAleatorio];

        if (candidata != nullptr && !yaFueReproducida(candidata->getId())) {
            cancionSeleccionada = candidata;
            break;
        }

        intentos++;
    }

    if (cancionSeleccionada == nullptr && totalCanciones > 0) {
        cancionSeleccionada = todasCanciones[0];
    }

    delete[] todasCanciones;

    return cancionSeleccionada;
}

bool FuenteAleatoria::yaFueReproducida(int idCancion) {
    for (int i = 0; i < cantidadReproducidas; i++) {
        if (cancionesReproducidas[i] != nullptr &&
            cancionesReproducidas[i]->getId() == idCancion) {
            return true;
        }
    }
    return false;
}
