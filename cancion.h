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

    // Métodos privados auxiliares
    void redimensionarCreditos();

public:
    // Constructores
    Cancion();
    Cancion(int id, const string& nom, int dur, const string& ubicacion);
    Cancion(const Cancion& otra);  // Constructor de copia

    // Destructor
    ~Cancion();

    // Métodos principales para gestión de créditos
    void agregarCredito(Credito* credito);
    bool eliminarCredito(const string& codigoAfiliacion);
    Credito* buscarCredito(const string& codigoAfiliacion) const;
    Credito** obtenerCreditosPorTipo(int tipo, int& cantidad) const;
    void setCredito(int indice, Credito* credito);
    Credito* getCredito(int indice) const;

    // Métodos para manejo de ID jerárquico
    int extraerIdArtista() const;
    int extraerIdAlbum() const;
    int extraerIdCancion() const;
    bool validarId() const;

    // Métodos de reproducción
    string obtenerRutaAudio(int calidad) const;  // 128 o 320 kbps
    void incrementarReproducciones();

    // Getters
    int getId() const;
    string getNombre() const;
    int getDuracion() const;
    string getUbicacionArchivo() const;
    int getNumCreditos() const;
    int getVecesReproducida() const;
    string getDuracionFormateada() const;  // Retorna formato MM:SS

    // Setters
    void setId(int nuevoId);
    void setNombre(const string& nom);
    void setDuracion(int dur);
    void setUbicacionArchivo(const string& ubicacion);

    // Sobrecarga de operadores
    Cancion& operator=(const Cancion& otra);
    bool operator==(const Cancion& otra) const;
    bool operator==(int idBuscar) const;  // Comparar con ID directamente
    bool operator!=(const Cancion& otra) const;
    bool operator<(const Cancion& otra) const;   // Por reproducciones
    bool operator>(const Cancion& otra) const;   // Por reproducciones

    // Método para medición de memoria
    int calcularMemoriaUsada() const;
};

#endif // CANCION_H
