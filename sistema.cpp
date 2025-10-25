#include "sistema.h"
#include "cancion.h"
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Sistema::Sistema(): usuarios(NULL), artistas(NULL), albumes(NULL), Mensajes(NULL), reproducidas(NULL), canciones(NULL) {}
int Sistema::iterador = 0;

usuario* Sistema::Login(const string& Nickname){
    /*Verifica y Busca si el Usuario que va a Ingresar al Sistema se encuentre Registrado.
    Entrada ---> Nickname del Usuario.
    Salida ---> Referencia al Usuario.
    */
    for (int i = 0; i < tamusuarios; i++){
        if (usuarios[i].Nickname == Nickname){
            return usuarios[i];
        }
    }
    return nullptr;
}

void Sistema::Log_out(){
    /*Cierra la sesión del Sistema.
    Entrada ---> Void.
    Salida ---> Void.
    */
    for (int i = 0; i < tamreproducidas; i++){
        delete[] reproducidas[i];
    }
    delete[] reproducidas;

    for (int i = 0; i < usuarioactual.tamlisfav_; i++){
        delete[] usuarioactual.List_favourites[i];
    }
    delete[] usuarioactual.List_favourites;

    usuarioactual.List_favourites = nullptr;
    reproducidas = nullptr;
}

void Sistema::CargarDatos(){
    /*
    Carga toda la Información Correspondiente a la Base de Datos del Sistema.
    Entrada ---> Void.
    Salida ---> Void.
    */
}
