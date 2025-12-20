#include "sistema.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm> // Para find

using namespace std;

// Función auxiliar para ver listas (Soluciona "listar alumnos y tutores")
void Coordinador::listarUsuariosPorRol(string rolBuscado) {
    ifstream f("general.txt");
    string linea, u, p, r;
    
    cout << "Listado de " << rolBuscado << "s disponibles:\n";
    bool hay = false;
    while(getline(f, linea)){
        stringstream ss(linea);
        getline(ss, u, ';');
        getline(ss, p, ';');
        getline(ss, r, ';');
        
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
    cout << "Alumno: ";
    cin >> alumno;

    ofstream f("asignaciones.txt", ios::app);
    if(f.is_open()){
        f << tutor << ";" << alumno << endl;
        f.close();
        cout << ">> Asignación guardada exitosamente.\n";
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
    string linea, u, p, r;
    while(getline(fGen, linea)){
        stringstream ss(linea);
        getline(ss, u, ';'); 
        getline(ss, p, ';'); 
        getline(ss, r, ';');
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
            alumnosYaAsignados.push_back(a);
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

        if(!yaTieneTutor){
            // Asignar al siguiente tutor (Round Robin)
            string tutorAsignado = tutores[tutorIndex];
            
            fOut << tutorAsignado << ";" << alumno << endl;
            cout << "Asignando " << alumno << " -> " << tutorAsignado << endl;
            
            asignadosCount++;
            tutorIndex = (tutorIndex + 1) % tutores.size(); // Ciclar tutores
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
