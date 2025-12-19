#include "sistema.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void evaluarAlumno() {
    string alumno;
    float nota;
    int asistencia;

    cout << "Alumno: ";
    cin >> alumno;
    cout << "Nota media: ";
    cin >> nota;
    cout << "Asistencia (%): ";
    cin >> asistencia;

    // Buscar tutor del alumno en asignaciones.txt
    string tutor = "NO ASIGNADO";
    ifstream fAsign("asignaciones.txt");
    if (fAsign.is_open()) {
        string linea;
        while (getline(fAsign, linea)) {
            stringstream ss(linea);
            string t, a;
            getline(ss, t, ';');
            getline(ss, a);
            if (a == alumno) {
                tutor = t;
                break;
            }
        }
        fAsign.close();
    }

    if (nota < 5 || asistencia < 75) {
        ofstream f("alertas.txt", ios::app);
        f << alumno << ";" << tutor << ";RIESGO ACADEMICO";
        if (nota < 5) f << " Nota baja";
        if (asistencia < 75) f << " Baja asistencia";
        f << endl;
        f.close();   
    }
}

void verAlertas(string t) {
    ifstream f("alertas.txt");
    if (!f.is_open()) {
        cout << "No se puede abrir el archivo de alertas.\n";
        return;
    }

    string linea;
    bool alertasEncontradas = false;
    cout << "===== Alertas de tus alumnos =====\n";

    while (getline(f, linea)) {
        stringstream ss(linea);
        string alumno, tutor, detalles;

        getline(ss, alumno, ';');
        getline(ss, tutor, ';');
        getline(ss, detalles);

        if (tutor == t) {
            alertasEncontradas = true;
            cout << "---------------------------\n";
            cout << "Alumno: " << alumno << "\n";
            cout << "Alerta: " << detalles << "\n";
        }
    }

    if (!alertasEncontradas) {
        cout << "No hay alertas para tus alumnos.\n";
    }

    cout << "===============================\n";
}