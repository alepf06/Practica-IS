#include "sistema.h"
#include <iostream>

using namespace std;

int main(){
    Usuario u;
    int opcion;

    do{
        cout << "1. Iniciar sesión\n";
        cout << "2. Crear cuenta\n";
        cout << "3. Recuperar contraseña\n";
        cout << "0. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch(opcion){
            case 1:
                if (!u.login()) break;

                int op;

                // =============================
                // MENU COORDINADOR
                // =============================
                if (u.getRol() == "COORDINADOR"){
                    Coordinador c;
                    do{
                        cout << "\n--- MENU COORDINADOR ---\n";
                        cout << "1. Asignar tutor\n";
                        cout << "2. Ver asignaciones\n";
                        cout << "3. Evaluar alumno\n";
                        cout << "4. Enviar mensaje\n";
                        cout << "5. Ver mensajes\n";
                        cout << "0. Salir\n";
                        cout << "Opción: ";
                        cin >> op;

                        switch(op){
                            case 1: c.asignarTutor(); break;
                            case 2: c.verAsignaciones(); break;
                            case 3: evaluarAlumno(); break;
                            case 4: enviarMensaje(u.getUsuario()); break;
                            case 5: verMensajes(u.getUsuario()); break;
                            case 0: break;
                            default: cout << "Opción no válida\n";
                        }

                    } while (op != 0);
                }

                // =============================
                // MENU TUTOR
                // =============================
                else if (u.getRol() == "TUTOR"){
                    Tutor t;
                    do{
                        cout << "\n--- MENU TUTOR ---\n";
                        cout << "1. Enviar mensaje\n";
                        cout << "2. Ver mensajes\n";
                        cout << "3. Ver alertas\n";
                        cout << "0. Salir\n";
                        cout << "Opción: ";
                        cin >> op;

                        switch(op){
                            case 1: enviarMensaje(u.getUsuario()); break;
                            case 2: verMensajes(u.getUsuario()); break;
                            case 3: verAlertas(u.getUsuario()); break;
                            case 0: break;
                            default: cout << "Opción no válida\n";
                        }

                    } while (op != 0);
                }

                // =============================
                // MENU ALUMNO
                // =============================
                else{
                    do{
                        cout << "\n--- MENU ALUMNO ---\n";
                        cout << "1. Enviar mensaje\n";
                        cout << "2. Ver mensajes\n";
                        cout << "0. Salir\n";
                        cout << "Opción: ";
                        cin >> op;

                        switch(op){
                            case 1: enviarMensaje(u.getUsuario()); break;
                            case 2: verMensajes(u.getUsuario()); break;
                            case 0: break;
                            default: cout << "Opción no válida\n";
                        }

                    } while (op != 0);
                }
                break;

            case 2:
                u.crearCuenta();
                break;

            case 3:
                u.recuperarPassword();
                break;

            case 0:
                cout << "Saliendo del sistema...\n";
                break;

            default:
                cout << "Opción no válida\n";
        }

    } while (opcion != 0);

    return 0;
}
