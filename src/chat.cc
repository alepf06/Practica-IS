#include "sistema.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void enviarMensaje(string emisor){
    string receptor;
    string mensaje;
    cout << "Receptor: ";
    cin >> receptor;
    cin.ignore();
    cout << "Mensaje: ";
    getline(cin, mensaje);

    ofstream f("mensajes.txt", ios::app);
    f << emisor << ";" << receptor << ";" << mensaje << endl;
    f.close();
}

void verMensajes(string usuario){
    ifstream f("mensajes.txt");
    if (!f.is_open()) {
        cout << "No se puede abrir el archivo de mensajes.\n";
        return;
    }

    string linea;
    bool encontrados = false;
    cout << "===== Mensajes de " << usuario << " =====\n";

    while (getline(f, linea)) {
        stringstream ss(linea);
        string emisor, receptor, mensaje;

        getline(ss, emisor, ';');
        getline(ss, receptor, ';');
        getline(ss, mensaje);

        if (usuario == emisor || usuario == receptor) {
            encontrados = true;
            cout << "---------------------------\n";
            cout << "De: " << emisor << "\n";
            cout << "Para: " << receptor << "\n";
            cout << "Mensaje: " << mensaje << "\n";
        }
    }

    if (!encontrados) {
        cout << "No hay mensajes para mostrar.\n";
    }
    cout << "===============================\n";
}
