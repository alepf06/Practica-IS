#include "Sistema.h"
#include <sstream>

// ==========================================
// CONSTRUCTOR 
// ==========================================
Usuario::Usuario(std::string nombre_usuario, std::string contrasena,
                 std::string correo, std::string nombre,
                 std::string apellidos, int edad)
{
    nombre_usuario_ = nombre_usuario;
    contrasena_ = contrasena;
    correo_ = correo;
    nombre_ = nombre;
    apellidos_ = apellidos;
    edad_ = edad;
}

// ==========================================
// CREAR CUENTA
// ==========================================
void Usuario::Crear_cuenta(std::string tipo_usuario)
{
    std::ifstream fichero_lectura("general.txt");
    std::string linea;

    // 1. Comprobar si el usuario ya existe
    if (fichero_lectura.is_open()) {
        while (getline(fichero_lectura, linea)) {
            std::string tipo, usuario;

            std::stringstream ss(linea);
            getline(ss, tipo, ';');
            getline(ss, usuario, ';');

            if (usuario == nombre_usuario_) {
                std::cout << "El nombre de usuario ya existe.\n";
                fichero_lectura.close();
                return;
            }
        }
        fichero_lectura.close();
    }

    // 2. Si no existe, crear la cuenta
    std::ofstream fichero_escritura("general.txt", std::ios::app);

    if (!fichero_escritura.is_open()) {
        std::cout << "Error al abrir el fichero.\n";
        return;
    }

    fichero_escritura << tipo_usuario << ";"
                      << nombre_usuario_ << ";"
                      << contrasena_ << ";"
                      << correo_ << ";"
                      << nombre_ << ";"
                      << apellidos_ << ";"
                      << edad_ << std::endl;

    fichero_escritura.close();

    std::cout << "Cuenta creada correctamente.\n";
}

// ==========================================
// INICIAR SESIÓN
// ==========================================
void Usuario::Iniciar_sesion()
{
    std::ifstream fichero("general.txt");
    std::string linea;

    if (!fichero.is_open()) {
        std::cout << "Error al abrir el fichero.\n";
        return;
    }

    bool encontrado = false;

    while (getline(fichero, linea)) {
        std::string tipo, usuario, clave;

        std::stringstream ss(linea);
        getline(ss, tipo, ';');
        getline(ss, usuario, ';');
        getline(ss, clave, ';');

        if (usuario == nombre_usuario_ && clave == contrasena_) {
            encontrado = true;
            break;
        }
    }

    fichero.close();

    if (encontrado) {
        std::cout << "Inicio de sesión correcto.\n";
    } else {
        std::cout << "Usuario o contraseña incorrectos.\n";
    }
}

// ==========================================
// RECUPERAR CONTRASEÑA
// ==========================================
std::string Usuario::Recuperar_contrasena()
{
    std::ifstream fichero("general.txt");
    std::string linea;

    if (!fichero.is_open()) {
        return "Error al abrir el fichero.";
    }

    while (getline(fichero, linea)) {
        std::string tipo, usuario, clave, correo;

        std::stringstream ss(linea);
        getline(ss, tipo, ';');
        getline(ss, usuario, ';');
        getline(ss, clave, ';');
        getline(ss, correo, ';');

        if (usuario == nombre_usuario_ && correo == correo_) {
            fichero.close();
            return "La contraseña es: " + clave;
        }
    }

    fichero.close();
    return "Usuario no encontrado.";
}
