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
    string file[6] = {"Credito.txt", "Cancion.txt", "Album.txt", "Artista.txt", "Usuario.txt", "Mensaje.txt"}; //Colocar Direcciones Verdaderos Archivos.
    for (int i = 1; i <= 6; i++){
        int pos = 0, j = 0, Tamagno = 0;
        string texto = "", dato = "";
        switch (i) {
        case 1:
            ifstream archivo(file[i-1], ios::in);
            archivo.getline(texto);
            Tamagno = 1;
            credito** creditos = new credito*[Tamagno];
            creditos[1] = new credito[7];
            while (getline(archivo, texto)){
                credito* Credito = new Credito();
                stringstream ss(texto);
                getline(ss, dato, '-');
                Credito.setTipoCredito(dato); //Revisar Union
                Credito.getTipoCredito();
                getline(ss, dato, '-');
                Credito.setNombres = dato; //Revisar Union
                getline(ss, dato, '-');
                Credito.apellido = dato;//Revisar Union
                getline(ss, dato);
                Credito.setCodigoAfiliacion(dato);
                Credito.getCodigoAfiliacion();
                creditos[j][pos] = &Credito;
                pos++;
                if (pos == 6 && j == Tamagno-1){
                    Tamagno *= 2;
                    credito** new_credito = new credito*[Tamagno];
                    for (int tam = 0; tam < Tamagno; tam++){
                        new_credito = new credito[7];
                    }
                    for (int tam = 0; tam < j; tam++){
                        new_credito[tam] = creditos[tam];
                    }
                    delete[] credito;
                    creditos = new_credito;
                    j++;
                    pos = 0;
                } else if (pos == 6){
                 j++;
                    pos = 0;
                }
            }
            archivo.close();
            break;
        case 2:
            if (canciones == nullptr){
                ifstream archivo(file[i-1], ios::in);
                archivo.getline(texto);
                Tamagno = 3;
                canciones = new cancion*[Tamagno];
                for (int filas = 0; filas < Tamagno; filas++){
                    canciones[filas] = new cancion[50];
                }
                while (getline(archivo, texto)){
                    cancion* Cancion = new Cancion();
                    stringstream ss(texto);
                    getline(ss, dato, '-');
                    Cancion.setNombre(dato);
                    Cancion.getNombre();
                    getline(ss, dato, '-');
                    Cancion.setId(stoi(dato));
                    Cancion.getId();
                    getline(ss, dato, '-');
                    Cancion.setDuracion(stoi(dato));
                    Cancion.getDuracion();
                    getline(ss, dato, '-');
                    Cancion.setUbicacionArchivo(dato);
                    Cancion.setUbicacionArchivo();
                    getline(ss, dato);
                    Cancion.setVecesReproducida(stoi(dato));
                    Cancion.getVecesReproducida();
                    canciones[j][pos] = &Cancion;
                    pos++;
                    if (pos == 49 && j == Tamagno-1){
                        Tamagno *= 2;
                        cancion** new_cancion = new cancion*[Tamagno];
                        for (int tam = 0; tam < Tamagno; tam++){
                            new_cancion[tam] = new cancion[50];
                        }
                        for (int tam = 0; tam < j; tam++){
                            new_cancion[tam] = canciones[tam];
                        }
                        delete[] canciones;
                        canciones = new_cancion;
                    } else if (pos == 49){
                        j++;
                        pos = 0;
                    }
                }
                archivo.close();
            }
            break;
        case 3:
            if (albumes == nullptr){
                ifstream archivo(file[i-1], ios::in);
                archivo.getline(texto);
                Tamagno = 2;
                canciones = new cancion*[Tamagno];
                for (int filas = 0; filas < Tamagno; filas++){
                    albumes[filas] = new cancion[25];
                }
                while (getline(archivo, texto)){
                    stringstream ss(texto);
                    getline(ss, dato, '-');
                    albumes[j][pos].generos = dato;
                    getline(ss, dato, '-');
                    albumes[j][pos].fechaLanzamiento = dato;
                    getline(ss, dato, '-');
                    albumes[j][pos].duracion = stoi(dato);
                    getline(ss, dato, '-');
                    albumes[j][pos].nombre = dato;
                    getline(ss, dato, '-');
                    albumes[j][pos].id = stoi(dato);
                    getline(ss, dato, '-');
                    albumes[j][pos].portada = dato;
                    getline(ss, dato);
                    albumes[j][pos].puntuacion = stoi(dato);
                    pos++;
                    if (pos == 24 && j == Tamagno-1){
                        Tamagno *= 2;
                        album** new_album = new album*[Tamagno];
                        for (int tam = 0; tam < Tamagno; tam++){
                            new_album[tam] = new album[25];
                        }
                        for (int tam = 0; tam < j; tam++){
                            new_album[tam] = albumes[tam];
                        }
                        delete[] albumes;
                        albumes = new_album;
                    } else if (pos == 24){
                        j++;
                        pos = 0;
                    }
                }
                archivo.close();
            }
            break;
        case 4:
            archivo(file[i-1], ios::ate);
            archivo.close();
            break;
        case 5:
            archivo(file[i-1], ios::ate);
            archivo.close();
            break;
        case 6:
            archivo(file[i-1], ios::ate);
            archivo.close();
            break;
        default:
            break;
        }
    }
}

