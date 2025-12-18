cmake_minimum_required(VERSION 3.10)

project(SistemaTutorizacion)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif (MSVC)
    add_compile_options(/W4)
endif()

include_directories(${PROJECT_SOURCE_DIR})

set(COMMON_SOURCES
    clases.cc
    asignacion.cc
    chat.cc
    alerta.cc
)

add_executable(SistemaTutorizacion
    main-sistema.cc
    ${COMMON_SOURCES}
)

option(BUILD_TESTS "Compilar pruebas CUTE" ON)

if (BUILD_TESTS)
    enable_testing()

    add_executable(TestSistema
        test_sistema.cpp
        ${COMMON_SOURCES}
    )

    # Registrar las pruebas en CTest
    add_test(
        NAME PruebasSistemaTutorizacion
        COMMAND TestSistema
    )
endif()

# Compilar solo el sistema:
#   mkdir build
#   cd build
#   cmake ..
#   make
# Ejecucion: ./SistemaTutorizacion

# Compilar también las pruebas CUTE (activado por defecto):
#   cmake -DBUILD_TESTS=ON ..
#   make
#   ctest

# Si NO se quiere compilar las pruebas: cmake -DBUILD_TESTS=OFF ..
