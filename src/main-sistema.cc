#include "sistema.h"
#include <iostream>

using namespace std;

int main(){
    Usuario u;
    if (!u.login()) return 0;

    int op;
    if (u.getRol() == "COORDINADOR"){
        Coordinador c;
        do{
            cout << "1. Asignar tutor\n2.Ver asignaciones\n3.Evaluar alumno\n0.Salir\n";
            cin >> op;
            if (op == 1) c.asignarTutor();
            if (op == 2) c.verAsignaciones();
            if (op == 3) evaluarAlumno();
        } while (op != 0);
    }
    else{
        do{
            cout << "1.Enviar mensaje\n2.Ver mensajes\n3.Ver alertas\n0.Salir\n";
            cin >> op;
            if (op == 1) enviarMensaje(u.getUsuario());
            if (op == 2) verMensajes(u.getUsuario());
            if (op == 3) verAlertas(u.getUsuario());
        } while (op != 0);
    }
    return 0;
}