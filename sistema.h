#ifndef SISTEMA_H
#define SISTEMA_H

#include "MensajePublicitario.h"
#include "album.h"
#include "usuario.h"
#include "reproduccion.h"

using namespace std;

class Sistema {

    public:
        Sistema(); //Constructor
        usuario* Login(const string& Nickname); //Metodo de ingreso al Sistema
        void Log_out(); //Metodo de Salir del Sistema
        //void R_musica(); // Metodo para Modelar la Reproduccion Musical
        void CargarDatos(); //Carga los Datos al Sistema
        bool ComprobarMemb(const usuario& usuario); //Verifica la Membresia del Usuario
        //void interaccion(); //Modela las Operaciones Premium
        void salida_pant(); //Imprime en Pantalla la Consola de Reproducción
        usuario* getusuarios() const; //Permite obtener el valor dedl Arreglo de Usuarios
        void setusuarios(usuario& Usuario); //Ingresa la Informacion al Arreglo de Usuarios
        album* getalbumes() const;
        void setalbumes(album& Album); //Ingresa la Informacion al Arreglo de Albumes
        artista* getartistas() const;
        void setartista(artista Artista); //Ingresa la Informacion al Arreglo de Artistas
        cancion* getCanciones() const;
        void setCanciones(cancion Cancion); //Ingresa la Informacion al Arreglo de Canciones
        MensajePublicitario* getMessage() const;
        void setMessage(MensajePublicitario Mensaje); //Ingresa la Informacion al Arreglo de Mensajes Publicitarios
        cancion* getR_Canciones() const;
        void setR_Canciones(cancion Cancion); //Ingresa la Informacion al Arreglo de Canciones Reproducidas
        ~Sistema(); //Destructor

    private:
        static int iterador;
        usuario** usuarios;
        int tamusuarios;
        usuario* usuarioactual;
        album** albumes;
        artista** artistas;
        cancion** canciones;
        MensajePublicitario* Mensajes;
        cancion** reproducidas;
        int tamreproducidas;
};

#endif // SISTEMA_H
