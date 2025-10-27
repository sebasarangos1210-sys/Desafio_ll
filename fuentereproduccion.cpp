#include "FuenteReproduccion.h"
#include <random>

// Generador de números aleatorios moderno (C++11)
static std::mt19937 generador_fuente(std::chrono::steady_clock::now().time_since_epoch().count());

FuenteReproduccion::FuenteReproduccion()
    : sistema(nullptr), sesionreproduccion(nullptr),
    tipoFuente(LISTA_PERSONALIZADA), cancionesReproducidas(nullptr),
    cantidadReproducidas(0), capacidadReproducidas(100),
    indiceActual(0), modoAleatorio(false) {

    cancionesReproducidas = new Cancion*[capacidadReproducidas];
    for (int i = 0; i < capacidadReproducidas; i++) {
        cancionesReproducidas[i] = nullptr;
    }
}

FuenteReproduccion::FuenteReproduccion(Sistema* sistema)
    : sistema(sistema), sesionreproducccion(nullptr),
    tipoFuente(ALEATORIA_SISTEMA), cancionesReproducidas(nullptr),
    cantidadReproducidas(0), capacidadReproducidas(100),
    indiceActual(0), modoAleatorio(true) {

    cancionesReproducidas = new Cancion*[capacidadReproducidas];
    for (int i = 0; i < capacidadReproducidas; i++) {
        cancionesReproducidas[i] = nullptr;
    }
}

FuenteReproduccion::FuenteReproduccion(ListaReproduccion* lista)
    : sistema(nullptr), sesionreproduccion(lista),
    tipoFuente(LISTA_FAVORITOS), cancionesReproducidas(nullptr),
    cantidadReproducidas(0), capacidadReproducidas(100),
    indiceActual(0), modoAleatorio(false) {

    cancionesReproducidas = new Cancion*[capacidadReproducidas];
    for (int i = 0; i < capacidadReproducidas; i++) {
        cancionesReproducidas[i] = nullptr;
    }
}

FuenteReproduccion::~FuenteReproduccion() {
    if (cancionesReproducidas != nullptr) {
        delete[] cancionesReproducidas;
        cancionesReproducidas = nullptr;
    }
}

void FuenteReproduccion::redimensionarReproducidas() {
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

int FuenteReproduccion::generarIndiceAleatorio(int max) {
    if (max <= 0) return 0;

    // Usar distribución uniforme moderna
    std::uniform_int_distribution<int> distribucion(0, max - 1);
    return distribucion(generador_fuente);
}

void FuenteReproduccion::establecerSistema(Sistema* sis) {
    sistema = sis;
    listaReproduccion = nullptr;
    tipoFuente = ALEATORIA_SISTEMA;
    modoAleatorio = true;
    reiniciar();
}

void FuenteReproduccion::establecersesionreproduccion(ListaReproduccion* lista) {
    listaReproduccion = lista;
    sistema = nullptr;
    tipoFuente = LISTA_FAVORITOS;
    reiniciar();
}

Cancion* FuenteReproduccion::siguienteCancion() {
    Cancion* cancion = nullptr;

    if (tipoFuente == ALEATORIA_SISTEMA) {
        // Modo aleatorio del sistema (todas las canciones)
        if (sistema != nullptr && haySiguiente()) {
            cancion = seleccionarCancionAleatoria();
        }
    } else if (tipoFuente == LISTA_FAVORITOS || tipoFuente == LISTA_PERSONALIZADA) {
        // Modo lista (favoritos o personalizada)
        if (listaReproduccion != nullptr && !listaReproduccion->estaVacia()) {
            if (modoAleatorio) {
                indiceActual = generarIndiceAleatorio(listaReproduccion->getNumCanciones());
            } else {
                if (indiceActual >= sesionreproduccion->getNumCanciones()) {
                    indiceActual = 0;  // Volver al inicio cuando llega al final
                }
            }
            cancion = (*listaReproduccion)[indiceActual];

            if (!modoAleatorio) {
                indiceActual++;
            }
        }
    }

    // Agregar al historial de reproducidas
    if (cancion != nullptr) {
        if (cantidadReproducidas >= capacidadReproducidas) {
            redimensionarReproducidas();
        }
        cancionesReproducidas[cantidadReproducidas] = cancion;
        cantidadReproducidas++;
    }

    return cancion;
}

Cancion* FuenteReproduccion::cancionActual() const {
    if (tipoFuente == ALEATORIA_SISTEMA) {
        if (cantidadReproducidas > 0) {
            return cancionesReproducidas[cantidadReproducidas - 1];
        }
    } else {
        if (listaReproduccion != nullptr && indiceActual >= 0 &&
            indiceActual < sesionreproduccion->getNumCanciones()) {
            return (*sesionreproduccion)[indiceActual];
        }
    }
    return nullptr;
}

bool FuenteReproduccion::haySiguiente() const {
    if (tipoFuente == ALEATORIA_SISTEMA) {
        if (sistema == nullptr) return false;
        int totalCanciones = sistema->getTotalCanciones();
        return cantidadReproducidas < totalCanciones;
    } else {
        if (sesionreproduccion == nullptr) return false;
        return !sesionreproduccion->estaVacia();
    }
}

void FuenteReproduccion::reiniciar() {
    cantidadReproducidas = 0;
    indiceActual = 0;
    for (int i = 0; i < capacidadReproducidas; i++) {
        cancionesReproducidas[i] = nullptr;
    }
}

Cancion* FuenteReproduccion::seleccionarCancionAleatoria() {
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

    // Buscar una canción no reproducida usando selección aleatoria moderna
    while (intentos < maxIntentos) {
        int indiceAleatorio = generarIndiceAleatorio(totalCanciones);
        Cancion* candidata = todasCanciones[indiceAleatorio];

        if (candidata != nullptr && !yaFueReproducida(candidata->getId())) {
            cancionSeleccionada = candidata;
            break;
        }

        intentos++;
    }

    // Si no se encontró canción no reproducida, tomar la primera disponible
    if (cancionSeleccionada == nullptr && totalCanciones > 0) {
        for (int i = 0; i < totalCanciones; i++) {
            if (todasCanciones[i] != nullptr) {
                cancionSeleccionada = todasCanciones[i];
                break;
            }
        }
    }

    delete[] todasCanciones;

    return cancionSeleccionada;
}

bool FuenteReproduccion::yaFueReproducida(int idCancion) {
    for (int i = 0; i < cantidadReproducidas; i++) {
        if (cancionesReproducidas[i] != nullptr &&
            cancionesReproducidas[i]->getId() == idCancion) {
            return true;
        }
    }
    return false;
}

Cancion* FuenteReproduccion::cancionAnterior() {
    if (cantidadReproducidas < 2) {
        return nullptr;  // No hay canción anterior
    }

    if (tipoFuente == ALEATORIA_SISTEMA) {
        // Para reproducción aleatoria: retroceder en el historial
        // Límite: 4 canciones hacia atrás (según enunciado)
        if (cantidadReproducidas >= 2) {
            cantidadReproducidas--;  // Retroceder una posición
            return cancionesReproducidas[cantidadReproducidas - 1];
        }
    }
    else if (tipoFuente == LISTA_FAVORITOS || tipoFuente == LISTA_PERSONALIZADA) {
        if (!modoAleatorio) {
            // Modo secuencial: retroceder en la lista
            if (indiceActual > 0) {
                indiceActual--;
                return (*listaReproduccion)[indiceActual];
            }
        } else {
            // Modo aleatorio de lista: usar historial
            if (cantidadReproducidas >= 2) {
                cantidadReproducidas--;
                return cancionesReproducidas[cantidadReproducidas - 1];
            }
        }
    }

    return nullptr;
}

int FuenteReproduccion::obtenerLimiteRetroceso() const {
    if (tipoFuente == ALEATORIA_SISTEMA) {
        return LIMITE_RETROCESO_ALEATORIO;  // 4
    } else {
        return LIMITE_RETROCESO_FAVORITOS;   // 6
    }
}

Cancion* FuenteReproduccion::cancionAnterior() {
    int limite = obtenerLimiteRetroceso();

    // Verificar si hay suficiente historial
    if (cantidadReproducidas < 2) {
        return nullptr;  // No hay canción anterior
    }

    // Calcular cuántas canciones podemos retroceder desde la posición actual
    int cancionesDisponibles = cantidadReproducidas - 1;

    if (cancionesDisponibles > limite) {
        // Solo podemos retroceder hasta el límite
        // No permitir ir más allá
        return nullptr;
    }

    // Retroceder una posición en el historial
    cantidadReproducidas--;
    return cancionesReproducidas[cantidadReproducidas - 1];
}

bool FuenteReproduccion::hayAnterior() const {
    if (cantidadReproducidas < 2) {
        return false;
    }

    int limite = obtenerLimiteRetroceso();
    int cancionesDisponibles = cantidadReproducidas - 1;

    return cancionesDisponibles <= limite;
}

int FuenteReproduccion::getCancionesRetrocesoPosibles() const {
    int limite = obtenerLimiteRetroceso();
    int disponibles = cantidadReproducidas - 1;

    return (disponibles < limite) ? disponibles : limite;
}

void FuenteReproduccion::setModoAleatorio(bool activar) {
    modoAleatorio = activar;
}

bool FuenteReproduccion::esModoAleatorio() const {
    return modoAleatorio;
}

FuenteReproduccion::TipoFuente FuenteReproduccion::getTipoFuente() const {
    return tipoFuente;
}

int FuenteReproduccion::getCantidadCanciones() const {
    if (tipoFuente == ALEATORIA_SISTEMA) {
        return sistema != nullptr ? sistema->getTotalCanciones() : 0;
    } else {
        return sesionreproduccion != nullptr ? sesionreproduccion->getNumCanciones() : 0;
    }
}

int FuenteReproduccion::getCantidadReproducidas() const {
    return cantidadReproducidas;
}

int FuenteReproduccion::calcularMemoriaUsada() const {
    int total = sizeof(*this);
    total += sizeof(Cancion*) * capacidadReproducidas;
    return total;
}
