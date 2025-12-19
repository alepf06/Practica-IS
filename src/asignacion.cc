#include "sistema.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void Coordinador::asignarTutor(){
    string tutor;
    string alumno;
    cout << "Tutor: ";
    cin >> tutor;
    cout << "Alumno: ";
    cin >> alumno;

    ofstream f("asignaciones.txt", ios::app);
    f << tutor << ";" << alumno <<endl;
    f.close();
    
    cout << "Asignación realizada\n";
}

void Coordinador::verAsignaciones(){
    ifstream f("asignaciones.txt");
    if (!f.is_open()) {
        cout << "No se puede abrir el archivo de asignaciones.\n";
        return;
    }

    string linea;
    int contador = 1;
    cout << "===== Asignaciones Tutor-Alumno =====\n";

    while (getline(f, linea)) {
        stringstream ss(linea);
        string tutor, alumno;
        getline(ss, tutor, ';');
        getline(ss, alumno);

        cout << "---------------------------\n";
        cout << contador << ". Tutor: " << tutor << "\n";
        cout << "   Alumno: " << alumno << "\n";
        contador++;
    }

    if (contador == 1) {
        cout << "No hay asignaciones registradas.\n";
    }

    cout << "===============================\n";
}