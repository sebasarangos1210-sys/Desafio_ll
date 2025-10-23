#ifndef CANCION_H
#define CANCION_H

#include <string>
#include "Credito.h"
using namespace std;

class Cancion {
private:
    int id;
    string nombre;
    int duracion;
    string ubicacionArchivo;
    Credito** creditos;
    int numCreditos;
    int capacidadCreditos;
    int vecesReproducida;

    void redimensionarCreditos();

public:
    Cancion();
    Cancion(int id, const string& nom, int dur, const string& ubicacion);
    Cancion(const Cancion& otra);
    ~Cancion();

    void agregarCredito(Credito* credito);
    bool eliminarCredito(const string& codigoAfiliacion);
    Credito* buscarCredito(const string& codigoAfiliacion) const;
    Credito** obtenerCreditosPorTipo(int tipo, int& cantidad) const;

    int extraerIdArtista() const;
    int extraerIdAlbum() const;
    int extraerIdCancion() const;
    bool validarId() const;

    string obtenerRutaAudio(int calidad) const;
    void incrementarReproducciones();

    int getId() const;
    string getNombre() const;
    int getDuracion() const;
    string getUbicacionArchivo() const;
    int getNumCreditos() const;
    int getVecesReproducida() const;
    string getDuracionFormateada() const;

    void setNombre(const string& nom);
    void setDuracion(int dur);
    void setUbicacionArchivo(const string& ubicacion);

    Cancion& operator=(const Cancion& otra);
    bool operator==(const Cancion& otra) const;
    bool operator==(int idBuscar) const;
    bool operator!=(const Cancion& otra) const;
    bool operator<(const Cancion& otra) const;
    bool operator>(const Cancion& otra) const;

    int calcularMemoriaUsada() const;
};

#endif
