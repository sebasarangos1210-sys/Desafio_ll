#include "Credito.h"

Credito::Credito()
    : nombres(""), apellidos(""), codigoAfiliacion(""), tipoCredito(1) {
}

Credito::Credito(const string& nom, const string& apell, const string& codigo, int tipo)
    : nombres(nom), apellidos(apell), tipoCredito(tipo) {

    if (validarCodigoAfiliacion(codigo)) {
        codigoAfiliacion = codigo;
    } else {
        codigoAfiliacion = "0000000000";
    }

    if (tipoCredito < 1 || tipoCredito > 3) {
        tipoCredito = 1;
    }
}

Credito::Credito(const Credito& otro)
    : nombres(otro.nombres), apellidos(otro.apellidos),
    codigoAfiliacion(otro.codigoAfiliacion), tipoCredito(otro.tipoCredito) {
}

Credito::~Credito() {
}

bool Credito::validarCodigoAfiliacion(const string& codigo) const {
    if (codigo.length() != 10) {
        return false;
    }

    for (size_t i = 0; i < codigo.length(); i++) {
        if (!isalnum(codigo[i])) {
            return false;
        }
    }
    return true;
}

bool Credito::esValido() const {
    return !nombres.empty() &&
           !apellidos.empty() &&
           validarCodigoAfiliacion(codigoAfiliacion) &&
           tipoCredito >= 1 &&
           tipoCredito <= 3;
}

string Credito::getNombres() const {
    return nombres;
}

string Credito::getApellidos() const {
    return apellidos;
}

string Credito::getCodigoAfiliacion() const {
    return codigoAfiliacion;
}

int Credito::getTipoCredito() const {
    return tipoCredito;
}

string Credito::getNombreCompleto() const {
    return nombres + " " + apellidos;
}

string Credito::getTipoCreditoString() const {
    switch(tipoCredito) {
    case 1: return "Productor";
    case 2: return "Musico";
    case 3: return "Compositor";
    default: return "Desconocido";
    }
}

void Credito::setNombres(const string& nom) {
    nombres = nom;
}

void Credito::setApellidos(const string& apell) {
    apellidos = apell;
}

void Credito::setCodigoAfiliacion(const string& codigo) {
    if (validarCodigoAfiliacion(codigo)) {
        codigoAfiliacion = codigo;
    }
}

void Credito::setTipoCredito(int tipo) {
    if (tipo >= 1 && tipo <= 3) {
        tipoCredito = tipo;
    }
}

Credito& Credito::operator=(const Credito& otro) {
    if (this != &otro) {
        nombres = otro.nombres;
        apellidos = otro.apellidos;
        codigoAfiliacion = otro.codigoAfiliacion;
        tipoCredito = otro.tipoCredito;
    }
    return *this;
}

bool Credito::operator==(const Credito& otro) const {
    return codigoAfiliacion == otro.codigoAfiliacion;
}

bool Credito::operator!=(const Credito& otro) const {
    return !(*this == otro);
}

bool Credito::operator<(const Credito& otro) const {
    return apellidos < otro.apellidos;
}

int Credito::calcularMemoriaUsada() const {
    int total = sizeof(*this);

    // Memoria de strings
    total += nombres.length();
    total += apellidos.length();
    total += codigoAfiliacion.length();

    return total;
}
