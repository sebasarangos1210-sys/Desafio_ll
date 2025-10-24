#include "SesionReproduccion.h"
#include <iostream>
using namespace std;

// Generador de números pseudoaleatorios simple
static unsigned int semilla_sesion = 987654321;

static void inicializarSemillaSesion() {
    semilla_sesion = (unsigned int)(long long)&semilla_sesion;
}

static int generarAleatorioSesion(int max) {
    semilla_sesion = semilla_sesion * 1103515245 + 12345;
    return (semilla_sesion / 65536) % max;
}

SesionReproduccion::SesionReproduccion()
    : usuario(nullptr), cancionActual(nullptr), listaReproduccion(nullptr),
    cantidadLista(0), capacidadLista(100), historial(nullptr),
    cantidadHistorial(0), capacidadHistorial(50), indiceActual(0),
    repetir(false), enReproduccion(false), modoAleatorio(false),
    contadorCanciones(0), fuenteAleatoria(nullptr), fuenteFavoritos(nullptr) {

    listaReproduccion = new Cancion*[capacidadLista];
    for (int i = 0; i < capacidadLista; i++) {
        listaReproduccion[i] = nullptr;
    }

    historial = new Cancion*[capacidadHistorial];
    for (int i = 0; i < capacidadHistorial; i++) {
        historial[i] = nullptr;
    }
    inicializarSemillaSesion();
}

SesionReproduccion::SesionReproduccion(Usuario* user)
    : usuario(user), cancionActual(nullptr), listaReproduccion(nullptr),
    cantidadLista(0), capacidadLista(100), historial(nullptr),
    cantidadHistorial(0), capacidadHistorial(50), indiceActual(0),
    repetir(false), enReproduccion(false), modoAleatorio(false),
    contadorCanciones(0), fuenteAleatoria(nullptr), fuenteFavoritos(nullptr) {

    listaReproduccion = new Cancion*[capacidadLista];
    for (int i = 0; i < capacidadLista; i++) {
        listaReproduccion[i] = nullptr;
    }

    historial = new Cancion*[capacidadHistorial];
    for (int i = 0; i < capacidadHistorial; i++) {
        historial[i] = nullptr;
    }
    inicializarSemillaSesion();
}

SesionReproduccion::~SesionReproduccion() {
    if (listaReproduccion != nullptr) {
        delete[] listaReproduccion;
        listaReproduccion = nullptr;
    }

    if (historial != nullptr) {
        delete[] historial;
        historial = nullptr;
    }
}

void SesionReproduccion::redimensionarLista() {
    int nuevaCapacidad = capacidadLista * 2;
    Cancion** nuevoArreglo = new Cancion*[nuevaCapacidad];

    for (int i = 0; i < cantidadLista; i++) {
        nuevoArreglo[i] = listaReproduccion[i];
    }

    for (int i = cantidadLista; i < nuevaCapacidad; i++) {
        nuevoArreglo[i] = nullptr;
    }

    delete[] listaReproduccion;
    listaReproduccion = nuevoArreglo;
    capacidadLista = nuevaCapacidad;
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

    // Si está en modo repetir, no agregar la misma canción múltiples veces
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
    if (cantidadLista == 0 && fuenteAleatoria == nullptr && fuenteFavoritos == nullptr) {
        cout << "No hay canciones para reproducir.\n";
        return;
    }

    enReproduccion = true;
    indiceActual = 0;
    contadorCanciones = 0;

    cout << "REPRODUCCION INICIADA\n";
    if (usuario != nullptr) {
        cout << "Usuario: " << usuario->getNickname() << "\n";
        cout << "Tipo: " << usuario->getTipoMembresiaString() << "\n";
    }
    cout << "Modo: " << (modoAleatorio ? "Aleatorio" : "Secuencial") << "\n";
    cout << "Repetir: " << (repetir ? "Activado" : "Desactivado") << "\n\n";
}

void SesionReproduccion::detener() {
    enReproduccion = false;
    cancionActual = nullptr;

    cout << "\nREPRODUCCION DETENIDA\n";
    cout << "Canciones reproducidas: " << contadorCanciones << "\n";
}

bool SesionReproduccion::siguiente() {
    if (!enReproduccion) {
        cout << "La reproduccion no esta activa. Use iniciar() primero.\n";
        return false;
    }

    // Si está en modo repetir, devolver la misma canción
    if (repetir && cancionActual != nullptr) {
        agregarAlHistorial(cancionActual);
        return true;
    }

    // Obtener siguiente canción según la fuente
    Cancion* siguienteCancion = nullptr;

    if (fuenteAleatoria != nullptr) {
        // Usar fuente aleatoria (todas las canciones del sistema)
        siguienteCancion = fuenteAleatoria->siguienteCancion();
    } else if (fuenteFavoritos != nullptr) {
        // Usar fuente de favoritos
        // Implementar cuando tengas FuenteListaFavoritos
    } else if (cantidadLista > 0) {
        // Usar lista interna
        if (modoAleatorio) {
            indiceActual = generarAleatorioSesion(cantidadLista);
        } else {
            indiceActual++;
            if (indiceActual >= cantidadLista) {
                indiceActual = 0; // Volver al inicio
            }
        }
        siguienteCancion = listaReproduccion[indiceActual];
    }

    if (siguienteCancion != nullptr) {
        cancionActual = siguienteCancion;
        agregarAlHistorial(cancionActual);
        contadorCanciones++;

        // Manejar publicidad si es usuario estándar
        if (usuario != nullptr && !usuario->esPremium() && contadorCanciones % 2 == 0) {
            manejarPublicidad();
        }

        mostrarInterfaz();
        return true;
    }

    return false;
}

bool SesionReproduccion::anterior() {
    if (!enReproduccion) {
        cout << "La reproduccion no esta activa.\n";
        return false;
    }

    if (!puedeRetroceder()) {
        cout << "No se puede retroceder mas.\n";
        return false;
    }

    // Determinar límite de retroceso según usuario
    int maxRetroceso = 4; // Por defecto para aleatorio
    if (fuenteFavoritos != nullptr) {
        maxRetroceso = 6; // Para favoritos
    }

    if (cantidadHistorial > 1) {
        // Retroceder en el historial
        cantidadHistorial--;
        cancionActual = historial[cantidadHistorial - 1];

        mostrarInterfaz();
        return true;
    }

    return false;
}

void SesionReproduccion::establecerFuenteAleatoria(FuenteAleatoria* fuente) {
    fuenteAleatoria = fuente;
    fuenteFavoritos = nullptr; // Desactivar favoritos si se establece aleatoria
}

void SesionReproduccion::establecerFuenteFavoritos(FuenteListaFavoritos* fuente) {
    fuenteFavoritos = fuente;
    fuenteAleatoria = nullptr; // Desactivar aleatoria si se establece favoritos
}

bool SesionReproduccion::agregarALista(Cancion* cancion) {
    if (cancion == nullptr) return false;

    // Verificar duplicados
    for (int i = 0; i < cantidadLista; i++) {
        if (listaReproduccion[i] == cancion) {
            return false; // Ya existe
        }
    }

    if (cantidadLista >= capacidadLista) {
        redimensionarLista();
    }

    listaReproduccion[cantidadLista] = cancion;
    cantidadLista++;
    return true;
}

void SesionReproduccion::mostrarInterfaz() {
    if (cancionActual == nullptr) return;

    cout << "\n----------------------------------------\n";
    cout << "Reproduciendo: " << cancionActual->getNombre() << "\n";
    cout << "Duracion: " << cancionActual->getDuracionFormateada() << "\n";

    if (usuario != nullptr) {
        int calidad = usuario->obtenerCalidadAudio();
        cout << "Calidad: " << calidad << " kbps\n";
        cout << "Audio: " << cancionActual->obtenerRutaAudio(calidad) << "\n";
    }

    cout << "Contador: " << contadorCanciones << "\n";
    cout << "----------------------------------------\n";

    if (usuario != nullptr && usuario->esPremium()) {
        cout << "[OPCIONES] Siguiente | Anterior | Repetir | Detener\n";
    } else {
        cout << "[OPCIONES] Siguiente | Detener\n";
    }
    cout << "\n";
}

void SesionReproduccion::manejarPublicidad() {
    cout << "*          PUBLICIDAD                  *\n";
    cout << "* Disfruta UdeATunes Premium          *\n";
    cout << "* Sin anuncios, calidad 777 kbps       *\n";
    cout << "* Solo 19,900 COP/mes                  *\n";

}

bool SesionReproduccion::puedeRetroceder() {
    if (usuario == nullptr || !usuario->esPremium()) {
        return false; // Solo premium puede retroceder
    }

    int maxRetroceso = 4;
    if (fuenteFavoritos != nullptr) {
        maxRetroceso = 6;
    }

    return cantidadHistorial > 1 && cantidadHistorial <= maxRetroceso + 1;
}

bool SesionReproduccion::haySiguiente() {
    if (repetir) return true; // En modo repetir siempre hay siguiente

    if (fuenteAleatoria != nullptr) {
        return fuenteAleatoria->haySiguiente();
    }

    if (fuenteFavoritos != nullptr) {
        // return fuenteFavoritos->haySiguiente();
        return true; // Temporal hasta implementar FuenteListaFavoritos
    }

    return cantidadLista > 0;
}

// --- GETTERS ---
Usuario* SesionReproduccion::getUsuario() const {
    return usuario;
}

Cancion* SesionReproduccion::getCancionActual() const {
    return cancionActual;
}

bool SesionReproduccion::estaEnReproduccion() const {
    return enReproduccion;
}

bool SesionReproduccion::esModoAleatorio() const {
    return modoAleatorio;
}

bool SesionReproduccion::esModoRepetir() const {
    return repetir;
}

int SesionReproduccion::getContadorCanciones() const {
    return contadorCanciones;
}

// --- SETTERS ---
void SesionReproduccion::setModoAleatorio(bool activar) {
    modoAleatorio = activar;
}

void SesionReproduccion::setModoRepetir(bool activar) {
    repetir = activar;
}

int SesionReproduccion::calcularMemoriaUsada() const {
    int total = sizeof(*this);

    // Memoria de la lista de reproducción
    total += sizeof(Cancion*) * capacidadLista;

    // Memoria del historial
    total += sizeof(Cancion*) * capacidadHistorial;

    // Memoria de las fuentes
    if (fuenteAleatoria != nullptr) {
        total += fuenteAleatoria->calcularMemoriaUsada();
    }

    if (fuenteFavoritos != nullptr) {
        total += fuenteFavoritos->calcularMemoriaUsada();
    }

    return total;
}
