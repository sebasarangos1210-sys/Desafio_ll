#ifndef FUENTEREPRODUCCION_H
#define FUENTEREPRODUCCION_H

#include "Sistema.h"
#include "Cancion.h"
#include <random>
#include <chrono>

// Forward declaration para evitar inclusiones circulares
class ListaReproduccion;

class FuenteReproduccion {
public:
    enum TipoFuente {
        ALEATORIA_SISTEMA,     // Reproduce todas las canciones del sistema
        LISTA_FAVORITOS,       // Reproduce lista de favoritos del usuario
        LISTA_PERSONALIZADA    // Reproduce lista personalizada
    };

private:
    Sistema* sistema;                   // Referencia al sistema para acceso a canciones
    ListaReproduccion* listaReproduccion; // Lista específica para reproducir
    TipoFuente tipoFuente;              // Tipo de fuente actual

    Cancion** cancionesReproducidas;    // Historial de canciones ya reproducidas
    int cantidadReproducidas;           // Número actual en el historial
    int capacidadReproducidas;          // Capacidad del arreglo historial

    int indiceActual;                   // Índice actual para listas secuenciales
    bool modoAleatorio;                 // true = aleatorio, false = secuencial

    std::mt19937 generador;             // Generador de números aleatorios (C++11)

    // MÉTODOS PRIVADOS
    void redimensionarReproducidas();   // Redimensiona arreglo de reproducidas
    int generarIndiceAleatorio(int max);// Genera índice aleatorio usando <random>
    Cancion* seleccionarCancionAleatoria(); // Selecciona canción aleatoria del sistema
    bool yaFueReproducida(int idCancion);   // Verifica si canción ya fue reproducida

public:
    // CONSTRUCTORES
    FuenteReproduccion();
    FuenteReproduccion(Sistema* sistema);
    FuenteReproduccion(ListaReproduccion* lista);
    ~FuenteReproduccion();

    // CONFIGURACIÓN
    void establecerSistema(Sistema* sistema);
    void establecerListaReproduccion(ListaReproduccion* lista);
    void setModoAleatorio(bool activar);
    void reiniciar();

    // REPRODUCCIÓN
    Cancion* siguienteCancion();
    Cancion* cancionActual() const;
    bool haySiguiente() const;

    // CONSULTAS
    bool esModoAleatorio() const;
    TipoFuente getTipoFuente() const;
    int getCantidadCanciones() const;
    int getCantidadReproducidas() const;

    // MEDICIÓN DE RECURSOS
    int calcularMemoriaUsada() const;
};

#endif

#endif
