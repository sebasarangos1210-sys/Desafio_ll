#include <string>
using namespace std;

class MensajePublicitario {
private:
    string contenido;
    int categoria;
    int vecesMostrado;

public:
    // Constructor por defecto
    MensajePublicitario() : contenido(""), categoria(1), vecesMostrado(0) {}

    // Constructor parametrizado
    MensajePublicitario(const string& cont, int cat)
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
    ~MensajePublicitario() {
        // No hay memoria dinámica que liberar en esta clase
    }

    // Retorna la prioridad según la categoría
    // C=1 (1x), B=2 (2x), AAA=3 (3x)
    int obtenerPrioridad() const {
        return categoria;
    }

    // Incrementa el contador de veces que se ha mostrado este mensaje
    void incrementarContador() {
        vecesMostrado++;
    }

    // Valida que el mensaje sea válido
    bool esValido() const {
        return !contenido.empty() &&
               contenido.length() <= 500 &&
               categoria >= 1 &&
               categoria <= 3;
    }

    // --- GETTERS ---
    string getContenido() const {
        return contenido;
    }

    int getCategoria() const {
        return categoria;
    }

    int getVecesMostrado() const {
        return vecesMostrado;
    }

    // --- SETTERS ---
    void setContenido(const string& cont) {
        if (cont.length() <= 500) {
            contenido = cont;
        }
    }

    void setCategoria(int cat) {
        if (cat >= 1 && cat <= 3) {
            categoria = cat;
        }
    }

    //resetear contador
    void resetearContador() {
        vecesMostrado = 0;
    }

    //obtener nombre de categoría como string
    string getNombreCategoria() const {
        switch(categoria) {
        case 1: return "C";
        case 2: return "B";
        case 3: return "AAA";
        default: return "Desconocida";
        }
    }
};

