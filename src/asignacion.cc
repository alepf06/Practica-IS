#include "sistema.h"
#include <fstream>
#include <iostream>

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
    string linea;
    while (getline(f, linea))
        cout << linea << endl;
}