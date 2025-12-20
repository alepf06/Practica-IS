#include "sistema.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits> // Necesario para limpiar el buffer

using namespace std;

void evaluarAlumno() {
    string alumno, tutor = "NO ASIGNADO";
    float nota;
    int asistencia;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Limpieza de buffer y lectura de datos

    cout << "--- Evaluar Alumno ---\n";
    cout << "Alumno: ";
    getline(cin, alumno);
    
    cout << "Nota media: ";
    cin >> nota;
    
    cout << "Asistencia (%): ";
    cin >> asistencia;

    // Buscar tutor del alumno en asignaciones.txt
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
    }   else {
        cout << "[Aviso] No se pudo leer asignaciones.txt. Se registrará sin tutor.\n";
    }

    if (nota < 5.0 || asistencia < 75) {
        ofstream f("alertas.txt", ios::app);
        if (f.is_open()) {
            f << alumno << ";" << tutor << ";";
            
            // Construir mensaje de detalle
            string motivos = "";
            if (nota < 5.0) motivos += "Suspenso (" + to_string(nota).substr(0,3) + ") ";
            if (asistencia < 75) motivos += "Baja Asistencia (" + to_string(asistencia) + "%)";
            
            f << motivos << endl;
            f.close();
            
            cout << ">> ALERTA GENERADA: El alumno está en riesgo. Tutor notificado (" << tutor << ").\n";
        } else {
            cout << "Error: No se pudo guardar la alerta en el archivo.\n";
        }
    } else {
        cout << ">> El alumno tiene buen rendimiento. No se generó alerta.\n";
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
    f.close();

    if (!alertasEncontradas) {
        cout << "No hay alertas para tus alumnos.\n";
    }
    cout << "===============================\n";
}
