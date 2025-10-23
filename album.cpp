#include "Album.h"
#include <sstream>
#include <iomanip>

Album::Album()
    : id(0), nombre(""), fechaLanzamiento(""), duracionTotal(0),
    selloDisquero(""), portada(""), puntuacion(0.0f),
    generos(nullptr), numGeneros(0), capacidadGeneros(4),
    canciones(nullptr), numCanciones(0), capacidadCanciones(10) {
    generos = new string[capacidadGeneros];
    canciones = new Cancion*[capacidadCanciones];
    for (int i = 0; i < capacidadCanciones; i++) {
        canciones[i] = nullptr;
    }
}

Album::Album(int id, const string& nom, const string& fecha, const string& sello, const string& port)
    : id(id), nombre(nom), fechaLanzamiento(fecha), duracionTotal(0),
    selloDisquero(sello), portada(port), puntuacion(0.0f),
    generos(nullptr), numGeneros(0), capacidadGeneros(4),
    canciones(nullptr), numCanciones(0), capacidadCanciones(10) {
    generos = new string[capacidadGeneros];
    canciones = new Cancion*[capacidadCanciones];
    for (int i = 0; i < capacidadCanciones; i++) {
        canciones[i] = nullptr;
    }
}

Album::Album(const Album& otro)
    : id(otro.id), nombre(otro.nombre), fechaLanzamiento(otro.fechaLanzamiento),
    duracionTotal(otro.duracionTotal), selloDisquero(otro.selloDisquero),
    portada(otro.portada), puntuacion(otro.puntuacion),
    numGeneros(otro.numGeneros), capacidadGeneros(otro.capacidadGeneros),
    numCanciones(otro.numCanciones), capacidadCanciones(otro.capacidadCanciones) {

    generos = new string[capacidadGeneros];
    for (int i = 0; i < numGeneros; i++) {
        generos[i] = otro.generos[i];
    }

    canciones = new Cancion*[capacidadCanciones];
    for (int i = 0; i < capacidadCanciones; i++) {
        if (i < numCanciones && otro.canciones[i] != nullptr) {
            canciones[i] = new Cancion(*(otro.canciones[i]));
        } else {
            canciones[i] = nullptr;
        }
    }
}

Album::~Album() {
    if (generos != nullptr) {
        delete[] generos;
        generos = nullptr;
    }

    if (canciones != nullptr) {
        for (int i = 0; i < numCanciones; i++) {
            if (canciones[i] != nullptr) {
                delete canciones[i];
                canciones[i] = nullptr;
            }
        }
        delete[] canciones;
        canciones = nullptr;
    }
}

void Album::redimensionarGeneros() {
    int nuevaCapacidad = capacidadGeneros * 2;
    string* nuevoArreglo = new string[nuevaCapacidad];

    for (int i = 0; i < numGeneros; i++) {
        nuevoArreglo[i] = generos[i];
    }

    delete[] generos;
    generos = nuevoArreglo;
    capacidadGeneros = nuevaCapacidad;
}

void Album::redimensionarCanciones() {
    int nuevaCapacidad = capacidadCanciones * 2;
    Cancion** nuevoArreglo = new Cancion*[nuevaCapacidad];

    for (int i = 0; i < numCanciones; i++) {
        nuevoArreglo[i] = canciones[i];
    }

    for (int i = numCanciones; i < nuevaCapacidad; i++) {
        nuevoArreglo[i] = nullptr;
    }

    delete[] canciones;
    canciones = nuevoArreglo;
    capacidadCanciones = nuevaCapacidad;
}

void Album::agregarGenero(const string& genero) {
    if (numGeneros >= 4) {
        return;
    }

    if (tieneGenero(genero)) {
        return;
    }

    if (numGeneros >= capacidadGeneros) {
        redimensionarGeneros();
    }

    generos[numGeneros] = genero;
    numGeneros++;
}

bool Album::eliminarGenero(const string& genero) {
    for (int i = 0; i < numGeneros; i++) {
        if (generos[i] == genero) {
            for (int j = i; j < numGeneros - 1; j++) {
                generos[j] = generos[j + 1];
            }
            numGeneros--;
            return true;
        }
    }
    return false;
}

bool Album::tieneGenero(const string& genero) const {
    for (int i = 0; i < numGeneros; i++) {
        if (generos[i] == genero) {
            return true;
        }
    }
    return false;
}

void Album::agregarCancion(Cancion* cancion) {
    if (cancion == nullptr) {
        return;
    }

    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i] != nullptr && *canciones[i] == *cancion) {
            return;
        }
    }

    if (numCanciones >= capacidadCanciones) {
        redimensionarCanciones();
    }

    canciones[numCanciones] = new Cancion(*cancion);
    numCanciones++;
    calcularDuracionTotal();
}

bool Album::eliminarCancion(int idCancion) {
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i] != nullptr && canciones[i]->getId() == idCancion) {
            delete canciones[i];

            for (int j = i; j < numCanciones - 1; j++) {
                canciones[j] = canciones[j + 1];
            }
            canciones[numCanciones - 1] = nullptr;
            numCanciones--;
            calcularDuracionTotal();
            return true;
        }
    }
    return false;
}

Cancion* Album::buscarCancion(int idCancion) const {
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i] != nullptr && canciones[i]->getId() == idCancion) {
            return canciones[i];
        }
    }
    return nullptr;
}

Cancion* Album::buscarCancionPorNombre(const string& nombre) const {
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i] != nullptr && canciones[i]->getNombre() == nombre) {
            return canciones[i];
        }
    }
    return nullptr;
}

void Album::calcularDuracionTotal() {
    duracionTotal = 0;
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i] != nullptr) {
            duracionTotal += canciones[i]->getDuracion();
        }
    }
}

void Album::actualizarPuntuacion(float nuevaPuntuacion) {
    if (nuevaPuntuacion >= 1.0f && nuevaPuntuacion <= 10.0f) {
        puntuacion = nuevaPuntuacion;
    }
}

bool Album::esValido() const {
    return id > 0 && !nombre.empty() && numCanciones > 0;
}

int Album::getId() const {
    return id;
}

string Album::getNombre() const {
    return nombre;
}

string Album::getFechaLanzamiento() const {
    return fechaLanzamiento;
}

int Album::getDuracionTotal() const {
    return duracionTotal;
}

string Album::getSelloDisquero() const {
    return selloDisquero;
}

string Album::getPortada() const {
    return portada;
}

float Album::getPuntuacion() const {
    return puntuacion;
}

int Album::getNumGeneros() const {
    return numGeneros;
}

int Album::getNumCanciones() const {
    return numCanciones;
}

string Album::getDuracionFormateada() const {
    int horas = duracionTotal / 3600;
    int minutos = (duracionTotal % 3600) / 60;
    int segundos = duracionTotal % 60;

    stringstream ss;
    if (horas > 0) {
        ss << horas << ":" << setfill('0') << setw(2) << minutos << ":" << setw(2) << segundos;
    } else {
        ss << minutos << ":" << setfill('0') << setw(2) << segundos;
    }
    return ss.str();
}

string* Album::getGeneros() const {
    if (numGeneros == 0) {
        return nullptr;
    }
    string* copia = new string[numGeneros];
    for (int i = 0; i < numGeneros; i++) {
        copia[i] = generos[i];
    }
    return copia;
}

void Album::setNombre(const string& nom) {
    nombre = nom;
}

void Album::setFechaLanzamiento(const string& fecha) {
    fechaLanzamiento = fecha;
}

void Album::setSelloDisquero(const string& sello) {
    selloDisquero = sello;
}

void Album::setPortada(const string& port) {
    portada = port;
}

void Album::setPuntuacion(float punt) {
    if (punt >= 1.0f && punt <= 10.0f) {
        puntuacion = punt;
    }
}

Album& Album::operator=(const Album& otro) {
    if (this != &otro) {
        if (generos != nullptr) {
            delete[] generos;
        }

        if (canciones != nullptr) {
            for (int i = 0; i < numCanciones; i++) {
                if (canciones[i] != nullptr) {
                    delete canciones[i];
                }
            }
            delete[] canciones;
        }

        id = otro.id;
        nombre = otro.nombre;
        fechaLanzamiento = otro.fechaLanzamiento;
        duracionTotal = otro.duracionTotal;
        selloDisquero = otro.selloDisquero;
        portada = otro.portada;
        puntuacion = otro.puntuacion;
        numGeneros = otro.numGeneros;
        capacidadGeneros = otro.capacidadGeneros;
        numCanciones = otro.numCanciones;
        capacidadCanciones = otro.capacidadCanciones;

        generos = new string[capacidadGeneros];
        for (int i = 0; i < numGeneros; i++) {
            generos[i] = otro.generos[i];
        }

        canciones = new Cancion*[capacidadCanciones];
        for (int i = 0; i < capacidadCanciones; i++) {
            if (i < numCanciones && otro.canciones[i] != nullptr) {
                canciones[i] = new Cancion(*(otro.canciones[i]));
            } else {
                canciones[i] = nullptr;
            }
        }
    }
    return *this;
}

bool Album::operator==(const Album& otro) const {
    return id == otro.id;
}

bool Album::operator==(int idBuscar) const {
    return id == idBuscar;
}

bool Album::operator!=(const Album& otro) const {
    return id != otro.id;
}

bool Album::operator<(const Album& otro) const {
    return puntuacion < otro.puntuacion;
}

bool Album::operator>(const Album& otro) const {
    return puntuacion > otro.puntuacion;
}

Cancion* Album::operator[](int indice) const {
    if (indice >= 0 && indice < numCanciones) {
        return canciones[indice];
    }
    return nullptr;
}

int Album::calcularMemoriaUsada() const {
    int total = sizeof(*this);
    total += nombre.capacity();
    total += fechaLanzamiento.capacity();
    total += selloDisquero.capacity();
    total += portada.capacity();

    total += sizeof(string) * capacidadGeneros;
    for (int i = 0; i < numGeneros; i++) {
        total += generos[i].capacity();
    }

    total += sizeof(Cancion*) * capacidadCanciones;
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i] != nullptr) {
            total += canciones[i]->calcularMemoriaUsada();
        }
    }

    return total;
}
