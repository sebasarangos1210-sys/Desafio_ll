#ifndef SISTEMA_H
#define SISTEMA_H

#include  "cancion.h"
#include "MensajePublicitario.h"
#include "album.h"|
#include "usuarios.h"

class Sistema {
    public:
        Sistema();
        ~Sistema();
        bool Login();
        void Log_out();
    private:
        static int iterador;
        usuario* usuarios;
        album* albumes;
        artista* artistas;
        cancion* canciones;
        MensajePublicitario* Mensajes;
        usuario usuarioActual;
        void CargarDatos();


};

#endif // SISTEMA_H
