#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <vector>

using namespace std;

// ==========================================
// CLASE BASE: USUARIO
// ==========================================
class Usuario{

    protected:
            /*Atributos marcados como 'protected' para permitir que las clases hijas
            (Tutor, Alumno, Coordinador) accedan a ellos directamente si es necesario.*/

            string usuario_;
            string contraseña_;
            string rol_;
            int intentos_;

    public:
            
            Usuario();
            bool login();
            string getUsuario(){ return usuario_; }
            string getRol(){ return rol_; }
            bool crearCuenta();
            void recuperarPassword();
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
                // NUEVAS FUNCIONES
                void listarUsuariosPorRol(string rolBuscado); 
                void asignacionAutomatica();
};

/* Prototipos globales */

void enviarMensaje(string emisor);
void verMensajes(string usuario);
void evaluarAlumno();        // genera alertas automáticas
void verAlertas(string usuario);

#endif
