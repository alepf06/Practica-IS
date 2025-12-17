#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Usuario{

    protected:
            std::string nombre_usuario_;
            std::string contrasena_;
            std::string correo_;
            std::string nombre_;
            std::string apellidos_;
            int edad_;

    public:
            Usuario(std::string nombre_usuario, std::string contrasena,
                std::string correo, std::string nombre, std::string apellidos, int edad);
        
            Usuario(){} /*Constructor por Defecto: Permite crear un objeto de la clase
                        Usuario sin necesidad de darle valores iniciales inmediatos.*/
            
            virtual ~Usuario(){} /*Destructor Virtual: Asegura que se borren correctamente los objetos hijos 
                                (Alumno, Tutor) cuando se manejan como genéricos (Usuario)*/
            
            std::string getNombreUsuario() const {return nombre_usuario_;}
            std::string getNombreCompleto() const {return nombre_ + " " + apellidos_;}

            void Crear_cuenta(std::string tipo_usuario);
            void Iniciar_sesion();
            std::string Recuperar_contrasena();
};


class Tutor : public Usuario{

        private:
                std::string id_tutor_;
                std::string asignaturas_impartidas_;
                int alumnos_asignados_;
        
        public:
                Tutor(std::string nombre_usuario, std::string contrasena,
                std::string correo, std::string nombre, std::string apellidos, int edad,
                std::string id_tutor, std::string asignaturas_impartidas);

                Tutor(){} /*Constructor por Defecto: Permite crear un objeto de la clase
                        Tutor sin necesidad de darle valores iniciales inmediatos.*/
                
                std::string getIdTutor() const {return id_tutor_;}
                
                void Gestionar_alumnos();
                void Contactar_alumno(std::string id_alumno);
};

class Alumno : public Usuario{

        private:
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
                
                std::string getIdAlumno() const {return id_alumno_;}
                std::string getCarrera() const {return carrera_;}
                std::string getDatosAcademicos() const {return "Curso: " + to_string(curso_) + ", Asignaturas: " + asignaturas_;}
                
                void Preguntar_tutor();
};

class Coordinador : public Usuario{

        private:
                std::string id_coordinador_;
        
        public:
                Coordinador(std::string nombre_usuario, std::string contrasena,
                std::string correo, std::string nombre, std::string apellidos, int edad,
                std::string id_coordinador);

                void Asignar_tutores(); 
                std::string Solicitar_informe();
};

class Alertas{

        private:
                std::string id_alerta_;
                std::string destinatario_;
                std::string informacion_;
        
        public:
                Alertas(std::string destinatario, std::string informacion);

                void Enviar_alerta();
};

class Chat{

        private:
                std::string id_chat_;
                std::string fecha_inicio_;
                std::string fecha_finalizacion_;
                std::string mensajes_;
                int miembros_;
        
        public:
                Chat();

                void Iniciar_chat(std::string usuario1, std::string usuario2);
                void Finalizar_chat();

                void Enviar_mensaje(std::string emisor, std::string destinatario, std::string texto);
};

class Informes{

    private:
            std::string id_informe_;
            std::string filtros_;
            std::string informacion_;

    public:
            Informes(std::string id_informe, std::string filtros, std::string informacion);
            Informes() {} /*Constructor por Defecto: Permite crear un objeto de la clase
                        Informes sin necesidad de darle valores iniciales inmediatos.*/

            void Guardar_informe();
};

//Prototipos globales
void ejecutarModuloAsignacion(Coordinador& coord);
void ejecutarModuloMensajeria(Usuario& usuarioActual);
void ejecutarModuloAvisos(Tutor& tutorActual);

#endif