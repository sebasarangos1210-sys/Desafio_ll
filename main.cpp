#include <iostream>
#include <string>
#include "sistema.h"
#include <cstdlib>

using namespace std;

int main (){

    bool Ingreso = false, Ejec_Sistem = true;
    while (Ejec_Sistem){
        string Usuario; char Opciones;
        cout << "Bienvenido a Nuestra App UdeATunes🎼!!\nA Continuacion, Logueate para Iniciar Sesion.\n";
        cout << "Ingresa tu Nombre de Usuario: ";
        cin >> Usuario;
        Sistema system_;
        system_.CargarDatos();

        while (!Ingreso){
            Ingreso = system_.Login(Usuario);
            if (!Ingreso){
                cout << "El Usuario Ingresado no Exite en el Sistema.\nIntenta Nuevamente :";
                cin >> Usuario;
            }
        }

        while(Ingreso){

            cout << "Bienvenid@!! " << system_.getusuarioactual() -> getNickname() << "Has Ingresado Correctamente.\n";
            cout << "===========================================\n";
            cout << "\tUdeATunes - MENU PRINCIPAL\n";
            cout << "===========================================\n";
            cout << "Usuario: " << system_.getusuarioactual() -> getNickname() << cout << "|\tPlan: " << system_.getusuarioactual() -> getTipoMembresiaString() << endl;
            cout << "-------------------------------------------\n";
            cout << "A continuacion, Elige una de las Siguientes Opciones: ";
            cout << "\n(1)🎧 Iniciar Sesion Reproduccion.\n(2)🚪 Cerrar sesión.\n";
            cout << "-------------------------------------------\n";
            cout << "¿Que Accion Deseas Realizar?\nAccion: ";
            cin >> Opciones;
            if (system_.ComprobarMemb(system_.getusuarioactual())){
                while (Opciones < 49 || Opciones > 50){
                    cout << "Has Ingresado una Opcion no Disponible.\nIntenta Nuevamente: ";
                    cin >> Opciones;
                }
            }
            if (Opciones == '1'){
                system_.reproduccion();
            } else{
                Ingreso = false;
            }
        }
        cout << "¿Deseas Salir de la App?\n- Ingresa (y) en caso de que salir del Programa.\n- Ingresa (n) en caso de que desees volver a ingresar al Sistema.\n";
        cin >> Opciones;
        while (Opciones != 'y' && Opciones != 'n'){
            cout << "Has Ingresado una Opcion no Valida.\nIntenta Nuevamente: ";
            cin >> Opciones;
        }
        if (Opciones == 'y'){
            Ejec_Sistem = false;
        }
        system("cls");
    }
    void mostrarMedicionRecursosDetallada(Sistema* sistema, SesionReproduccion* sesionActual,
                                          int iteracionesFuncionalidad,
                                          const string& nombreFuncionalidad) {

        cout << "\n";
        cout << "╔══════════════════════════════════════════════════════════════╗\n";
        cout << "║           MEDICIÓN DETALLADA DE RECURSOS                     ║\n";
        cout << "╚══════════════════════════════════════════════════════════════╝\n";
        cout << "Funcionalidad: " << nombreFuncionalidad << "\n";
        cout << "══════════════════════════════════════════════════════════════\n\n";


        // 1. ITERACIONES

        cout << "📊 MÉTRICAS DE ITERACIONES\n";
        cout << "──────────────────────────────────────────────────────────────\n";
        cout << "   Iteraciones en esta funcionalidad: " << iteracionesFuncionalidad << "\n";
        cout << "   Complejidad estimada: O(n)\n\n";


        // 2. MEMORIA DETALLADA

        int memoriaTotal = 0;

        cout << "💾 DESGLOSE DE MEMORIA POR COMPONENTE\n";
        cout << "──────────────────────────────────────────────────────────────\n";

        // Sistema y sus componentes
        if (sistema != nullptr) {
            int memArtistas = 0;
            int memUsuarios = 0;
            int memMensajes = 0;
            int numArtistas = sistema->getNumArtistas();
            int numUsuarios = sistema->getNumUsuarios();
            int numMensajes = sistema->getNumMensajes();

            // Calcular memoria de artistas (incluye álbumes y canciones)
            for (int i = 0; i < numArtistas; i++) {
                Artista* artista = sistema->getArtista(i);
                if (artista != nullptr) {
                    memArtistas += artista->calcularMemoriaUsada();
                }
            }

            // Calcular memoria de usuarios
            for (int i = 0; i < numUsuarios; i++) {
                Usuario* usuario = sistema->getUsuario(i);
                if (usuario != nullptr) {
                    memUsuarios += usuario->calcularMemoriaUsada();
                }
            }

            // Calcular memoria de mensajes publicitarios
            for (int i = 0; i < numMensajes; i++) {
                MensajePublicitario* mensaje = sistema->getMensaje(i);
                if (mensaje != nullptr) {
                    memMensajes += mensaje->calcularMemoriaUsada();
                }
            }

            int memSistemaBase = sizeof(*sistema) +
                                 (sistema->getCapacidadArtistas() * sizeof(Artista*)) +
                                 (sistema->getCapacidadUsuarios() * sizeof(Usuario*)) +
                                 (sistema->getCapacidadMensajes() * sizeof(MensajePublicitario*));

            cout << "   [SISTEMA]\n";
            cout << "   ├─ Estructura base:     " << memSistemaBase << " bytes\n";
            cout << "   ├─ Artistas (" << numArtistas << "):      "
                 << memArtistas << " bytes\n";
            cout << "   ├─ Usuarios (" << numUsuarios << "):      "
                 << memUsuarios << " bytes\n";
            cout << "   └─ Mensajes (" << numMensajes << "):       "
                 << memMensajes << " bytes\n";

            int totalSistema = memSistemaBase + memArtistas + memUsuarios + memMensajes;
            cout << "   SUBTOTAL SISTEMA:       " << totalSistema << " bytes\n\n";
            memoriaTotal += totalSistema;
        }

        // Sesión de reproducción
        if (sesionActual != nullptr) {
            int memSesion = sesionActual->calcularMemoriaUsada();
            cout << "   [SESIÓN DE REPRODUCCIÓN]\n";
            cout << "   └─ Sesión actual:       " << memSesion << " bytes\n";
            cout << "   SUBTOTAL SESIÓN:        " << memSesion << " bytes\n\n";
            memoriaTotal += memSesion;
        }


        // 3. RESUMEN FINAl

        cout << "──────────────────────────────────────────────────────────────\n";
        cout << "   MEMORIA TOTAL:          " << memoriaTotal << " bytes\n";
        cout << "                           " << fixed << setprecision(2)
             << (memoriaTotal / 1024.0) << " KB\n";
        cout << "                           " << fixed << setprecision(4)
             << (memoriaTotal / 1048576.0) << " MB\n";

        // Estimación de memoria disponible típica
        double porcentajeRAM = (memoriaTotal / (8.0 * 1024 * 1024 * 1024)) * 100; // Asumiendo 8GB RAM
        cout << "                           ~" << fixed << setprecision(6)
             << porcentajeRAM << "% de 8GB RAM\n";

        cout << "══════════════════════════════════════════════════════════════\n\n";
    }
}
