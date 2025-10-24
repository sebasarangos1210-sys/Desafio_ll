#include "Artista.h"

Artista::Artista()
    : id(0), edad(0), paisOrigen(""), seguidores(0), posicionTendencia(0),
    albumes(nullptr), numAlbumes(0), capacidadAlbumes(5) {
    albumes = new Album*[capacidadAlbumes];
    for (int i = 0; i < capacidadAlbumes; i++) {
        albumes[i] = nullptr;
    }
}

Artista::Artista(int id, int edad, const string& pais)
    : id(id), edad(edad), paisOrigen(pais), seguidores(0), posicionTendencia(0),
    albumes(nullptr), numAlbumes(0), capacidadAlbumes(5) {
    albumes = new Album*[capacidadAlbumes];
    for (int i = 0; i < capacidadAlbumes; i++) {
        albumes[i] = nullptr;
    }
}

Artista::Artista(const Artista& otro)
    : id(otro.id), edad(otro.edad), paisOrigen(otro.paisOrigen),
    seguidores(otro.seguidores), posicionTendencia(otro.posicionTendencia),
    numAlbumes(otro.numAlbumes), capacidadAlbumes(otro.capacidadAlbumes) {

    albumes = new Album*[capacidadAlbumes];
    for (int i = 0; i < capacidadAlbumes; i++) {
        if (i < numAlbumes && otro.albumes[i] != nullptr) {
            albumes[i] = new Album(*(otro.albumes[i]));
        } else {
            albumes[i] = nullptr;
        }
    }
}

Artista::~Artista() {
    if (albumes != nullptr) {
        for (int i = 0; i < numAlbumes; i++) {
            if (albumes[i] != nullptr) {
                delete albumes[i];
                albumes[i] = nullptr;
            }
        }
        delete[] albumes;
        albumes = nullptr;
    }
}

void Artista::redimensionarAlbumes() {
    int nuevaCapacidad = capacidadAlbumes * 2;
    Album** nuevoArreglo = new Album*[nuevaCapacidad];

    for (int i = 0; i < numAlbumes; i++) {
        nuevoArreglo[i] = albumes[i];
    }

    for (int i = numAlbumes; i < nuevaCapacidad; i++) {
        nuevoArreglo[i] = nullptr;
    }

    delete[] albumes;
    albumes = nuevoArreglo;
    capacidadAlbumes = nuevaCapacidad;
}

void Artista::agregarAlbum(Album* album) {
    if (album == nullptr || !album->esValido()) {
        return;
    }

    for (int i = 0; i < numAlbumes; i++) {
        if (albumes[i] != nullptr && *albumes[i] == *album) {
            return;
        }
    }

    if (numAlbumes >= capacidadAlbumes) {
        redimensionarAlbumes();
    }

    albumes[numAlbumes] = new Album(*album);
    numAlbumes++;
}

bool Artista::eliminarAlbum(int idAlbum) {
    for (int i = 0; i < numAlbumes; i++) {
        if (albumes[i] != nullptr && albumes[i]->getId() == idAlbum) {
            delete albumes[i];

            for (int j = i; j < numAlbumes - 1; j++) {
                albumes[j] = albumes[j + 1];
            }
            albumes[numAlbumes - 1] = nullptr;
            numAlbumes--;
            return true;
        }
    }
    return false;
}

Album* Artista::buscarAlbum(int idAlbum) const {
    for (int i = 0; i < numAlbumes; i++) {
        if (albumes[i] != nullptr && albumes[i]->getId() == idAlbum) {
            return albumes[i];
        }
    }
    return nullptr;
}

Album* Artista::buscarAlbumPorNombre(const string& nombre) const {
    for (int i = 0; i < numAlbumes; i++) {
        if (albumes[i] != nullptr && albumes[i]->getNombre() == nombre) {
            return albumes[i];
        }
    }
    return nullptr;
}

Cancion** Artista::obtenerTodasCanciones(int& cantidadTotal) const {
    cantidadTotal = 0;

    for (int i = 0; i < numAlbumes; i++) {
        if (albumes[i] != nullptr) {
            cantidadTotal += albumes[i]->getNumCanciones();
        }
    }

    if (cantidadTotal == 0) {
        return nullptr;
    }

    Cancion** todasCanciones = new Cancion*[cantidadTotal];
    int indice = 0;

    for (int i = 0; i < numAlbumes; i++) {
        if (albumes[i] != nullptr) {
            int numCancionesAlbum = albumes[i]->getNumCanciones();
            for (int j = 0; j < numCancionesAlbum; j++) {
                todasCanciones[indice] = (*albumes[i])[j];
                indice++;
            }
        }
    }

    return todasCanciones;
}

Cancion* Artista::buscarCancion(int idCancion) const {
    for (int i = 0; i < numAlbumes; i++) {
        if (albumes[i] != nullptr) {
            Cancion* cancion = albumes[i]->buscarCancion(idCancion);
            if (cancion != nullptr) {
                return cancion;
            }
        }
    }
    return nullptr;
}

void Artista::incrementarSeguidores() {
    seguidores++;
}

void Artista::decrementarSeguidores() {
    if (seguidores > 0) {
        seguidores--;
    }
}

void Artista::actualizarPosicionTendencia(int nuevaPosicion) {
    if (nuevaPosicion > 0) {
        posicionTendencia = nuevaPosicion;
    }
}

bool Artista::esValido() const {
    return id > 0 && edad > 0 && !paisOrigen.empty();
}

int Artista::getId() const {
    return id;
}

int Artista::getEdad() const {
    return edad;
}

string Artista::getPaisOrigen() const {
    return paisOrigen;
}

int Artista::getSeguidores() const {
    return seguidores;
}

int Artista::getPosicionTendencia() const {
    return posicionTendencia;
}

int Artista::getNumAlbumes() const {
    return numAlbumes;
}

int Artista::getTotalCanciones() const {
    int total = 0;
    for (int i = 0; i < numAlbumes; i++) {
        if (albumes[i] != nullptr) {
            total += albumes[i]->getNumCanciones();
        }
    }
    return total;
}

void Artista::setEdad(int nuevaEdad) {
    if (nuevaEdad > 0) {
        edad = nuevaEdad;
    }
}

void Artista::setId(int nuevoId) {
    id = nuevoId;
}

void Artista::setPaisOrigen(const string& pais) {
    if (!pais.empty()) {
        paisOrigen = pais;
    }
}

void Artista::setPosicionTendencia(int posicion) {
    if (posicion > 0) {
        posicionTendencia = posicion;
    }
}

Artista& Artista::operator=(const Artista& otro) {
    if (this != &otro) {
        if (albumes != nullptr) {
            for (int i = 0; i < numAlbumes; i++) {
                if (albumes[i] != nullptr) {
                    delete albumes[i];
                }
            }
            delete[] albumes;
        }

        id = otro.id;
        edad = otro.edad;
        paisOrigen = otro.paisOrigen;
        seguidores = otro.seguidores;
        posicionTendencia = otro.posicionTendencia;
        numAlbumes = otro.numAlbumes;
        capacidadAlbumes = otro.capacidadAlbumes;

        albumes = new Album*[capacidadAlbumes];
        for (int i = 0; i < capacidadAlbumes; i++) {
            if (i < numAlbumes && otro.albumes[i] != nullptr) {
                albumes[i] = new Album(*(otro.albumes[i]));
            } else {
                albumes[i] = nullptr;
            }
        }
    }
    return *this;
}

bool Artista::operator==(const Artista& otro) const {
    return id == otro.id;
}

bool Artista::operator==(int idBuscar) const {
    return id == idBuscar;
}

bool Artista::operator!=(const Artista& otro) const {
    return id != otro.id;
}

bool Artista::operator<(const Artista& otro) const {
    if (posicionTendencia == 0) return false;
    if (otro.posicionTendencia == 0) return true;
    return posicionTendencia > otro.posicionTendencia;
}

bool Artista::operator>(const Artista& otro) const {
    if (posicionTendencia == 0) return true;
    if (otro.posicionTendencia == 0) return false;
    return posicionTendencia < otro.posicionTendencia;
}

Artista& Artista::operator++() {
    incrementarSeguidores();
    return *this;
}

Artista Artista::operator++(int) {
    Artista temp = *this;
    incrementarSeguidores();
    return temp;
}

Album* Artista::operator[](int indice) const {
    if (indice >= 0 && indice < numAlbumes) {
        return albumes[indice];
    }
    return nullptr;
}

int Artista::calcularMemoriaUsada() const {
    int total = sizeof(*this);
    total += paisOrigen.length();

    total += sizeof(Album*) * capacidadAlbumes;

    for (int i = 0; i < numAlbumes; i++) {
        if (albumes[i] != nullptr) {
            total += albumes[i]->calcularMemoriaUsada();
        }
    }

    return total;
}
