#ifndef MENSAJEPUBLICITARIO_H
#define MENSAJEPUBLICITARIO_H

#include <string>
using namespace std;

class MensajePublicitario {
private:
    string contenido;
    int categoria;      // 1=C, 2=B, 3=AAA
    int vecesMostrado;

public:
    // Constructores
    MensajePublicitario();
    MensajePublicitario(const string& cont, int cat);

    // Destructor
    ~MensajePublicitario();

    // Métodos principales
    int obtenerPrioridad() const;
    void incrementarContador();
    bool esValido() const;

    // Getters
    string getContenido() const;
    int getCategoria() const;
    int getVecesMostrado() const;
    string getNombreCategoria() const;

    // Setters
    void setContenido(const string& cont);
    void setCategoria(int cat);
    void resetearContador();

    // Sobrecarga de operadores
    bool operator>(const MensajePublicitario& otro) const;
    bool operator<(const MensajePublicitario& otro) const;
    bool operator==(const MensajePublicitario& otro) const;

    // Método para medición de memoria
    int calcularMemoriaUsada() const;
};

#endif // MENSAJEPUBLICITARIO_H
