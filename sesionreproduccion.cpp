#include "SesionReproduccion.h"

SesionReproduccion::SesionReproduccion()
    : fuente(nullptr), repetir(false), enReproduccion(false) {
}

SesionReproduccion::SesionReproduccion(FuenteReproduccion* fuenteReproduccion)
    : fuente(fuenteReproduccion), repetir(false), enReproduccion(false) {
}

SesionReproduccion::~SesionReproduccion() {
    // No elimina fuente porque no es responsabilidad de la sesión
}

void SesionReproduccion::iniciar() {
    if (fuente == nullptr || !fuente->haySiguiente()) {
        return;
    }
    enReproduccion = true;
}

void SesionReproduccion::detener() {
    enReproduccion = false;
}

bool SesionReproduccion::siguiente() {
    if (!enReproduccion || fuente == nullptr) {
        return false;
    }

    if (repetir) {
        // En modo repetir, solo retorna true sin avanzar
        return true;
    }

    return fuente->siguienteCancion() != nullptr;
}

bool SesionReproduccion::anterior() {
    if (!enReproduccion || fuente == nullptr) {
        return false;
    }

    Cancion* cancion = fuente->cancionAnterior();
    return cancion != nullptr;
}

bool SesionReproduccion::anterior() {
    if (!enReproduccion || fuente == nullptr) {
        return false;
    }

    // La lógica de retroceso la maneja la fuente
    return true;
}

void SesionReproduccion::setModoRepetir(bool activar) {
    repetir = activar;
}

bool SesionReproduccion::esModoRepetir() const {
    return repetir;
}

bool SesionReproduccion::estaEnReproduccion() const {
    return enReproduccion;
}

FuenteReproduccion* SesionReproduccion::getFuente() const {
    return fuente;
}

void SesionReproduccion::setFuente(FuenteReproduccion* fuenteReproduccion) {
    fuente = fuenteReproduccion;
}

int SesionReproduccion::calcularMemoriaUsada() const {
    int total = sizeof(*this);
    if (fuente != nullptr) {
        total += fuente->calcularMemoriaUsada();
    }
    return total;
}
