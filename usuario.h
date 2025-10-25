#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "ListaReproduccion.h"
using namespace std;

class Usuario {
private:
    string nickname;
    int membresia;
    string ciudad;
    string pais;
    string fechaInscripcion;
    sesionreproduccion* listaFavoritos;
    int ultimoMensajePublicitario;

public:
    Usuario();
    Usuario(const string& nick, int memb, const string& ciudad, const string& pais, const string& fecha);
    Usuario(const Usuario& otro);
    ~Usuario();

    bool esPremium() const;
    int obtenerCalidadAudio() const;
    bool puedeAgregarAFavoritos() const;

    bool agregarAFavoritos(Cancion* cancion);
    bool eliminarDeFavoritos(int idCancion);
    bool seguirListaFavoritos(Usuario* otroUsuario);
    ListaReproduccion* obtenerListaFavoritos() const;

    void cambiarMembresia(int nuevoTipo);
    void actualizarUltimoMensaje(int idMensaje);

    string getNickname() const;
    int getMembresia() const;
    string getCiudad() const;
    string getPais() const;
    string getFechaInscripcion() const;
    int getUltimoMensajePublicitario() const;
    string getTipoMembresiaString() const;

    void setNickname(const string& nick);
    void setCiudad(const string& city);
    void setPais(const string& country);

    Usuario& operator=(const Usuario& otro);
    bool operator==(const Usuario& otro) const;
    bool operator==(const string& nick) const;
    bool operator!=(const Usuario& otro) const;
    bool operator<(const Usuario& otro) const;

    int calcularMemoriaUsada() const;
};

#endif
