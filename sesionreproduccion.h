#ifndef SESIONREPRODUCCION_H
#define SESIONREPRODUCCION_H

#include "Usuario.h"
#include "Cancion.h"
#include "FuenteAleatoria.h"

// evitar dependencia circular
class FuenteListaFavoritos;

class SesionReproduccion {
private:
    Usuario* usuario;
    Cancion* cancionActual;
    Cancion** listaReproduccion;
    int cantidadLista;
    int capacidadLista;
    Cancion** historial;
    int cantidadHistorial;
    int capacidadHistorial;
    int indiceActual;
    bool repetir;
    bool enReproduccion;
    bool modoAleatorio;
    int contadorCanciones;
    FuenteAleatoria* fuenteAleatoria;
    FuenteListaFavoritos* fuenteFavoritos;

    void redimensionarLista();
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

    void establecerFuenteAleatoria(FuenteAleatoria* fuente);
    void establecerFuenteFavoritos(FuenteListaFavoritos* fuente);

    bool agregarALista(Cancion* cancion);
    void mostrarInterfaz();
    void manejarPublicidad();
    bool puedeRetroceder();
    bool haySiguiente();

    // Getters
    Usuario* getUsuario() const;
    Cancion* getCancionActual() const;
    bool estaEnReproduccion() const;
    bool esModoAleatorio() const;
    bool esModoRepetir() const;
    int getContadorCanciones() const;

    // Setters
    void setModoAleatorio(bool activar);
    void setModoRepetir(bool activar);

    int calcularMemoriaUsada() const;
};

#endif
