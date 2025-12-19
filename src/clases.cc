#include "sistema.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Usuario::Usuario() {
    intentos_ = 0;
}

bool Usuario::login() {
    ifstream f("general.txt");
    string u, p;
    while(intentos_<=3){
    cout << "Usuario: "; cin >> u;
    cout << "Contraseña: "; cin >> p;

    string linea;
    while (getline(f, linea)) {
        stringstream ss(linea);
        getline(ss, usuario_, ';');
        getline(ss, contraseña_, ';');
        getline(ss, rol_, ';');

        if (usuario_ == u && contraseña_ == p) {
            ofstream log("general.txt", ios::app);
            log << "LOGIN;" << usuario_ << endl;
            log.close();
            return true;
        }
    }

    intentos_++;
    if (intentos_ == 3) {
        cout << "Cuenta bloqueada por seguridad\n";
        return false;
    } else {
        cout << "Credenciales incorrectas\n";
    }
}
}

bool Usuario::crearCuenta(){
    ifstream f("general.txt");
    string u, p, r, linea;

    cout << "Nuevo usuario: ";
    cin >> u;

    // Comprobar si ya existe
    while (getline(f, linea)) {
        stringstream ss(linea);
        getline(ss, usuario_, ';');

        if (usuario_ == u) {
            cout << "El usuario ya existe\n";
            f.close();
            return false;
        }
    }
    f.close();

    cout << "Contraseña: ";
    cin >> p;
    cout << "Rol (Alumno/Tutor/Coordinador): ";
    cin >> r;

    ofstream out("general.txt", ios::app);
    out << u << ";" << p << ";" << r << endl;
    out.close();

    cout << "Cuenta creada correctamente\n";
    return true;
}

void Usuario::recuperarPassword() {
    ifstream f("general.txt");
    string u, linea;

    cout << "Introduce tu usuario: ";
    cin >> u;

    while (getline(f, linea)) {
        stringstream ss(linea);
        getline(ss, usuario_, ';');
        getline(ss, contraseña_, ';');

        if (usuario_ == u) {
            cout << "Tu contraseña es: " << contraseña_ << endl;
            f.close();
            return;
        }
    }

    f.close();
    cout << "Usuario no encontrado\n";
}