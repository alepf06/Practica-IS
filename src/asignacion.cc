#include "sistema.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

// ==================================================
// FUNCIONES AUXILIARES (PROVISIONALES)
// ==================================================

static bool leerGeneral(std::vector<std::string>& alumnos,
                        std::vector<std::string>& tutores) {

    std::ifstream archivo("data/general.txt");
    if (!archivo.is_open()) {
        std::cerr << "[Asignacion] No se pudo abrir data/general.txt\n";
        return false;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string tipo, id, nombre, apellidos;

        std::getline(ss, tipo, ';');
        std::getline(ss, id, ';');
        std::getline(ss, nombre, ';');
        std::getline(ss, apellidos, ';');

        if (tipo == "ALUMNO") {
            alumnos.push_back(id + " - " + nombre + " " + apellidos);
        }
        else if (tipo == "TUTOR") {
            tutores.push_back(id + " - " + nombre + " " + apellidos);
        }
    }

    archivo.close();
    return true;
}

// --------------------------------------------------

static void actualizarAsignaciones(const std::string& alumno,
                                   const std::string& tutor) {

    std::map<std::string, std::string> asignaciones;
    std::ifstream entrada("data/asignaciones.txt");

    if (entrada.is_open()) {
        std::string linea;
        while (std::getline(entrada, linea)) {
            size_t pos = linea.find(" -> ");
            if (pos != std::string::npos) {
                asignaciones[linea.substr(0, pos)] =
                    linea.substr(pos + 4);
            }
        }
        entrada.close();
    }

    // Inserta o reasigna
    asignaciones[alumno] = tutor;

    std::ofstream salida("data/asignaciones.txt", std::ios::trunc);
    for (const auto& par : asignaciones) {
        salida << par.first << " -> " << par.second << "\n";
    }
    salida.close();
}

// ==================================================
// IMPLEMENTACIÓN DEL CASO DE USO CU-02
// ==================================================

void ejecutarModuloAsignacion(Coordinador& /*coord*/) {

    std::vector<std::string> alumnos;
    std::vector<std::string> tutores;

    if (!leerGeneral(alumnos, tutores)) {
        std::cout << "No se pudo cargar el sistema de usuarios.\n";
        return;
    }

    if (alumnos.empty()) {
        std::cout << "No hay alumnos registrados.\n";
        return;
    }

    if (tutores.empty()) {
        std::cout << "No hay tutores disponibles.\n";
        return;
    }

    int opcion;
    std::cout << "\n=== ASIGNACIÓN DE TUTORES ===\n";
    std::cout << "1. Asignación automática\n";
    std::cout << "2. Asignación manual\n";
    std::cout << "Seleccione opción: ";
    std::cin >> opcion;

    // ------------------------------
    // ASIGNACIÓN AUTOMÁTICA
    // ------------------------------
    if (opcion == 1) {
        for (size_t i = 0; i < alumnos.size(); ++i) {
            std::string tutor = tutores[i % tutores.size()];
            actualizarAsignaciones(alumnos[i], tutor);
            std::cout << alumnos[i] << " asignado a " << tutor << "\n";
        }
    }

    // ------------------------------
    // ASIGNACIÓN MANUAL
    // ------------------------------
    else if (opcion == 2) {

        for (const auto& alumno : alumnos) {
            std::cout << "\nAlumno: " << alumno << "\n";
            for (size_t i = 0; i < tutores.size(); ++i) {
                std::cout << i + 1 << ". " << tutores[i] << "\n";
            }

            int sel;
            std::cout << "Seleccione tutor (0 para omitir): ";
            std::cin >> sel;

            if (sel > 0 && sel <= (int)tutores.size()) {
                actualizarAsignaciones(alumno, tutores[sel - 1]);
            }
        }
    }

    else {
        std::cout << "Opción inválida.\n";
    }

    std::cout << "Asignación finalizada.\n";
}
