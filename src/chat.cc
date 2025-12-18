#include "sistema.h"
#include <fstream>
#include <iostream>

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
    string linea;
    while (getline(f, linea))
        if(linea.find(usuario) != string::npos)
            cout << linea << endl;
}