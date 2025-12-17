#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// ==========================================
// CLASE BASE: USUARIO
// ==========================================
class Usuario{

    protected:
            /*Atributos marcados como 'protected' para permitir que las clases hijas
            (Tutor, Alumno, Coordinador) accedan a ellos directamente si es necesario.*/

            std::string nombre_usuario_;
            std::string contrasena_;
            std::string correo_;
            std::string nombre_;
            std::string apellidos_;
            int edad_;

    public:
            //Constructor Parametrizado: Inicializa todos los datos básicos del usuario.
            Usuario(std::string nombre_usuario, std::string contrasena,
                std::string correo, std::string nombre, std::string apellidos, int edad);
                
            /* Constructor por Defecto.
                Necesario para crear arreglos de objetos o instancias temporales antes de cargar datos. */
            Usuario(){}
            
            virtual ~Usuario(){} /*Destructor Virtual: Asegura que se borren correctamente los objetos hijos 
                                (Alumno, Tutor) cuando se manejan como genéricos (Usuario)*/
            
            //Getters (Accesores) de información común
            std::string getNombreUsuario() const {return nombre_usuario_;}
            std::string getNombreCompleto() const {return nombre_ + " " + apellidos_;}
            
            //Registra un nuevo usuario en el fichero 'usuarios.txt'
            void Crear_cuenta(std::string tipo_usuario);

            //Verifica las credenciales
            void Iniciar_sesion();

            //Simula el envío de correo para recuperación de clave
            std::string Recuperar_contrasena();
};

// ==========================================
// CLASE : TUTOR
// ==========================================
class Tutor : public Usuario{

        private:
                //Atributos específicos del rol de Tutor
                std::string id_tutor_;
                std::string asignaturas_impartidas_;
                int alumnos_asignados_;
        
        public:
                //Constructor que inicializa la parte de Usuario + la parte de Tutor
                Tutor(std::string nombre_usuario, std::string contrasena,
                std::string correo, std::string nombre, std::string apellidos, int edad,
                std::string id_tutor, std::string asignaturas_impartidas);

                Tutor(){} /*Constructor por Defecto: Permite crear un objeto de la clase
                        Tutor sin necesidad de darle valores iniciales inmediatos.*/
                
                //Getter necesario para la lógica de asignación
                std::string getIdTutor() const {return id_tutor_;}
                
                //Permite visualizar la lista de alumnos a cargo
                void Gestionar_alumnos();

                //Inicia un Chat con un alumno específico
                void Contactar_alumno(std::string id_alumno);
};

// ==========================================
// CLASE : ALUMNO
// ==========================================
class Alumno : public Usuario{

        private:
                // Atributos estrictos según manual.
                // NOTA: No se incluye 'id_tutor' como atributo persistente en memoria,
                // la relación se gestiona externamente o por ficheros
                std::string id_alumno_;
                std::string asignaturas_;
                int curso_;
                std::string carrera_;
        
        public:
                Alumno(std::string nombre_usuario, std::string contrasena,
                std::string correo, std::string nombre, std::string apellidos, int edad,
                std::string id_alumno, std::string carrera, int curso);

                Alumno(){} /*Constructor por Defecto: Permite crear un objeto de la clase
                        Alumno sin necesidad de darle valores iniciales inmediatos.*/
                
                //Helpers para obtener datos en los módulos de lógica
                std::string getIdAlumno() const {return id_alumno_;}
                std::string getCarrera() const {return carrera_;}

                //Devuelve un string formateado con curso y asignaturas (Útil para módulo Avisos)
                std::string getDatosAcademicos() const {return "Curso: " + std::to_string(curso_) + ", Asignaturas: " + asignaturas_;}
                
                //Busca quién es su tutor asignado e inicia contacto
                void Preguntar_tutor();
};

// ==========================================
// CLASE : ALUMNO
// ==========================================
class Coordinador : public Usuario{

        private:
                //Atributo estricto según manual
                std::string id_coordinador_;
        
        public:
                Coordinador(std::string nombre_usuario, std::string contrasena,
                std::string correo, std::string nombre, std::string apellidos, int edad,
                std::string id_coordinador);
                
                //Ejecuta la lógica de la Asignación Automática/Manual
                void Asignar_tutores(); 

                //Genera reportes de rendimiento
                std::string Solicitar_informe();
};

// ==========================================
// CLASE AUXILIAR: ALERTAS
// ==========================================
class Alertas{

        private:
                // Atributos estrictos según manual
                std::string id_alerta_;
                std::string destinatario_;
                std::string informacion_;
        
        public:
                Alertas(std::string destinatario, std::string informacion);
                
                //Guarda la alerta en fichero y notifica en consola
                void Enviar_alerta();
};

// ==========================================
// CLASE AUXILIAR: CHAT
// ==========================================
class Chat{

        private:
                // Atributos estrictos según manual
                std::string id_chat_;
                std::string fecha_inicio_;
                std::string fecha_finalizacion_;
                std::string mensajes_;
                int miembros_;
        
        public:
                Chat();

                //Establece la conexión inicial entre dos usuarios
                void Iniciar_chat(std::string usuario1, std::string usuario2);

                //Cierra la sesión de chat y guarda registro
                void Finalizar_chat();

                //Permite registrar el texto enviado
                void Enviar_mensaje(std::string emisor, std::string destinatario, std::string texto);
};

// ==========================================
// CLASE AUXILIAR: INFORMES
// ==========================================
class Informes{

    private:
            // Atributos estrictos según manual
            std::string id_informe_;
            std::string filtros_;
            std::string informacion_;

    public:
            Informes(std::string id_informe, std::string filtros, std::string informacion);
            Informes() {} /*Constructor por Defecto: Permite crear un objeto de la clase
                        Informes sin necesidad de darle valores iniciales inmediatos.*/

            //Guarda los datos del informe generado en un archivo de texto
            void Guardar_informe();
};

/* Prototipos globales */

// Implementa la lógica de Asignación de Tutores
void ejecutarModuloAsignacion(Coordinador& coord);

// Implementa la lógica de Mensajería Instantánea
void ejecutarModuloMensajeria(Usuario& usuarioActual);

// Implementa la lógica del Sistema de Avisos
void ejecutarModuloAvisos(Tutor& tutorActual);

#endif