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
        if (!f.is_open()) {
            cout << "Error: No existe general.txt. Crea una cuenta primero.\n";
            return false;
        }
        
    cout << "Usuario: "; cin >> u;
    cout << "Contraseña: "; cin >> p;

    string linea;
    bool loginExitoso = false;
    
    while (getline(f, linea)) {
        stringstream ss(linea);
        // Declaramos variables AQUÍ para que se limpien en cada vuelta
        string userFile, passFile, roleFile;
        
        getline(ss, userFile, ';');
        getline(ss, passFile, ';');
        getline(ss, roleFile, ';');

        if (userFile == u && passFile == p) {
        // Rellenamos los datos del objeto
            usuario_ = userFile;
            contraseña_ = passFile;
            rol_ = roleFile;
                
            loginExitoso = true;
            break; // Dejamos de leer el fichero
        }
     }
    f.close();

    if (loginExitoso) {
        // ELIMINADO: Ya no escribimos "LOGIN" en general.txt para no romperlo
        return true;
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
    if (f.is_open()) {
        while (getline(f, linea)) {
            stringstream ss(linea);
            string userFile;
            getline(ss, userFile, ';');

            if (userFile == u) {
                cout << "Error: El usuario '" << u << "' ya existe.\n";
                f.close();
                return false;
            }
        }
        f.close();
    }

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
    if (!f.is_open()) {
        cout << "No hay usuarios registrados.\n";
        return;
    }

    string u, linea;
    cout << "Introduce tu usuario para recuperar la contraseña: ";
    cin >> u;

    bool encontrado = false;
    while (getline(f, linea)) {
        stringstream ss(linea);
        string userFile, passFile; // Variables locales
        
        getline(ss, userFile, ';');
        getline(ss, passFile, ';');
        // No necesitamos el rol aquí

        if (userFile == u) {
            cout << "Tu contraseña es: " << passFile << endl;
            encontrado = true;
            break;
        }
    }
    f.close();

    if (!encontrado) {
        cout << "Usuario no encontrado.\n";
    }
}
