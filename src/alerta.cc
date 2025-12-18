#include "sistema.h"
#include <fstream>
#include <iostream>

using namespace std;

void evaluarAlumno(){
    string alumno;
    float nota;
    int asistencia;

    cout << "Alumno: ";
    cin >> alumno;
    cout << "Nota media: ";
    cin >> nota;
    cout << "Asistencia (%): ";
    cin >> asistencia;

    if (nota < 5 || asistencia < 75){
        ofstream f("alertas.txt", ios::app);
        f << alumno << ";RIESGO ACADEMICO";
        if (nota < 5) f << "Nota baja ";
        if (asistencia < 75) f << "Baja asistencia";
        f << endl;
        f.close();

        cout << "Alerta generada automáticamente\n";
    }
    else{
        cout << "Alumno sin riesgo\n";
    }
}

void verAlertas(string usuario){
    ifstream f("alertas.txt");
    string linea;
    while (getline(f, linea))
        if(linea.find(usuario) != string::npos)
            cout << linea << endl;
}