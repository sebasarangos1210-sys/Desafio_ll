#ifndef CREDITO_H
#define CREDITO_H

#include <string>
using namespace std;

class Credito {
private:
    string nombres;
    string apellidos;
    string codigoAfiliacion;
    int tipoCredito;

public:
    Credito();
    Credito(const string& nom, const string& apell, const string& codigo, int tipo);
    Credito(const Credito& otro);
    ~Credito();

    bool validarCodigoAfiliacion(const string& codigo) const;
    bool esValido() const;

    string getNombres() const;
    string getApellidos() const;
    string getCodigoAfiliacion() const;
    int getTipoCredito() const;
    string getNombreCompleto() const;
    string getTipoCreditoString() const;

    void setNombres(const string& nom);
    void setApellidos(const string& apell);
    void setCodigoAfiliacion(const string& codigo);
    void setTipoCredito(int tipo);

    Credito& operator=(const Credito& otro);
    bool operator==(const Credito& otro) const;
    bool operator!=(const Credito& otro) const;
    bool operator<(const Credito& otro) const;

    int calcularMemoriaUsada() const;
};

#endif
