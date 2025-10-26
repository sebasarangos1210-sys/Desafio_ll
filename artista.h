#ifndef ARTISTA_H
#define ARTISTA_H

#include <string>
#include "Album.h"
using namespace std;

class Artista {
private:
    int id;
    int edad;
    string paisOrigen;
    int seguidores;
    int posicionTendencia;
    Album** albumes;
    int numAlbumes;
    int capacidadAlbumes;

    void redimensionarAlbumes();

public:
    Artista();
    Artista(int id, int edad, const string& pais);
    Artista(const Artista& otro);
    ~Artista();

    void agregarAlbum(Album* album);
    bool eliminarAlbum(int idAlbum);
    Album* buscarAlbum(int idAlbum) const;
    Album* buscarAlbumPorNombre(const string& nombre) const;

    Cancion** obtenerTodasCanciones(int& cantidadTotal) const;
    Cancion* buscarCancion(int idCancion) const;

    void incrementarSeguidores();
    void decrementarSeguidores();
    void actualizarPosicionTendencia(int nuevaPosicion);
    bool esValido() const;

    int getId() const;
    int getEdad() const;
    string getPaisOrigen() const;
    int getSeguidores() const;
    int getPosicionTendencia() const;
    int getNumAlbumes() const;
    int getTotalCanciones() const;
    Album** getAlbumes() const;
    int getCapacidadAlbumes() const;

    void setEdad(int nuevaEdad);
    void setId(int nuevoId);
    void setPaisOrigen(const string& pais);
    void setPosicionTendencia(int posicion);
    void setSeguidores(int numSeguidores);
    void setNumAlbumes(int cantidad);
    void setAlbumes(Album** nuevosAlbumes, int cantidad);

    Artista& operator=(const Artista& otro);
    bool operator==(const Artista& otro) const;
    bool operator==(int idBuscar) const;
    bool operator!=(const Artista& otro) const;
    bool operator<(const Artista& otro) const;
    bool operator>(const Artista& otro) const;
    Artista& operator++();
    Artista operator++(int);
    Album* operator[](int indice) const;

    int calcularMemoriaUsada() const;
};

#endif
