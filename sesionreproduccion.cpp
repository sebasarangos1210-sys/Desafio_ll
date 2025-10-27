#include "SesionReproduccion.h"
#include "Album.h"

SesionReproduccion::SesionReproduccion()
    : usuario(nullptr), cancionActual(nullptr), historial(nullptr),
    cantidadHistorial(0), capacidadHistorial(50),
    repetir(false), enReproduccion(false),
    contadorCanciones(0), fuente(nullptr) {

    historial = new Cancion*[capacidadHistorial];
    for (int i = 0; i < capacidadHistorial; i++) {
        historial[i] = nullptr;
    }

    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    generador.seed(seed);
}

SesionReproduccion::SesionReproduccion(Usuario* user)
    : usuario(user), cancionActual(nullptr), historial(nullptr),
    cantidadHistorial(0), capacidadHistorial(50),
    repetir(false), enReproduccion(false),
    contadorCanciones(0), fuente(nullptr) {

    historial = new Cancion*[capacidadHistorial];
    for (int i = 0; i < capacidadHistorial; i++) {
        historial[i] = nullptr;
    }

    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    generador.seed(seed);
}

SesionReproduccion::~SesionReproduccion() {
    if (historial != nullptr) {
        delete[] historial;
        historial = nullptr;
    }
}

void SesionReproduccion::redimensionarHistorial() {
    int nuevaCapacidad = capacidadHistorial * 2;
    Cancion** nuevoArreglo = new Cancion*[nuevaCapacidad];

    for (int i = 0; i < cantidadHistorial; i++) {
        nuevoArreglo[i] = historial[i];
    }

    for (int i = cantidadHistorial; i < nuevaCapacidad; i++) {
        nuevoArreglo[i] = nullptr;
    }

    delete[] historial;
    historial = nuevoArreglo;
    capacidadHistorial = nuevaCapacidad;
}

void SesionReproduccion::agregarAlHistorial(Cancion* cancion) {
    if (cancion == nullptr) return;

    if (repetir && cantidadHistorial > 0 && historial[cantidadHistorial - 1] == cancion) {
        return;
    }

    if (cantidadHistorial >= capacidadHistorial) {
        redimensionarHistorial();
    }

    historial[cantidadHistorial] = cancion;
    cantidadHistorial++;
}

void SesionReproduccion::iniciar() {
    if (fuente == nullptr || !fuente->haySiguiente()) {
        return;
    }

    enReproduccion = true;
    contadorCanciones = 0;
    tiempoInicio = std::chrono::steady_clock::now();
}

void SesionReproduccion::detener() {
    enReproduccion = false;
    cancionActual = nullptr;
}

bool SesionReproduccion::siguiente() {
    if (!enReproduccion || fuente == nullptr) {
        return false;
    }

    if (repetir && cancionActual != nullptr) {
        agregarAlHistorial(cancionActual);
        return true;
    }

    Cancion* siguienteCancion = fuente->siguienteCancion();

    if (siguienteCancion != nullptr) {
        cancionActual = siguienteCancion;
        agregarAlHistorial(cancionActual);
        contadorCanciones++;

        cancionActual->incrementarReproducciones();

        return true;
    }

    return false;
}

bool SesionReproduccion::anterior() {
    if (!enReproduccion || !puedeRetroceder()) {
        return false;
    }

    if (cantidadHistorial > 1) {
        cantidadHistorial--;

        if (cantidadHistorial > 0) {
            cancionActual = historial[cantidadHistorial - 1];
            return true;
        }
    }

    return false;
}

void SesionReproduccion::establecerFuente(FuenteReproduccion* fuenteReproduccion) {
    fuente = fuenteReproduccion;
}

long long SesionReproduccion::obtenerTiempoTranscurrido() {
    auto ahora = std::chrono::steady_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(ahora - tiempoInicio);
    return duracion.count();
}

bool SesionReproduccion::puedeRetroceder() {
    if (usuario == nullptr || !usuario->esPremium()) {
        return false;
    }

    int maxRetroceso = 4;
    if (fuente != nullptr && fuente->getTipoFuente() == FuenteReproduccion::LISTA_FAVORITOS) {
        maxRetroceso = 6;
    }

    return cantidadHistorial > 1 && cantidadHistorial <= maxRetroceso + 1;
}

bool SesionReproduccion::haySiguiente() {
    if (repetir) return true;
    if (fuente != nullptr) {
        return fuente->haySiguiente();
    }
    return false;
}

Usuario* SesionReproduccion::getUsuario() const {
    return usuario;
}

Cancion* SesionReproduccion::getCancionActual() const {
    return cancionActual;
}

bool SesionReproduccion::estaEnReproduccion() const {
    return enReproduccion;
}

bool SesionReproduccion::esModoRepetir() const {
    return repetir;
}

int SesionReproduccion::getContadorCanciones() const {
    return contadorCanciones;
}

int SesionReproduccion::getCantidadHistorial() const {
    return cantidadHistorial;
}

FuenteReproduccion* SesionReproduccion::getFuente() const {
    return fuente;
}

void SesionReproduccion::setModoRepetir(bool activar) {
    repetir = activar;
}
