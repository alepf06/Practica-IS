#include "sistema.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits> // Para numeric_limits

using namespace std;

// Función auxiliar para verificar si el usuario existe en general.txt
bool usuarioExiste(string nombreBuscado) {
    ifstream f("general.txt");
    if (!f.is_open()) return false;

    string linea, u;
    // Leemos línea por línea
    while (getline(f, linea)) {
        stringstream ss(linea);
        getline(ss, u, ';'); // El usuario es el primer campo
        
        if (u == nombreBuscado) {
            f.close();
            return true;
        }
    }
    f.close();
    return false;
}

void enviarMensaje(string emisor){
    string receptor;
    string mensaje;
    cout << "Receptor: ";
    cin >> receptor;

    // CORRECCIÓN IMPORTANTE: Limpiar el buffer antes del getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Mensaje: ";
    getline(cin, mensaje);

    // Validar que no se envíe vacío
    if(mensaje.empty()) {
        cout << "Error: El mensaje no puede estar vacío.\n";
        return;
    }
    
    ofstream f("mensajes.txt", ios::app);
    if(f.is_open()){
        f << emisor << ";" << receptor << ";" << mensaje << endl;
        f.close();
        cout << ">> Mensaje enviado correctamente.\n";
    } else {
        cout << "Error: No se pudo escribir en mensajes.txt\n";
    }
}

void verMensajes(string usuario){
    ifstream f("mensajes.txt");
    if (!f.is_open()) {
        cout << "No hay historial de mensajes (o no se pudo abrir el archivo).\n";
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
            cout << (emisor == usuario ? "Yo" : emisor) << " -> " 
                 << (receptor == usuario ? "Mí" : receptor) << ":\n";
            cout << "   \"" << mensaje << "\"\n";
        }
    }
    f.close();

    if (!encontrados) {
        cout << "Buzón vacío.\n";
    }
    cout << "===============================\n";
}
