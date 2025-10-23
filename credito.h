#ifndef CREDITO_H
#define CREDITO_H

#ifndef CREDITO_H
#define CREDITO_H

#include <string>
using namespace std;

class Credito {
private:
    string* nombres;              // Puntero para permitir flexibilidad
    string apellidos;
    string codigoAfiliacion;      // 10 caracteres alfanuméricos
    int tipoCredito;              // 1=Productor, 2=Músico, 3=Compositor

public:
    // Constructores
    Credito();
    Credito(const string& nom, const string& apell, const string& codigo, int tipo);
    Credito(const Credito& otro);  // Constructor de copia

    // Destructor
    ~Credito();

    // Métodos principales
    bool validarCodigoAfiliacion(const string& codigo) const;
    bool esValido() const;

    // Getters
    string getNombres() const;
    string getApellidos() const;
    string getCodigoAfiliacion() const;
    int getTipoCredito() const;
    string getNombreCompleto() const;
    string getTipoCreditoString() const;

    // Setters
    void setNombres(const string& nom);
    void setApellidos(const string& apell);
    void setCodigoAfiliacion(const string& codigo);
    void setTipoCredito(int tipo);

    // Sobrecarga de operadores
    Credito& operator=(const Credito& otro);
    bool operator==(const Credito& otro) const;
    bool operator!=(const Credito& otro) const;
    bool operator<(const Credito& otro) const;

    // Método para medición de memoria
    int calcularMemoriaUsada() const;
};

#endif // CREDITO_H
