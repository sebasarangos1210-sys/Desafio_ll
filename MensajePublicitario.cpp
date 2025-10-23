#include "MensajePublicitario.h"

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
