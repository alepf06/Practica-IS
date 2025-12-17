#include "sistema.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// ==================================================
// FUNCIONES AUXILIARES
// ==================================================

// Simula si un usuario está conectado
static bool usuarioConectado(const std::string& usuario) {
    // Simulación simple: usuarios con 'A' están conectados
    return !usuario.empty() && usuario[0] == 'A';
}

// --------------------------------------------------

// Guarda mensaje entregado
static void registrarMensaje(const std::string& emisor,
                             const std::string& receptor,
                             const std::string& texto) {

    std::ofstream archivo("data/mensajes.txt", std::ios::app);
    if (!archivo.is_open()) {
        std::cerr << "[Chat] Error al escribir mensajes.txt\n";
        return;
    }

    archivo << emisor << " -> " << receptor << ": "
            << texto << "\n";
    archivo.close();
}

// --------------------------------------------------

// Guarda mensaje pendiente
static void guardarPendiente(const std::string& emisor,
                             const std::string& receptor,
                             const std::string& texto) {

    std::ofstream archivo("data/pendientes.txt", std::ios::app);
    if (!archivo.is_open()) {
        std::cerr << "[Chat] Error al escribir pendientes.txt\n";
        return;
    }

    archivo << emisor << " -> " << receptor << ": "
            << texto << "\n";
    archivo.close();
}

// ==================================================
// IMPLEMENTACIÓN DEL CASO DE USO CU-03
// ==================================================

void ejecutarModuloMensajeria(Usuario& usuarioActual) {

    std::string emisor = usuarioActual.getNombreUsuario();

    std::cout << "\n=== CANAL DE MENSAJERÍA ===\n";
    std::cout << "Usuario: " << emisor << "\n";

    // 1. Mostrar bandeja (simulada)
    std::cout << "\n[Bandeja de mensajes]\n";
    std::ifstream bandeja("data/mensajes.txt");
    if (bandeja.is_open()) {
        std::string linea;
        while (std::getline(bandeja, linea)) {
            if (linea.find(emisor) != std::string::npos) {
                std::cout << linea << "\n";
            }
        }
        bandeja.close();
    }
    else {
        std::cout << "(Sin mensajes)\n";
    }

    // 2. Seleccionar destinatario
    std::string receptor;
    std::cout << "\nIntroduce destinatario: ";
    std::cin >> receptor;

    // 3. Redactar mensaje
    std::cin.ignore();
    std::string mensaje;
    std::cout << "Escribe el mensaje: ";
    std::getline(std::cin, mensaje);

    // 4. Enviar mensaje
    std::cout << "Enviando mensaje...\n";

    // Simulación de fallo del servidor
    bool servidorActivo = true;
    if (!servidorActivo) {
        std::cout << "ERROR: Servidor de mensajería no disponible.\n";
        std::cout << "Reintentando cuando se restablezca...\n";
        return;
    }

    // 5. Receptor conectado / desconectado
    if (usuarioConectado(receptor)) {
        registrarMensaje(emisor, receptor, mensaje);
        std::cout << "Mensaje entregado a " << receptor << "\n";
    }
    else {
        guardarPendiente(emisor, receptor, mensaje);
        std::cout << "Usuario desconectado. Mensaje almacenado.\n";
    }

    std::cout << "=== FIN DEL CHAT ===\n";
}
