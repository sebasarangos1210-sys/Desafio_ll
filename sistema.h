#ifndef SISTEMA_H
#define SISTEMA_H

#include "MensajePublicitario.h"
#include <string>
#include "album.h"
#include "artista.h"
#include "usuario.h"
#include "reproduccion.h"

using namespace std;

class Sistema {

    public:
        Sistema(); //Constructor
        Usuario* Login(const string& Nickname); //Metodo de ingreso al Sistema
        void Log_out(); //Metodo de Salir del Sistema
        //void R_musica(); // Metodo para Modelar la Reproduccion Musical
        void CargarDatos(); //Carga los Datos al Sistema
        bool ComprobarMemb(const Usuario* usuarioactual); //Verifica la Membresia del Usuario
        //void interaccion(); //Modela las Operaciones Premium
        void salida_pant(); //Imprime en Pantalla la Consola de Reproducción
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
        ~Sistema(); //Destructor

    private:
        Usuario** usuarios;
        int tamusuarios;
        Usuario** usuarioactual;
        Album** albumes;
        Artista** artistas;
        Cancion** canciones;
        MensajePublicitario* Mensajes;
        Cancion** reproducidas;
};

#endif // SISTEMA_H
