#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
using namespace std;


// ==========================================
// CLASE BASE: USUARIO
// ==========================================
class Usuario{

    protected:
            /*Atributos marcados como 'protected' para permitir que las clases hijas
            (Tutor, Alumno, Coordinador) accedan a ellos directamente si es necesario.*/

            string usuario;
            string password;
            string rol;
            int intentos;

    public:
            
            Usuario();
            bool login();
            string getUsuario();
            string getRol();
};

// ==========================================
// CLASE : TUTOR
// ==========================================
class Tutor : public Usuario{
        
        public:
                void menu();
};

// ==========================================
// CLASE : ALUMNO
// ==========================================
class Alumno : public Usuario{

        public:
                void menu();
};

// ==========================================
// CLASE : COORDINADOR
// ==========================================
class Coordinador : public Usuario{
        
        public:
                void menu();
                void asignarTutor();
                void verAsignaciones();
};

/* Prototipos globales */

void enviarMensaje(string emisor);

void verMensajes(string usuario);

void evaluarAlumno();        // genera alertas automáticas

void verAlertas(string usuario);

#endif