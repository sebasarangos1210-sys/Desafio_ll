#ifndef SESIONREPRODUCCION_H
#define SESIONREPRODUCCION_H

#include "Usuario.h"
#include "Cancion.h"
#include "FuenteReproduccion.h"
#include <random>
#include <chrono>

class SesionReproduccion {
private:
    Usuario* usuario;
    Cancion* cancionActual;
    Cancion** historial;
    int cantidadHistorial;
    int capacidadHistorial;
    bool repetir;
    bool enReproduccion;
    int contadorCanciones;
    FuenteReproduccion* fuente;

    std::mt19937 generador;
    std::chrono::steady_clock::time_point tiempoInicio;

    void redimensionarHistorial();
    void agregarAlHistorial(Cancion* cancion);

public:
    SesionReproduccion();
    SesionReproduccion(Usuario* user);
    ~SesionReproduccion();

    void iniciar();
    void detener();
    bool siguiente();
    bool anterior();

    void establecerFuente(FuenteReproduccion* fuenteReproduccion);
    bool puedeRetroceder();
    bool haySiguiente();
    long long obtenerTiempoTranscurrido();

    Usuario* getUsuario() const;
    Cancion* getCancionActual() const;
    bool estaEnReproduccion() const;
    bool esModoRepetir() const;
    int getContadorCanciones() const;
    int getCantidadHistorial() const;
    FuenteReproduccion* getFuente() const;

    void setModoRepetir(bool activar);

    int calcularMemoriaUsada() const;
};

#endif
