#include "Cancion.h"
#include <sstream>
#include <iomanip>

// Constructor por defecto
Cancion::Cancion()
    : id(0), nombre(""), duracion(0), ubicacionArchivo(""),
    creditos(nullptr), numCreditos(0), capacidadCreditos(5), vecesReproducida(0) {
    creditos = new Credito*[capacidadCreditos];
    for (int i = 0; i < capacidadCreditos; i++) {
        creditos[i] = nullptr;
    }
}

// Constructor parametrizado
Cancion::Cancion(int id, const string& nom, int dur, const string& ubicacion)
    : id(id), nombre(nom), duracion(dur), ubicacionArchivo(ubicacion),
    creditos(nullptr), numCreditos(0), capacidadCreditos(5), vecesReproducida(0) {
    creditos = new Credito*[capacidadCreditos];
    for (int i = 0; i < capacidadCreditos; i++) {
        creditos[i] = nullptr;
    }
}

// Constructor de copia
Cancion::Cancion(const Cancion& otra)
    : id(otra.id), nombre(otra.nombre), duracion(otra.duracion),
    ubicacionArchivo(otra.ubicacionArchivo), numCreditos(otra.numCreditos),
    capacidadCreditos(otra.capacidadCreditos), vecesReproducida(otra.vecesReproducida) {

    // Copia profunda del arreglo de créditos
    creditos = new Credito*[capacidadCreditos];
    for (int i = 0; i < capacidadCreditos; i++) {
        if (i < numCreditos && otra.creditos[i] != nullptr) {
            creditos[i] = new Credito(*(otra.creditos[i]));
        } else {
            creditos[i] = nullptr;
        }
    }
}

// Destructor
Cancion::~Cancion() {
    if (creditos != nullptr) {
        for (int i = 0; i < numCreditos; i++) {
            if (creditos[i] != nullptr) {
                delete creditos[i];
                creditos[i] = nullptr;
            }
        }
        delete[] creditos;
        creditos = nullptr;
    }
}

// Redimensionar arreglo de créditos cuando se llena
void Cancion::redimensionarCreditos() {
    int nuevaCapacidad = capacidadCreditos * 2;
    Credito** nuevoArreglo = new Credito*[nuevaCapacidad];

    // Copiar créditos existentes
    for (int i = 0; i < numCreditos; i++) {
        nuevoArreglo[i] = creditos[i];
    }

    // Inicializar nuevos espacios
    for (int i = numCreditos; i < nuevaCapacidad; i++) {
        nuevoArreglo[i] = nullptr;
    }

    // Liberar arreglo antiguo y actualizar
    delete[] creditos;
    creditos = nuevoArreglo;
    capacidadCreditos = nuevaCapacidad;
}

// Agregar un crédito a la canción
void Cancion::agregarCredito(Credito* credito) {
    if (credito == nullptr || !credito->esValido()) {
        return;
    }

    // Verificar si ya existe (no duplicar)
    for (int i = 0; i < numCreditos; i++) {
        if (creditos[i] != nullptr && *creditos[i] == *credito) {
            return; // Ya existe
        }
    }

    // Redimensionar si es necesario
    if (numCreditos >= capacidadCreditos) {
        redimensionarCreditos();
    }

    // Agregar nuevo crédito (copia profunda)
    creditos[numCreditos] = new Credito(*credito);
    numCreditos++;
}

// Eliminar un crédito por código de afiliación
bool Cancion::eliminarCredito(const string& codigoAfiliacion) {
    for (int i = 0; i < numCreditos; i++) {
        if (creditos[i] != nullptr &&
            creditos[i]->getCodigoAfiliacion() == codigoAfiliacion) {

            // Eliminar el crédito
            delete creditos[i];

            // Desplazar los elementos restantes
            for (int j = i; j < numCreditos - 1; j++) {
                creditos[j] = creditos[j + 1];
            }
            creditos[numCreditos - 1] = nullptr;
            numCreditos--;
            return true;
        }
    }
    return false;
}

// Buscar un crédito por código de afiliación
Credito* Cancion::buscarCredito(const string& codigoAfiliacion) const {
    for (int i = 0; i < numCreditos; i++) {
        if (creditos[i] != nullptr &&
            creditos[i]->getCodigoAfiliacion() == codigoAfiliacion) {
            return creditos[i];
        }
    }
    return nullptr;
}

// Obtener créditos por tipo ("Productor", "Musico", "Compositor")
Credito** Cancion::obtenerCreditosPorTipo(const string& tipo, int& cantidad) const {
    // Contar cuántos hay de ese tipo
    cantidad = 0;
    for (int i = 0; i < numCreditos; i++) {
        if (creditos[i] != nullptr && creditos[i]->getTipoCredito() == tipo) {
            cantidad++;
        }
    }

    if (cantidad == 0) {
        return nullptr;
    }

    // Crear arreglo con los créditos de ese tipo
    Credito** resultado = new Credito*[cantidad];
    int indice = 0;
    for (int i = 0; i < numCreditos; i++) {
        if (creditos[i] != nullptr && creditos[i]->getTipoCredito() == tipo) {
            resultado[indice] = creditos[i];
            indice++;
        }
    }

    return resultado;
}

// Establecer un crédito en una posición específica
void Cancion::setCredito(int indice, Credito* credito) {
    if (indice < 0 || indice >= numCreditos || credito == nullptr) {
        return;
    }

    if (creditos[indice] != nullptr) {
        delete creditos[indice];
    }

    creditos[indice] = new Credito(*credito);
}

// Obtener un crédito por índice
Credito* Cancion::getCredito(int indice) const {
    if (indice >= 0 && indice < numCreditos) {
        return creditos[indice];
    }
    return nullptr;
}

// Obtener todos los créditos
Credito** Cancion::getCreditos() const {
    return creditos;
}

int Cancion::getCapacidadCreditos() const {
    return capacidadCreditos;
}

// Establecer todos los créditos
void Cancion::setCreditos(Credito** nuevosCreditos, int cantidad) {
    if (nuevosCreditos == nullptr || cantidad < 0) {
        return;
    }

    // Limpiar créditos existentes
    for (int i = 0; i < numCreditos; i++) {
        if (creditos[i] != nullptr) {
            delete creditos[i];
            creditos[i] = nullptr;
        }
    }
    numCreditos = 0;

    // Agregar nuevos créditos
    for (int i = 0; i < cantidad; i++) {
        if (nuevosCreditos[i] != nullptr) {
            agregarCredito(nuevosCreditos[i]);
        }
    }
}

// Extraer ID del artista (primeros 5 dígitos)
int Cancion::extraerIdArtista() const {
    return id / 10000;  // Divide entre 10^4 para obtener primeros 5 dígitos
}

// Extraer ID del álbum (dígitos 6-7)
int Cancion::extraerIdAlbum() const {
    return (id / 100) % 100;  // Obtiene los dígitos del medio
}

// Extraer ID de la canción (últimos 2 dígitos)
int Cancion::extraerIdCancion() const {
    return id % 100;  // Módulo 100 para últimos 2 dígitos
}

// Validar que el ID tenga exactamente 9 dígitos
bool Cancion::validarId() const {
    return id >= 100000000 && id <= 999999999;
}

// Obtener ruta del archivo de audio según calidad
string Cancion::obtenerRutaAudio(int calidad) const {
    if (calidad != 128 && calidad != 320) {
        calidad = 128;  // Por defecto 128 kbps
    }

    // Formato: ubicacion_base_128.ogg o ubicacion_base_320.ogg
    stringstream ss;
    ss << ubicacionArchivo << "_" << calidad << ".ogg";
    return ss.str();
}

// Incrementar contador de reproducciones
void Cancion::incrementarReproducciones() {
    vecesReproducida++;
}

// --- GETTERS ---
int Cancion::getId() const {
    return id;
}

string Cancion::getNombre() const {
    return nombre;
}

int Cancion::getDuracion() const {
    return duracion;
}

string Cancion::getUbicacionArchivo() const {
    return ubicacionArchivo;
}

int Cancion::getNumCreditos() const {
    return numCreditos;
}

int Cancion::getVecesReproducida() const {
    return vecesReproducida;
}

// Obtener duración en formato MM:SS
string Cancion::getDuracionFormateada() const {
    int minutos = duracion / 60;
    int segundos = duracion % 60;

    stringstream ss;
    ss << minutos << ":" << setfill('0') << setw(2) << segundos;
    return ss.str();
}

// --- SETTERS ---
void Cancion::setId(int nuevoId) {
    id = nuevoId;
}

void Cancion::setNombre(const string& nom) {
    nombre = nom;
}

void Cancion::setDuracion(int dur) {
    if (dur > 0) {
        duracion = dur;
    }
}

void Cancion::setUbicacionArchivo(const string& ubicacion) {
    ubicacionArchivo = ubicacion;
}

void Cancion::setVecesReproducida(int cantidad) {
    if (cantidad >= 0) {
        vecesReproducida = cantidad;
    }
}

void Cancion::setNumCreditos(int cantidad) {
    if (cantidad >= 0) {
        numCreditos = cantidad;
    }
}

// --- SOBRECARGA DE OPERADORES ---

// Operador de asignación
Cancion& Cancion::operator=(const Cancion& otra) {
    if (this != &otra) {
        // Liberar memoria existente
        if (creditos != nullptr) {
            for (int i = 0; i < numCreditos; i++) {
                if (creditos[i] != nullptr) {
                    delete creditos[i];
                }
            }
            delete[] creditos;
        }

        // Copiar atributos básicos
        id = otra.id;
        nombre = otra.nombre;
        duracion = otra.duracion;
        ubicacionArchivo = otra.ubicacionArchivo;
        numCreditos = otra.numCreditos;
        capacidadCreditos = otra.capacidadCreditos;
        vecesReproducida = otra.vecesReproducida;

        // Copia profunda del arreglo de créditos
        creditos = new Credito*[capacidadCreditos];
        for (int i = 0; i < capacidadCreditos; i++) {
            if (i < numCreditos && otra.creditos[i] != nullptr) {
                creditos[i] = new Credito(*(otra.creditos[i]));
            } else {
                creditos[i] = nullptr;
            }
        }
    }
    return *this;
}

// Comparar canciones por ID
bool Cancion::operator==(const Cancion& otra) const {
    return id == otra.id;
}

// Comparar canción con ID directamente (útil para búsquedas)
bool Cancion::operator==(int idBuscar) const {
    return id == idBuscar;
}

// Operador diferente
bool Cancion::operator!=(const Cancion& otra) const {
    return id != otra.id;
}

// Comparar por número de reproducciones (menor)
bool Cancion::operator<(const Cancion& otra) const {
    return vecesReproducida < otra.vecesReproducida;
}

// Comparar por número de reproducciones (mayor)
bool Cancion::operator>(const Cancion& otra) const {
    return vecesReproducida > otra.vecesReproducida;
}

// Calcular memoria usada
int Cancion::calcularMemoriaUsada() const {
    int total = sizeof(*this);

    // Memoria de strings
    total += nombre.length();
    total += ubicacionArchivo.length();

    // Memoria del arreglo de créditos
    total += sizeof(Credito*) * capacidadCreditos;

    // Memoria de cada crédito
    for (int i = 0; i < numCreditos; i++) {
        if (creditos[i] != nullptr) {
            total += creditos[i]->calcularMemoriaUsada();
        }
    }

    return total;
}

