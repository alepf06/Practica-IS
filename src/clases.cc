#include "sistema.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Usuario::Usuario() {
    intentos_ = 0;
}

bool Usuario::login() {
    string u, p;
    while(intentos_<3){
    ifstream f("general.txt");
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
return false;
}

bool Usuario::crearCuenta(){
    ifstream f("general.txt");
    string u, p, r, linea;

    cout << "--- CREAR CUENTA ---\n";
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

    // 2. BUCLE DE VALIDACIÓN DEL ROL
    // Repetirá la pregunta hasta que el usuario escriba una opción válida
    bool rolValido = false;
    do {
        cout << "Rol (Alumno/Tutor/Coordinador): ";
        cin >> r;

        // Comprobamos que sea exactamente una de las 3 opciones (respetando mayúsculas)
        if (r == "Alumno" || r == "Tutor" || r == "Coordinador") {
            rolValido = true;
        } else {
            cout << "Error: Rol no válido. Escribe 'Alumno', 'Tutor' o 'Coordinador' tal cual.\n";
        }

    } while (!rolValido);

    // 3. Guardar en fichero
    ofstream out("general.txt", ios::app);
    out << u << ";" << p << ";" << r << endl;
    out.close();

    cout << ">> Cuenta creada correctamente como " << r << ".\n";
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
