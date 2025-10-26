#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "Cancion.h"
using namespace std;

class Album {
private:
    int id;
    string nombre;
    string fechaLanzamiento;
    int duracionTotal;
    string selloDisquero;
    string portada;
    float puntuacion;
    string* generos;
    int numGeneros;
    int capacidadGeneros;
    Cancion** canciones;
    int numCanciones;
    int capacidadCanciones;

    void redimensionarGeneros();
    void redimensionarCanciones();

public:
    Cancion();
    Album(int id, const string& nom, const string& fecha, const string& sello, const string& portada);
    Album(const Album& otro);
    ~Album();

    void agregarGenero(const string& genero);
    bool eliminarGenero(const string& genero);
    bool tieneGenero(const string& genero) const;

    void agregarCancion(Cancion* cancion);
    bool eliminarCancion(int idCancion);
    Cancion* buscarCancion(int idCancion) const;
    Cancion* buscarCancionPorNombre(const string& nombre) const;

    void calcularDuracionTotal();
    void actualizarPuntuacion(float nuevaPuntuacion);
    bool esValido() const;

    int getId() const;
    string getNombre() const;
    string getFechaLanzamiento() const;
    int getDuracionTotal() const;
    string getSelloDisquero() const;
    string getPortada() const;
    float getPuntuacion() const;
    int getNumGeneros() const;
    int getNumCanciones() const;
    string getDuracionFormateada() const;
    string* getGeneros() const;
    int getCapacidadGeneros() const;
    Cancion** getCanciones() const;
    int getCapacidadCanciones() const;

    void setNombre(const string& nom);
    void setId(int nuevoId);
    void setFechaLanzamiento(const string& fecha);
    void setSelloDisquero(const string& sello);
    void setPortada(const string& port);
    void setPuntuacion(float punt);
    void setDuracionTotal(int duracion);
    void setNumCanciones(int cantidad);
    void setNumGeneros(int cantidad);
    void setGeneros(string* nuevosGeneros, int cantidad);
    void setCanciones(Cancion** nuevasCanciones, int cantidad);

    Album& operator=(const Album& otro);
    bool operator==(const Album& otro) const;
    bool operator==(int idBuscar) const;
    bool operator!=(const Album& otro) const;
    bool operator<(const Album& otro) const;
    bool operator>(const Album& otro) const;
    Cancion* operator[](int indice) const;

    int calcularMemoriaUsada() const;
};

#endif
