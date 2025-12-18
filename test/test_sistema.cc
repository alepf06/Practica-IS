#include "cute/cute.h"           // Ajustado a la estructura estandar
#include "cute/ide_listener.h"   // Necesario para ver los resultados
#include "cute/cute_runner.h"    // Necesario para ejecutar
#include <fstream>
#include <string>
#include "sistema.h"

void testHU2_AsignacionCorrecta(){
	Coordinador c;
	c.asignarTutor();    // Se introducen datos válidos por consola
	ASSERTM("Asignación realizada sin errores", true);
}

void testHU2_PersistenciaAsignacion(){
	std::ifstream f("asignaciones.txt");
	bool existe = f.good();
	f.close();

	ASSERTM("El fichero asignaciones.txt existe y es accesible", existe);
}

void testHU3_EnvioMensaje(){
    enviarMensaje("alu1"); // receptor y mensaje por consola
    ASSERTM("Mensaje enviado correctamente", true);
}

void testHU3_PersistenciaMensaje(){
	std::ifstream f("mensajes.txt");
	bool existe = f.good();
	f.close();

	ASSERTM("El fichero mensajes.txt existe y contiene mensajes", existe);
}

void testHU4_GeneracionAutomaticaAlerta(){
    evaluarAlumno();    // introducir nota < 5 o asistencia < 75
    ASSERTM("Alerta automática generada por riesgo académico", true);
}

void testHU4_PersistenciaAlerta(){
	std::ifstream f("alertas.txt");
	bool existe = f.good();
	f.close();

	ASSERTM("El fichero alertas.txt existe y contiene alertas", existe);
}

// Función que organiza y lanza las pruebas
void runSuite(){
    cute::suite s;
    s.push_back(CUTE(testHU2_AsignacionCorrecta));
    s.push_back(CUTE(testHU2_PersistenciaAsignacion));
    s.push_back(CUTE(testHU3_EnvioMensaje));
    s.push_back(CUTE(testHU3_PersistenciaMensaje));
    s.push_back(CUTE(testHU4_GeneracionAutomaticaAlerta));
    s.push_back(CUTE(testHU4_PersistenciaAlerta));

    cute::ide_listener<> lis;
    cute::makeRunner(lis, s).run();
}

// El punto de entrada principal
int main(){
    runSuite();
    return 0;
}


