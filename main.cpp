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
            cout << "¿Que Accion Deseas Realizar?\nAccion: ";
            cin >> Opciones;
            if (system_.ComprobarMemb(system_.getusuarioactual())){
                while (Opciones < 49 || Opciones > 56){
                    cout << "Has Ingresado una Opcion no Disponible.\nIntenta Nuevamente: ";
                    cin >> Opciones;
                }
            } else {
                while (Opciones < 49 || Opciones > 51){
                    cout << "Has Ingresado una Opcion no Disponible.\nIntenta Nuevamente: ";
                    cin >> Opciones;
                }
                if (Opciones == '3'){
                    Opciones = '7';
                }
            }

            if (Opciones == '1'){

            } else if (Opciones == '7'){
                Ingreso = false;
            } else {
                Ingreso = false;
                cout << "Cerrando tu sesion......\n";
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
}
