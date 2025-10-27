#ifndef SISTEMA_H
#define SISTEMA_H

#include "MensajePublicitario.h"
#include <string>
#include "album.h"
#include "artista.h"
#include "usuario.h"
#include "reproduccion.h"
#include <chrono>
#include <thread>

using namespace std;

class Sistema {

    public:
        Sistema(); //Constructor
        ~Sistema(); //Destructor

        bool Login(const string& Nickname); //Metodo de ingreso al Sistema
        void Log_out(); //Metodo de Salir del Sistema
        //void R_musica(); // Metodo para Modelar la Reproduccion Musical

        void CargarDatos(); //Carga los Datos al Sistema
        void CargarAlbumes(Album* album, string texto);
        void CargarCanciones(Cancion* cancion, string texto, ifstream archivo3);
        void CargarArtistas(Artista* artista, string texto);
        void CargarUsuarios(Usuario* user, string texto);
        void CargarListaFavoritos();
        void agregarcanciones(int& filas, int& columnas, int& tamcanciones, const Cancion* cancion);
        void agregaralbumes(int& filas, int& columnas, int& tamalbumes, const Album* album);
        void agregarartistas(int& filas, int& columnas, int& tamartistas,const Artista* artista);
        void agregarusuarios(int& filas, int& columnas, int& tamusuarios, const Usuario* user);

        bool ComprobarMemb(const Usuario* usuarioactual); //Verifica la Membresia del Usuario
        char reproduccion(Usuario& useractual);
        void reproducir();
        void pausa();
        void buscarUsuario();
        void BuscarCancion();
        void repetir();
        void siguiente();
        void anterior();
        void SalidaPantalla();

        string getusuarioactual() const;
        Usuario* getusuarios() const; //Permite obtener el valor dedl Arreglo de Usuarios
        void setusuarios(Usuario& Usuario); //Ingresa la Informacion al Arreglo de Usuarios
        Album* getalbumes() const;
        void setalbumes(Album& Album); //Ingresa la Informacion al Arreglo de Albumes
        Artista* getartistas() const;
        void setartista(Artista Artista); //Ingresa la Informacion al Arreglo de Artistas
        Cancion* getCanciones() const;
        void setCanciones(Cancion Cancion); //Ingresa la Informacion al Arreglo de Canciones
        MensajePublicitario* getMessage() const;
        void setMessage(MensajePublicitario Mensaje); //Ingresa la Informacion al Arreglo de Mensajes Publicitarios
        Cancion* getR_Canciones() const;
        void setR_Canciones(Cancion Cancion); //Ingresa la Informacion al Arreglo de Canciones Reproducidas

    private:
        std::chrono::steady_clock::time_point inicioReproduccion;
        std::chrono::seconds tiempoAcumulado{0};
        Usuario** usuarios;
        int cantusuarios;
        Usuario* usuarioactual;
        Cancion* cancionactual;
        Album** albumes;
        int cantalbumes;
        Artista** artistas;
        int cantartistas;
        Cancion** canciones;
        int cantcanciones;
        MensajePublicitario* Mensajes;
        Cancion** reproducidas;
        int tamcanciones;
        int tamalbumes;
        int tamartistas;
        int tamusuarios;
        int tiemporeproduccion;
};

#endif // SISTEMA_H
