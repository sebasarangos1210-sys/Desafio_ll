#include "sistema.h"
#include "cancion.h"
#include "artista.h"
#include "album.h"
#include "usuario.h"
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

Sistema::Sistema(): usuarios(NULL), artistas(NULL), albumes(NULL),
    Mensajes(NULL), reproducidas(NULL), canciones(NULL), usuarioactual(NULL), cantartistas(0), cantalbumes(0), cantusuarios(0), cantcanciones(0) {}

bool Sistema::Login(const string& Nickname){
    /*Verifica y Busca si el Usuario que va a Ingresar al Sistema se encuentre Registrado.
    Entrada ---> Nickname del Usuario.
    Salida ---> Referencia al Usuario.
    */
    for (int i = 0; i < cantusuarios; i++){
        if (usuarios[i] -> getNickname() == Nickname){
            usuarioactual = usuarios[i];
            return true;
        }
    }
    cout << "Este Usuario no Existe en el Sistema.\n";
    return false;
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
    string texto;
    ifstream archivo("Artistas.txt");
    ifstream archivo1("Albumes.txt");
    ifstream archivo2("Canciones.txt");
    ifstream archivo3("Creditos.txt");
    ifstream archivo4("Usuarios.txt");
    ifstream archivo5("List.Favoritos.txt");

    tamartistas = 2; int filas = 0, columna = 0;
    artistas = new Artista*[tamartistas];
    for (int i = 0; i < tamartistas; i++){
        artistas[i] = new Artista[30];
    }

    tamalbumes = 2; int filalbum = 0, colalbum = 0;
    albumes = new Album*[tamalbumes];
    for (int i = 0; i < tamalbumes; i++){
        albumes[i] = new Album[40];
    }

    tamcanciones = 2; int filcancion = 0, colcancion = 0;
    canciones = new Cancion*[tamcanciones];
    for (int i = 0; i < tamcanciones; i++){
        canciones[i] = new Cancion[100];
    }

    tamusuarios = 2; int filuser = 0, coluser = 0;
    usuarios = new Usuario*[tamusuarios];
    for (int i = 0; i < tamusuarios; i++){
        usuarios[i] = new Usuario[100];
    }

    getline(archivo, texto);
    while (getline(archivo, texto)){

        Artista* artista = new Artista();
        CargarArtistas(artista, texto);

        int contalbum = 1;
        Album** al_tits = new Album*[artista -> getNumAlbumes()];
        getline(archivo1, texto);
        while (contalbum <= artista -> getNumAlbumes() && getline(archivo1, texto)){

            Album* album = new Album();
            CargarAlbumes(album, texto);

            Cancion** can_tits = new Cancion*[album -> getNumCanciones()];
            short int contcancion = 1;
            getline(archivo2, texto);
            while (contcancion <= album -> getNumCanciones() && getline(archivo2, texto)){

                Cancion* cancion = new Cancion();
                CargarCanciones(texto, archivo3);

                can_tits[contcancion-1] = cancion;
                cantcanciones++;
                agregarcanciones(filcancion, colcancion, tamcanciones, cancion);
                contcancion++;
            }
            album -> setCanciones(can_tits);
            album -> getCanciones();

            al_tits[contalbum-1] = album;
            cantalbumes++;
            agregaralbumes(filalbum, colalbum, tamalbumes, album);
            contalbum++;
        }
        artista -> setalbumes(al_tits);
        artista -> getalbumes();
        cantartistas++;
    }

    getline(archivo4, texto);
    while (getline(archivo4, texto)){
        Usuario* user = new Usuario();
        CargarUsuarios(user, texto);

        CargarListaFavoritos();
    }
}

void Sistema::CargarAlbumes(Album* album, string texto){
    /*Carga la Informacion de los Albumes Correspondientes al Artista.
    Entradas ---> Referencia al Artista Instancioado, texto del cual obtener los datos del Álbum.
    Salida ---> Void.
    */
    Album* album = new Album();
    stringstream ssAlbum (texto);
    string segmento;

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
    if (genero == 1){
        genAlbum = nullptr;
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
}

void Sistema::agregaralbumes(int& filas, int& columnas, int& tamalbumes, const Album* album){
    /*Agrega los Albumes Instanciados al Arreglo de Albumes del Sistema.
    Entradas ---> filas del Arreglo, Columnas del Arreglo, Cantidad Total de Filas del Arreglo, Referencia del Objeto Instanciado.
    Salidas ---> Void.
    */
    albumes[filas][columnas] = album;
    if (columnas == 29){
        filas++;
        columnas = 0;
        if (filas == tamalbumes){
            tamalbumes++;
            Album** newalbum = new Album*[tamalbumes];
            for (int i = 0; i < tamalbumes; i++){
                if (i < filas){
                    newalbum[i] = albumes[i];
                } else{
                    newalbum[i] = new Album[40];
                }
            }
            delete[] albumes;
            albumes = newalbum;
        }
    } else{
        columnas++;
    }
}

void Sistema::CargarCanciones(Cancion* cancion, string texto, ifstream archivo3){
    /*Carga la Informacion de las Canciones Correspondientes al Album.
    Entradas ---> Texto del cual obtener los datos de la Canción, Archivo del cual se extraerán la información de los Créditos.
    Salida ---> Void.
    */
    string segmento;
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

    Credito** creditos = new Credito*[stoi(segmento)];
    short int contcreditos = 1;
    getline(archivo3, texto);

    while (contcreditos <= cancion -> getNumCreditos() && getline(archivo3, texto)){

        Credito* credito = new Credito();
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

        creditos[contcreditos-1] = credito;
        contcreditos++;
    }
    if (contcreditos == 1){
        creditos = nullptr;
    }
    cancion -> setCredito(creditos);
    cancion -> getCredito();

    getline(ssCancion, segmento);
    cancion -> setVecesReproducida(stoi(segmento));
    cancion -> getVecesReproducida();
}

void Sistema::agregarcanciones(int& filas, int& columnas, int& tamcanciones, Cancion* cancion){
    /*Agrega las Canciones Instanciados al Arreglo de Canciones del Sistema.
    Entradas ---> Filas del Arreglo, Columnas del Arreglo, Cantidad Total de Filas del Arreglo, Referencia del Objeto Instanciado.
    Salidas ---> Void.
    */
    canciones[filas][columnas] = cancion;
    if (columnas == 39){
        filas++;
        columnas = 0;
        if (filas == tamcanciones){
            tamcanciones++;
            Cancion** newcanciom = new Cancion*[tamcanciones];
            for (int i = 0; i < tamcanciones; i++){
                if (i < filas){
                    newcancion[i] = canciones[i];
                } else{
                    newcancion[i] = new Cancion[100];
                }
            }
            delete[] canciones;
            canciones = newcancion;
        }
    } else{
        columnas++;
    }
}

void Sistema::agregarartistas(int& filas, int& columnas, int& tamartistas, Artista* artista){
    /*Agrega los Artistas Instanciados al Arreglo de Artistas del Sistema.
    Entradas ---> Filas del Arreglo, Columnas del Arreglo, Cantidad Total de Filas del Arreglo, Referencia del Objeto Instanciado.
    Salidas ---> Void.
    */
    artistas[filas][columnas] = artista;
    if (columnas == 6){
        filas++;
        columnas = 0;
        if (filas == tamartistas){
            tamartistas++;
            Artista** newartist = new Artista*[tamartistas];
            for (int i = 0; i < tamartistas; i++){
                if (i < filas){
                    newartist[i] = artistas[i];
                } else{
                    newartist[i] = new Artista[20];
                }
            }
            delete[] artistas;
            artistas = newartist;
        }
    } else{
        columnas++;
    }
}

void Sistema::CargarArtistas(Artista* artista, string texto){
    /*Carga la Informacion de los Artistas Correspondientes al Arreglo de Artistas.
    Entradas ---> Referencia del Objeto Instanciado, Texto que contiene la Información del Objeto.
    Salida ---> Void.
    */
    stringstream ss (texto);
    string segmento;

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
}

void Sistema::CargarUsuarios(Usuario* user, string texto){
    /*Realiza la Lectura de la Información Correspondiante a cada Usuario.
    Entradas ---> Referencia al Objeto Instanciado, Texto con el Flujo de Datos del Usuario.
    Salida ---> Void.
    */
    stringstream ssUsuario(texto);
    string segmento;

    getline(ssUsuario, segmento, '-');
    user -> setNickname(segmento);
    user -> getNickname();
    getline(ssUsuario, segmento, '-');

    if (segmento == "Premium"){
        user -> setMembresia(1);
        user -> getMembresia();
    } else{
        user -> setMembresia(0);
        user -> getMembresia();
    }

    getline(ssUsuario, segmento, '-');
    user -> setCiudad(segmento);
    user -> getCiudad();
    getline(ssUsuario, segmento, '-');
    user -> setPais(segmento);
    user -> getPais();
    getline(ssUsuario, segmento, '-');
    user -> setFechaInscripcion(segmento);
    user -> getFechaInscripcion();
    getline(ssUsuario, segmento);
    user -> setSeguido(segmento);
    user -> getSeguido();
}

void Sistema::agregarusuarios(int& filas, int& columnas, int& tamusuarios, const Usuario* user){
    /*Agrega el Usuario al Arreglo de Usuarios del Sistema.
    Entradas ---> Filas del Arreglo, Columnas del Arreglo, Cantidad Total de Filas del Arreglo, Referencia del Objeto Instanciado.
    Salidas ---> Void.
    */
    usuarios[filas][columnas] = user;
    if (columnas == 99){
        filas++;
        columnas = 0;
        if (filas == tamusuarios){
            tamusuarios++;
            Usuario** newusuario = new Usuario*[tamusuarios];
            for (int i = 0; i < tamusuarios; i++){
                if (i < filas){
                    newusuario[i] = usuarios[i];
                } else{
                    newusuario[i] = new Usuario[100];
                }
            }
            delete[] usuarios;
            usuarios = newusuario;
        }
    } else{
        columnas++;
    }
}

void Sistema::CargarListaFavoritos(ListaFavoritos* List_user, ifstream archivo5){
    /*Carga la Lista de Favoritos de cada Usuario.
    Entradas ---> Referencia del usuario, Archivo con la Informacion de la Lista de Favoritos.
    Salidas ---> Void.
    */
    string texto;
    List_user -> canciones = new Cancion*[capcanciones];
    int num = cantcanciones%30 != 0? cantcanciones/30 +1: cantcanciones/30;
    for (int i = 0; i < capcanciones; i++){
        List_user -> canciones[i] = new Cancion[100];
    }
    while(getline(archivo5, texto, '-')){
        for (int i = 0; i < num; i++){
            for (int j = 0; j < 100; j++){
                if (canciones[i][j] -> getNombre() == texto){
                    List_user.AgregarCancion(canciones[i][j]);
                }
            }
        }
    }
}

void Sistema::Log_out(){
    /*
    Cierra la sesión del Usuario Actual en el Sistema.
    Entrada ---> Void.
    Salida ---> Void.
    */
    ofstream archivo("Artistas.txt", ios::out);
    ofstream archivo1("Albumes.txt", ios::out);
    ofstream archivo2("Canciones.txt", ios::out);
    ofstream archivo3("Creditos.txt", ios::out);
    ofstream archivo4("Usuarios.txt", ios::out);
    ofstream archivo5("List.Favoritos.txt", ios::out);
    ofstream archivo6("Mensajes.txt");

    archivo2 << "Nombre-Identificacion-Duracion-Ubicacion Archivos-Numero Creditos-Veces Reproducida\n";
    archivo1 << "Numero Generos-Generos-Fecha Lanzamiento-Duracion-Nombre-Numero Canciones-Identificador-Sello-Imagen-Puntuacion\n";
    archivo << "Identificacion-Edad-Pais-Seguidores-Top Ranking-Numero Albumes\n";
    archivo3 << "Tipo Credito-Nombre-Apellido-Codigo-Regalias\n";
    archivo4 << "Nickname-Membresia-Ciudad-Pais-Fecha Inscripcion-Usuario Seguido\n";
    archivo6 << "Categoria Mensaje-Contenido\n";
    for (int i = 0; i < tamcanciones; i++){
        for (int j = 0; j < 100; j++){
            archivo << canciones[i][j] -> getNombre() << "-" << canciones[i][j] -> getId() << "-" << canciones[i][j] -> getDuracion() << "-" << canciones[i][j] -> getUbicacionArchivo() << "-" << canciones[i][j] -> getNumCreditos() << "-" << canciones[i][j] -> getVecesReproducida() << "\n";
            if (i*100 + j == cantcanciones-1){
                break;
            }
        }
        if (i == cantcanciones/100){
            break;
        }
    }

    for (int i = 0; i < tamalbumes; i++){
        for (int j = 0; j < 40; j++){
            archivo1 << albumes[i][j] -> getNumGeneros() << "-";
                for (int k = 1; k <= albumes[i][j] -> getNumGeneros(); k++){
                    if (k < albumes[i][j] -> getNumGeneros()){
                        archivo1 << albumes[i][j] -> getGeneros()[k] << ",";
                    } else{
                        archivo1 << albumes[i][j] -> getGeneros()[k];
                    }
                }
            archivo1 << canciones[i][j] -> getFechaLanzamiento() << "-" << canciones[i][j] -> getDuracion() << "-" << canciones[i][j] -> getNombre() << "-" << canciones[i][j] -> getNumCanciones() <<
            canciones[i][j] -> getId() << "-" << canciones[i][j] -> getSelloDisquero() << "-" << canciones[i][j] -> getPortada() << "-" << canciones[i][j] -> getPuntuacion() << "\n";
            if (i*40 + j == cantalbumes-1){
                break;
            }
        }
        if (i == cantalbumes/40){
            break;
        }
    }

    for (int i = 0; i < tamartistas; i++){
        for (int j = 0; j < 30; j++){
            archivo << artistas[i][j] -> getId() << "-" << artistas[i][j] -> getEdad() << "-" << artistas[i][j] -> getPaisOrigen() << "-" << artistas[i][j] -> getSeguidores() << "-" << artistas[i][j] -> getPosicionTendencia() << "-" << artistas[i][j] -> getNumAlbumes() << "\n";
            if (i*30 + j == cantartistas-1){
                break;
            }
        }
        if (i == cantartistas/30){
            break;
        }
    }

    for (int i = 0; i < tamusuarios; i++){
        for (int j = 0; j < 100; j++){
            archivo << usuarios[i][j] -> getNickname() << "-" << usuarios[i][j] -> getMembresia() << "-" << usuarios[i][j] -> getCiudad() << "-" << usuarios[i][j] -> getPais() << "-" << usuarios[i][j] -> getFechaInscripcion() << "-" << usuarios[i][j] -> getSeguido() << "\n";
            if (i*100 + j == cantusuarios-1){
                break;
            }
        }
        if (i == cantusuarios/100){
            break;
        }
    }
}

Usuario* Sistema::getusuarioactual(){
    /*Entrega el Usuario Actual que ha ingresado al Sistema.
    Entradas ---> Void.
    Salida ---> Void.
    */
    return usuarioactual;
}

void Sistema::reproducir(FuenteReproduccion* f_user){
    /*Comienza la Accion de Reproducir las Canciones segun corresponde al Usuario.
    Entradas ---> Void.
    Salida ---> Void.
    */
    if (sesion.estaEnReproduccion()){
        cout << "Ya el Sistema se encuentra en Reproduccion.\n";
    } else {
        sesion.iniciar();
        if (tiemporeproduccion == 0){
            this -> pasarcancion(f_user);
        }
    }
}

void Sistema::pausa(){
    /*Pausa la Reproduccion de las Canciones.
    Entradas ---> Void.
    Salida ---> Void.
    */
    if (!sesion.estaEnReproduccion()){
        cout << "Ya el Sistema se encuentra en Pausa.\n";
    } else{
        sesion.detener();
    }
}

char Sistema::reproduccion(){
    /*Modela las Acciones de Interaccion con el Usuario.
    Entradas ---> Void.
    Salida ---> Void.
    */
    string Opciones; int max;
    thread Input(this -> input());
    this -> reproducir(usuarioactual.getFuenteReproduccion());
    if (usuarioactual.getFuenteReproducccion -> getTipoFuente() == ALEATORIA_SISTEMA){
        max = 3;
    } else{
        max = cancionactual.getDuracion();
    }
    while (tiemporeproduccion < max && Exec){
        this_thread::sleep_for(chrono::milliseconds(1000));
        if (sesion.enReproduccion){
            tiemporeproduccion++;
        }
        if (tiemporeproduccion == max){
            this -> pasarcancion(this -> getusuarioactual() -> getFuenteReproduccion());
        }
    }
}

void Sistema::pasarcancion(FuenteReproduccion* f_user){
    /*Pasa a la siguiente Cancion.
    Entradas ---> Void.
    Salida ---> Void.
    */
    tiemporeproduccion = 0;
    if (!sesion.esModoRepetir()){
        if (f_user.haySiguiente()){
            cancionactual = f_user.siguienteCancion();
        } else{
            f_user.reiniciar();
        }
    }
}

void Sistema::input(){
    char Opciones;
    cout << "¿Que Accion Deseas Realizar?\nAccion: ";
    cin >> Opciones;

    while (Opciones < 49 || Opciones > 53){
        cout << "Has Ingresado una Opcion no Disponible.\nIntenta Nuevamente: ";
        cin >> Opciones;
    }
    if (Opciones == '1'){
        this -> reproducir(usuarioactual.getFuenteReproduccion);
    } else if (Opciones == '2'){
        this -> pausa();
    } else if (Opciones == '3'){
        this -> pasarcancion(usuarioactual.getFuenteReproduccion);
    } else if (Opciones == '4'){
        this -> retroceder(usuarioactual.getFuenteReproduccion);
    } else if (Opciones == '5'){
        sesion.setModoRepetir(1);
        sesion.getModoRepetir();
    } else if (Opciones == '6'){
        sesion.setModoRepetir(0);
        sesion.getModoRepetir();
    } else if (Opciones == '7'){
        cout << "Elige (1) si deseas Seguir la Lista de Favoritos de Otro Usuario.\nElige (2) si deseas dejar de Seguir la Lista de Favoritos de Otro Usuario.\nElige (3) si deseas Agregar una Cancion a tu Lista de Favoritos.\nElige (4) si deseas Eliminar una Cancion tu Lista de Favoritos.\n";
        cin >> Opciones;
        while (Opciones < 49 || Opciones > 52){
            cout << "Has Ingresado una Opcion no Disponible.\nIntenta Nuevamente: ";
            cin >> Opciones;
        }
        this -> Favoritos(Opciones);
    } else{
        Exec = false;
        return;
    }
}

void Sistema::retroceder(FuenteReproduccion* f_user){
    if (f_user.getCantidadReproducidas() == 0){
        cout << "Aun no has escuchado Ninguna Cancion.\n";
    } else if(sesion.anterior()){
    }
}

bool Sistema::BuscarUsuario(const string& Nickname){
    for (int i = 0; i < cantusuarios; i++){
        if (usuarios[i] -> getNickname == Nickname){
            usuarioactual.setSeguido(usuarios[i]);
            usuarioactual.getSeguido();
            usuarioactual.seguirListaFavoritos(usuarioactual.getSeguido());
            return true;
        }
    }
    return false;
}

void Sistema::Favoritos(char Opcion){
    string Dato;
    this -> pausa();
    if (Opcion == '1'){
        if (usuario.getSeguido() == nullptr){
            cout << "Ingresa el nombre del Usuario que deseas seguir: ";
            cin >> Dato;
            while (!BuscarUsuario(Dato)){
                cout << "El Usuario que has Ingresado no Existe.\nIntenta Nuevamente: ";
                cin >> Dato;
            }
        } else{
            cout << "Ya sigues a un Usuario.\n";
        }
    } else if (Opcion == '2'){
    } else if (Opcion == '3'){
        cout << "Ingresa el nombre de la Cancion que deseas Agregar: ";
        cin >> Dato;
        while (!BuscarCancion(Dato)){
            cout << "El Id que has Ingresado no Existe.\nIntenta Nuevamente: ";
            cin >> Dato;
        }
    } else {
        cout << "Ingresa el nombre de la Cancion que deseas Eliminar: ";
        cin >> Dato;
        while (!usuarioactual.eliminarDeFavoritos()){
            cout << "El Id que has Ingresado no Existe.\nIntenta Nuevamente: ";
            cin >> Dato;
        }
    }
}

bool Sistema::BuscarCancion(const string& Id){
    for (int i = 0; i < cantcanciones; i++){
        if (canciones[i] -> getId == Id){
            usuarioactual.agregarAFavoritos(canciones[i]);
            return true;
        }
    }
    return false;
}
