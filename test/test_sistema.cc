#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "sistema.h"

// =======================
// HU2 Asignación tutor
// =======================

TEST(testHU2, AsignacionCorrecta){
    Coordinador c;
    c.asignarTutor();   // Se introducen datos válidos por consola
    SUCCEED();          // Si no hay crash, el test pasa
}

TEST(testHU2, PersistenciaAsignacion){
    std::ifstream f("asignaciones.txt");
    bool existe = f.good();
    f.close();

    EXPECT_TRUE(existe) << "El fichero asignaciones.txt existe y es accesible";
}

// =======================
// HU3 Mensajería
// =======================

TEST(testHU3, EnvioMensaje){
    enviarMensaje("alu1"); // receptor y mensaje por consola
    SUCCEED();
}

TEST(testHU3, PersistenciaMensaje){
    std::ifstream f("mensajes.txt");
    bool existe = f.good();
    f.close();

    EXPECT_TRUE(existe) << "El fichero mensajes.txt existe y contiene mensajes";
}

// =======================
// HU4 Alertas automáticas
// =======================

TEST(testHU4, GeneracionAutomaticaAlerta){
    evaluarAlumno();   // introducir nota < 5 o asistencia < 75
    SUCCEED();
}

TEST(testHU4, PersistenciaAlerta){
    std::ifstream f("alertas.txt");
    bool existe = f.good();
    f.close();

    EXPECT_TRUE(existe) << "El fichero alertas.txt existe y contiene alertas";
}
