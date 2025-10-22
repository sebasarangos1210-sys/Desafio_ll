#include "prototipados.h"

// Constructor por defecto
MensajePublicitario::MensajePublicitario()
    : contenido(""), categoria(1), vecesMostrado(0) {
}

// Constructor parametrizado
MensajePublicitario::MensajePublicitario(const string& cont, int cat)
    : contenido(cont), categoria(cat), vecesMostrado(0) {
    // Validar que la categoría sea válida (1, 2 o 3)
    if (categoria < 1 || categoria > 3) {
        categoria = 1;  // Por defecto categoría C
    }
    // Validar que el contenido no exceda 500 caracteres
    if (contenido.length() > 500) {
        contenido = contenido.substr(0, 500);
    }
}

// Destructor
MensajePublicitario::~MensajePublicitario() {
    // No hay memoria dinámica que liberar en esta clase
}

// Retorna la prioridad según la categoría
int MensajePublicitario::obtenerPrioridad() const {
    return categoria;
}

// Incrementa el contador de veces mostrado
void MensajePublicitario::incrementarContador() {
    vecesMostrado++;
}

// Valida que el mensaje sea válido
bool MensajePublicitario::esValido() const {
    return !contenido.empty() &&
           contenido.length() <= 500 &&
           categoria >= 1 &&
           categoria <= 3;
}

// --- GETTERS ---
string MensajePublicitario::getContenido() const {
    return contenido;
}

int MensajePublicitario::getCategoria() const {
    return categoria;
}

int MensajePublicitario::getVecesMostrado() const {
    return vecesMostrado;
}

string MensajePublicitario::getNombreCategoria() const {
    switch(categoria) {
    case 1: return "C";
    case 2: return "B";
    case 3: return "AAA";
    default: return "Desconocida";
    }
}

// --- SETTERS ---
void MensajePublicitario::setContenido(const string& cont) {
    if (cont.length() <= 500) {
        contenido = cont;
    }
}

void MensajePublicitario::setCategoria(int cat) {
    if (cat >= 1 && cat <= 3) {
        categoria = cat;
    }
}

void MensajePublicitario::resetearContador() {
    vecesMostrado = 0;
}

// --- SOBRECARGA DE OPERADORES ---

// Comparar por prioridad (mayor prioridad > menor prioridad)
bool MensajePublicitario::operator>(const MensajePublicitario& otro) const {
    return categoria > otro.categoria;
}

// Comparar por prioridad (menor prioridad < mayor prioridad)
bool MensajePublicitario::operator<(const MensajePublicitario& otro) const {
    return categoria < otro.categoria;
}

// Comparar por igualdad de contenido
bool MensajePublicitario::operator==(const MensajePublicitario& otro) const {
    return contenido == otro.contenido && categoria == otro.categoria;
}

// Calcular memoria usada por esta instancia
int MensajePublicitario::calcularMemoriaUsada() const {
    int total = sizeof(*this);  // Tamaño base del objeto
    total += contenido.capacity();  // Memoria del string
    return total;
}

//-----------------------------------------------------------------//

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

// Validar código de afiliación (10 caracteres alfanuméricos)
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
bool Credito::operator==(const Credito& otro) const {
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
