#include "sistema.h"
#include "cancion.h"
#include "artista.h"
#include "album.h"
#include "usuario.h"
//#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

Sistema::Sistema(): usuarios(NULL), artistas(NULL), albumes(NULL), Mensajes(NULL), reproducidas(NULL), canciones(NULL), usuarioactual(NULL) {}

Usuario* Sistema::Login(const string* Nickname){
    /*Verifica y Busca si el Usuario que va a Ingresar al Sistema se encuentre Registrado.
    Entrada ---> Nickname del Usuario.
    Salida ---> Referencia al Usuario.
    */
    for (int i = 0; i < tamusuarios; i++){
        if (usuarios[i].Nickname == Nickname){
            return usuarios[i];
        }
    }
    cout << "Este Usuario no Existe en el Sistema.\n";
    return nullptr;
}

bool Sistema::ComprobarMemb(const Usuario* usuarioactual){
    /*Identifica el Tipo de Membresía del Usuario que ingresó al Sistema.
    Entradas ---> Referencia del Usuario Actual en el Sistema.
    Salida ---> True (si es Premium) or False.
    */
    return usuarioactual.getMembresia();
}

void Sistema::CargarDatos(){
    /*
    Carga toda la Información Correspondiente a la Base de Datos del Sistema.
        Entrada ---> Void.
        Salida ---> Void.
    */
    string texto, segmento, dato;
    ifstream archivo("Artistas.txt");
    ifstream archivo1.open("Albumes.txt");
    ifstream archivo2("Canciones.txt");
    ifstream archivo3("Creditos.txt");
    while (getline(archivo, texto)){

        Artista* artista = new Artista[1];
        stringstream ss (texto);

        getline(ss, segmento, '-');
        artista -> setId(stoi(segmento));
        artista ->getId();
        getline(ss, segmento, '-');
        artista -> setEdad(stoi(segmento));
        artista -> getEdad();
        getline(ss, segmento, '-');
        artista -> setPaisOrigen(segmento);
        artista -> getPaisOrigen();
        getline(ss, segmento, '-');
        artista -> setSeguidores(stoi(segmento));
        artista -> getSeguidores();
        getline(ss, segmento, '-');
        artista -> setPosicionTendencia(stoi(segmento));
        artista -> getPosicionTendencia();
        getline(ss, segmento);
        artista -> setNumAlbumes(stoi(segmento));
        artista -> getNumAlbumes();

        int contalbum = 1;
        albumes = new Album[stoi(segmento)];
        while (contalbum <= artista -> getNumAlbumes && getline(archivo1, texto)){

            Album* album = new Album[1];
            stringstream ssAlbum (texto);

            getline(ssAlbum, segmento, '-');
            album -> setNumGeneros(stoi(segmento));
            album -> getNumGeneros();

            getline(ssAlbum, segmento, '-');
            string* genAlbum = new string[stoi(segmento)];
            short int genero = 1;
            while (genero <= album -> getNumGeneros()){
                getline(segmento, dato, ",");
                genAlbum[genero-1] = dato;
                genero++;
            }

            album -> setGeneros(genAlbum);
            album -> getGeneros();
            getline(ssAlbum, segmento, '-');
            album -> setFechaLanzamiento(segmento);
            album -> getFechaLanzamiento();
            getline(ssAlbum, segmento, '-');
            album -> setDuracionTotal(stoi(segmento));
            album -> getDuracionTotal();
            getline(ssAlbum, segmento, '-');
            album -> setNombre(segmento);
            album -> getNombre();
            getline(ssAlbum, segmento, '-');
            album -> setNumCanciones(stoi(segmento));
            album -> getNumCanciones();

            canciones = new Cancion[stoi(segmento)];
            short int contcancion = 1;
            while (contcancion <= album -> getNumCanciones() && getline(archivo2, texto)){

                Cancion* cancion = new Cancion[1];
                stringstream ssCancion (texto);

                getline(ssCancion, segmento, '-');
                cancion -> setNombre(segmento);
                cancion -> getNombre();
                getline(ssCancion, segmento, '-');
                cancion -> setId(stoi(segmento));
                cancion -> getId();
                getline(ssCancion, segmento, '-');
                cancion -> setDuracion(stoi(segmento));
                cancion -> getDuracion();
                getline(ssCancion, segmento, '-');
                cancion -> setUbicacionArchivo(segmento);
                cancion -> getUbicacionArchivo();
                getline(ssCancion, segmento, '-');
                cancion -> setNumCreditos(stoi(segmento));
                cancion -> getNumCreditos();

                Credito** creditos = new Credito[stoi(segmento)];
                getline(ssCancion, segmento, '-');
                short int contcreditos = 1;

                while (contcreditos <= cancion -> getNumCreditos() && getline(archivo3, texto)){

                    Credito* credito = new Credito[1];
                    stringstream ssCredito(texto);

                    getline(ssCredito, segmento,'-');
                    credito -> setTipoCredito(segmento);
                    credito -> getTipoCredito();
                    getline(ssCredito, segmento,'-');
                    credito -> setNombres(segmento);
                    credito -> getNombres();
                    getline(ssCredito, segmento,'-');
                    credito -> setApellidos(segmento);
                    credito -> getApellidos();
                    getline(ssCredito, segmento);
                    credito -> setCodigoAfiliacion(segmento);
                    credito -> getCodigoAfiliacion();

                    creditos[contcreditos-1] = &credito;
                    contcreditos++;
                }
                cancion -> setCredito(creditos);
                cancion -> getCredito();

                getline(ssCancion, segmento);
                cancion -> setVecesReproducida(stoi(segmento));
                cancion -> getVecesReproducida();

                canciones[contcancion] = &cancion;
                contcancion++;
            }
            album -> setCanciones(canciones);
            album -> getCanciones();

            getline(ssAlbum, segmento, '-');
            album -> setId(stoi(segmento));
            album -> getId();
            getline(ssAlbum, segmento, '-');
            album -> setSelloDisquero(segmento);
            album -> getSelloDisquero();
            getline(ssAlbum, segmento, '-');
            album -> setPortada(segmento);
            album -> getPortada();
            getline(ssAlbum, segmento);
            album -> setPuntuacion(stof(segmento));
            album -> getPuntuacion();

            albumes[contalbum] = &album;
            contalbum++;
        }
        artista -> setalbumes(albumes);
        artista -> getalbumes();
    }
}

/*
void Sistema::salida_pant(){
    Muestra en Pantalla el Menu para el Usuario.
    Entradas ---> Void.
    Salida ---> Void.

    if (ComprobarMemb((this->usuarioactual)){

    }
}
*/
/*
void Sistema::Log_out(){
    Cierra la sesión del Usuario Actual en el Sistema.
    Entrada ---> Void.
    Salida ---> Void.

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


