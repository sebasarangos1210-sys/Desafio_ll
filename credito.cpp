#include "Credito.h"
#include <cctype>

// Constructor por defecto
Credito::Credito()
    : nombres(nullptr), apellidos(""), codigoAfiliacion(""), tipoCredito(1) {
    nombres = new string("");
}

// Constructor parametrizado
Credito::Credito(const string& nom, const string& apell, const string& codigo, int tipo)
    : apellidos(apell), tipoCredito(tipo) {
    nombres = new string(nom);

    // Validar y ajustar código de afiliación (debe tener 10 caracteres)
    if (validarCodigoAfiliacion(codigo)) {
        codigoAfiliacion = codigo;
    } else {
        codigoAfiliacion = "0000000000"; // Código por defecto si no es válido
    }

    // Validar tipo de crédito (1, 2 o 3)
    if (tipoCredito < 1 || tipoCredito > 3) {
        tipoCredito = 1; // Por defecto Productor
    }
}

// Constructor de copia (IMPORTANTE por el uso de punteros)
Credito::Credito(const Credito& otro)
    : apellidos(otro.apellidos),
    codigoAfiliacion(otro.codigoAfiliacion),
    tipoCredito(otro.tipoCredito) {
    // Copia profunda del puntero
    if (otro.nombres != nullptr) {
        nombres = new string(*(otro.nombres));
    } else {
        nombres = nullptr;
    }
}

// Destructor
Credito::~Credito() {
    if (nombres != nullptr) {
        delete nombres;
        nombres = nullptr;
    }
}

// Validar código de afiliación (10 caracteres)
bool Credito::validarCodigoAfiliacion(const string& codigo) const {
    if (codigo.length() != 10) {
        return false;
    }

    for (size_t i = 0; i < codigo.length(); i++) {
        if (!isalnum(codigo[i])) {  // No es alfanumérico
            return false;
        }
    }
    return true;
}

// Validar que el crédito es válido
bool Credito::esValido() const {
    return nombres != nullptr &&
           !nombres->empty() &&
           !apellidos.empty() &&
           validarCodigoAfiliacion(codigoAfiliacion) &&
           tipoCredito >= 1 &&
           tipoCredito <= 3;
}

// --- GETTERS ---
string Credito::getNombres() const {
    return (nombres != nullptr) ? *nombres : "";
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
    return getNombres() + " " + apellidos;
}

// Obtener tipo de crédito como string
string Credito::getTipoCreditoString() const {
    switch(tipoCredito) {
    case 1: return "Productor";
    case 2: return "Musico";
    case 3: return "Compositor";
    default: return "Desconocido";
    }
}

// --- SETTERS ---
void Credito::setNombres(const string& nom) {
    if (nombres == nullptr) {
        nombres = new string(nom);
    } else {
        *nombres = nom;
    }
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

// --- SOBRECARGA DE OPERADORES ---

// Operador de asignación (CRÍTICO por punteros)
Credito& Credito::operator=(const Credito& otro) {
    if (this != &otro) {  // Evitar autoasignación
        // Liberar memoria existente
        if (nombres != nullptr) {
            delete nombres;
        }

        // Copia profunda
        if (otro.nombres != nullptr) {
            nombres = new string(*(otro.nombres));
        } else {
            nombres = nullptr;
        }

        apellidos = otro.apellidos;
        codigoAfiliacion = otro.codigoAfiliacion;
        tipoCredito = otro.tipoCredito;
    }
    return *this;
}

// Comparar créditos por código de afiliación
bool Credito::operator== st {
    return codigoAfiliacion == otro.codigoAfiliacion;
}

// Operador diferente
bool Credito::operator!=(const Credito& otro) const {
    return !(*this == otro);
}

// Ordenar por apellido (útil para ordenamiento)
bool Credito::operator<(const Credito& otro) const {
    return apellidos < otro.apellidos;
}

// Calcular memoria usada por esta instancia
int Credito::calcularMemoriaUsada() const {
    int total = sizeof(*this);  // Tamaño base del objeto
    if (nombres != nullptr) {
        total += sizeof(string) + nombres->capacity();
    }
    total += apellidos.capacity();
    total += codigoAfiliacion.capacity();
    return total;
}
