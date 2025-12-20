#include "sistema.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm> // Para find

using namespace std;

// =========================================================
// FUNCIÓN AUXILIAR (Privada de este archivo)
// Comprueba si existe un usuario con un ROL específico
// =========================================================
bool existeUsuarioYRol(string nombre, string rolEsperado) {
    ifstream f("general.txt");
    if (!f.is_open()) return false;

    string linea, u, p, r;
    while (getline(f, linea)) {
        // Filtro de seguridad: saltar líneas vacías
        if (linea.empty()) continue;
        
        stringstream ss(linea);
        getline(ss, u, ';'); // Usuario
        getline(ss, p, ';'); // Contraseña
        getline(ss, r, ';'); // Rol

        // Filtro de seguridad: Si el rol no es válido, ignoramos la línea (ej. LOGIN)
        if (r != "Alumno" && r != "Tutor" && r != "Coordinador") continue;

        // Comprobamos nombre Y rol
        if (u == nombre && r == rolEsperado) {
            f.close();
            return true;
        }
    }
    f.close();
    return false;
}

// Función auxiliar para ver listas (Soluciona "listar alumnos y tutores")
void Coordinador::listarUsuariosPorRol(string rolBuscado) {
    ifstream f("general.txt");
    if (!f.is_open()) return;
    
    string linea, u, p, r;
    
    cout << "Listado de " << rolBuscado << "s disponibles:\n";
    bool hay = false;
    while(getline(f, linea)){
        
        stringstream ss(linea);

        getline(ss, u, ';');
        getline(ss, p, ';');
        getline(ss, r, ';');

        // Limpiamos caracteres invisibles (opcional, pero útil en Windows/Linux)
        if (!r.empty() && r.back() == '\r') r.pop_back();
        
        if(r == rolBuscado){
            cout << "- " << u << endl;
            hay = true;
        }
    }
    if(!hay) cout << "(No hay usuarios registrados con este rol)\n";
    f.close();
}

void Coordinador::asignarTutor(){
    // Mostramos listas antes de pedir datos para ayudar al usuario
    listarUsuariosPorRol("Tutor");
    cout << "----------------\n";
    listarUsuariosPorRol("Alumno");
    cout << "----------------\n";
    
    string tutor;
    string alumno;
    
    cout << "Tutor: ";
    cin >> tutor;
    
    // --- AQUÍ ESTABA EL ERROR: Faltaba esta comprobación ---
    if (existeUsuarioYRol(tutor, "Tutor") == false) {
        cout << "ERROR: El usuario '" << tutor << "' no existe o no es un Tutor.\n";
        cout << "Asignación cancelada.\n";
        return; // Salimos de la función sin guardar nada
    }
    
    cout << "Alumno: ";
    cin >> alumno;

    // --- Validación del Alumno ---
    if (existeUsuarioYRol(alumno, "Alumno") == false) {
        cout << "ERROR: El usuario '" << alumno << "' no existe o no es un Alumno.\n";
        cout << "Asignación cancelada.\n";
        return; // Salimos de la función sin guardar nada
    }

    //Verificar si el alumno YA tiene tutor (opcional pero recomendado)
    ifstream fCheck("asignaciones.txt");
    if (fCheck.is_open()) {
    string linea, t, a;
    while(getline(fCheck, linea)){
        stringstream ss(linea);
        getline(ss, t, ';');
        getline(ss, a);
        if(a == alumno){
            cout << "AVISO: El alumno " << alumno << " ya tenía asignado al tutor " << t << ".\n"; 
            // Aquí podrías poner un return si quieres prohibir reasignaciones
        }
    }
    fCheck.close();
}

    ofstream f("asignaciones.txt", ios::app);
    if(f.is_open()){
        f << tutor << ";" << alumno << endl;
        f.close();
        cout << ">> Asignación guardada exitosamente: " << tutor << " -> " << alumno << endl;
    } else {
        cout << "Error crítico: No se pudo abrir asignaciones.txt\n";
    }
}

// NUEVA FUNCIÓN: Asignación Automática
void Coordinador::asignacionAutomatica(){
    vector<string> tutores;
    vector<string> alumnos;
    vector<string> alumnosYaAsignados;

    // 1. Cargar Tutores y Alumnos desde general.txt
    ifstream fGen("general.txt");
    if (!fGen.is_open()) {
        cout << "Error: No se encuentra general.txt\n";
        return;
    }
    
    string linea, u, p, r;
    while(getline(fGen, linea)){
        if (linea.empty()) continue;
        
        stringstream ss(linea);
        getline(ss, u, ';'); 
        getline(ss, p, ';'); 
        getline(ss, r, ';');

        // Limpieza de formato (CRLF)
        if (!r.empty() && r.back() == '\r') r.pop_back();
        
        if(r == "Tutor") tutores.push_back(u);
        else if(r == "Alumno") alumnos.push_back(u);
    }
    fGen.close();

    if(tutores.empty()) {
        cout << "No hay tutores registrados para repartir.\n";
        return;
    }

    // 2. Ver quiénes ya tienen asignación
    ifstream fAsign("asignaciones.txt");
    if(fAsign.is_open()){
        while(getline(fAsign, linea)){
            stringstream ss(linea);
            string t, a;
            getline(ss, t, ';');
            getline(ss, a, ';');
            if (!a.empty()) {
                alumnosYaAsignados.push_back(a);
            }
        }
        fAsign.close();
    }

    // 3. Repartir alumnos libres
    ofstream fOut("asignaciones.txt", ios::app);
    int tutorIndex = 0;
    int asignadosCount = 0;

    for(const auto& alumno : alumnos){
        // Verificar si el alumno ya está en la lista de asignados
        bool yaTieneTutor = false;
        for(const auto& asignado : alumnosYaAsignados){
            if(asignado == alumno) {
                yaTieneTutor = true;
                break;
            }
        }

        // Solo asignamos si NO tiene tutor
        if(!yaTieneTutor){
            // Asignar al siguiente tutor (Round Robin)
            string tutorAsignado = tutores[tutorIndex];
            
            fOut << tutorAsignado << ";" << alumno << endl;
            cout << "Asignando " << alumno << " -> " << tutorAsignado << endl;
            
            asignadosCount++;
            tutorIndex = (tutorIndex + 1) % tutores.size();
            }
        }
    fOut.close();
    

    if(asignadosCount > 0)
        cout << ">> Se han realizado " << asignadosCount << " asignaciones automáticas.\n";
    else
        cout << "Todos los alumnos ya tenían tutor asignado.\n";
}

void Coordinador::verAsignaciones(){
    ifstream f("asignaciones.txt");
    if (!f.is_open()) {
        cout << "No se puede abrir el archivo de asignaciones.\n";
        return;
    }

    string linea;
    cout << "===== Asignaciones Actuales =====\n";
    while (getline(f, linea)) {
        stringstream ss(linea);
        string tutor, alumno;
        getline(ss, tutor, ';');
        getline(ss, alumno); // Lee hasta el final
        if(!tutor.empty() && !alumno.empty())
            cout << "Tutor: " << tutor << " | Alumno: " << alumno << endl;
    }
    f.close();
    cout << "=================================\n";
}
