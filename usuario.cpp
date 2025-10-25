#include "Usuario.h"

Usuario::Usuario()
    : nickname(""), membresia(0), ciudad(""), pais(""),
    fechaInscripcion(""), listaFavoritos(nullptr), ultimoMensajePublicitario(-1) {
}

Usuario::Usuario(const string& nick, int memb, const string& city, const string& country, const string& fecha)
    : nickname(nick), membresia(memb), ciudad(city), pais(country),
    fechaInscripcion(fecha), listaFavoritos(nullptr), ultimoMensajePublicitario(-1) {

    if (membresia != 0 && membresia != 1) {
        membresia = 0;
    }

    if (esPremium()) {
        listaFavoritos = new sesionreproduccion(10000);
    }
}

Usuario::Usuario(const Usuario& otro)
    : nickname(otro.nickname), membresia(otro.membresia), ciudad(otro.ciudad),
    pais(otro.pais), fechaInscripcion(otro.fechaInscripcion),
    ultimoMensajePublicitario(otro.ultimoMensajePublicitario) {

    if (otro.listaFavoritos != nullptr) {
        listaFavoritos = new sesionreproduccion(*(otro.listaFavoritos));
    } else {
        listaFavoritos = nullptr;
    }
}

Usuario::~Usuario() {
    if (listaFavoritos != nullptr) {
        delete listaFavoritos;
        listaFavoritos = nullptr;
    }
}

bool Usuario::esPremium() const {
    return membresia == 1;
}

int Usuario::obtenerCalidadAudio() const {
    return esPremium() ? 320 : 128;
}

bool Usuario::puedeAgregarAFavoritos() const {
    return esPremium();
}

bool Usuario::agregarAFavoritos(Cancion* cancion) {
    if (!esPremium() || listaFavoritos == nullptr || cancion == nullptr) {
        return false;
    }

    return listaFavoritos->agregarCancion(cancion);
}

bool Usuario::eliminarDeFavoritos(int idCancion) {
    if (!esPremium() || listaFavoritos == nullptr) {
        return false;
    }

    return listaFavoritos->eliminarCancion(idCancion);
}

bool Usuario::seguirListaFavoritos(Usuario* otroUsuario) {
    if (!esPremium() || otroUsuario == nullptr || !otroUsuario->esPremium()) {
        return false;
    }

    if (listaFavoritos == nullptr) {
        listaFavoritos = new sesionreproduccion(10000);
    }

    sesionreproduccion* otraLista = otroUsuario->obtenerListaFavoritos();
    if (otraLista == nullptr) {
        return false;
    }

    *listaFavoritos += *otraLista;
    return true;
}

sesionreproduccion* Usuario::obtenerListaFavoritos() const {
    return listaFavoritos;
}

void Usuario::cambiarMembresia(int nuevoTipo) {
    if (nuevoTipo != 0 && nuevoTipo != 1) {
        return;
    }

    int anteriorMembresia = membresia;
    membresia = nuevoTipo;

    if (anteriorMembresia == 0 && nuevoTipo == 1) {
        if (listaFavoritos == nullptr) {
            listaFavoritos = new sesionreproduccion(10000);
        }
    } else if (anteriorMembresia == 1 && nuevoTipo == 0) {
        if (listaFavoritos != nullptr) {
            delete listaFavoritos;
            listaFavoritos = nullptr;
        }
    }
}

void Usuario::actualizarUltimoMensaje(int idMensaje) {
    ultimoMensajePublicitario = idMensaje;
}

string Usuario::getNickname() const {
    return nickname;
}

int Usuario::getMembresia() const {
    return membresia;
}

string Usuario::getCiudad() const {
    return ciudad;
}

string Usuario::getPais() const {
    return pais;
}

string Usuario::getFechaInscripcion() const {
    return fechaInscripcion;
}

int Usuario::getUltimoMensajePublicitario() const {
    return ultimoMensajePublicitario;
}

string Usuario::getTipoMembresiaString() const {
    return esPremium() ? "Premium" : "Estandar";
}

void Usuario::setNickname(const string& nick) {
    if (!nick.empty()) {
        nickname = nick;
    }
}

void Usuario::setCiudad(const string& city) {
    ciudad = city;
}

void Usuario::setPais(const string& country) {
    pais = country;
}

Usuario& Usuario::operator=(const Usuario& otro) {
    if (this != &otro) {
        if (listaFavoritos != nullptr) {
            delete listaFavoritos;
        }

        nickname = otro.nickname;
        membresia = otro.membresia;
        ciudad = otro.ciudad;
        pais = otro.pais;
        fechaInscripcion = otro.fechaInscripcion;
        ultimoMensajePublicitario = otro.ultimoMensajePublicitario;

        if (otro.listaFavoritos != nullptr) {
            sesionreproduccion = new sesionreproduccion(*(otro.listaFavoritos));
        } else {
            listaFavoritos = nullptr;
        }
    }
    return *this;
}

bool Usuario::operator==(const Usuario& otro) const {
    return nickname == otro.nickname;
}

bool Usuario::operator==(const string& nick) const {
    return nickname == nick;
}

bool Usuario::operator!=(const Usuario& otro) const {
    return !(*this == otro);
}

bool Usuario::operator<(const Usuario& otro) const {
    return membresia < otro.membresia;
}

int Usuario::calcularMemoriaUsada() const {
    int total = sizeof(*this);
    total += nickname.length();
    total += ciudad.length();
    total += pais.length();
    total += fechaInscripcion.length();

    if (listaFavoritos != nullptr) {
        total += listaFavoritos->calcularMemoriaUsada();
    }

    return total;
}
