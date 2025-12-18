cmake_minimum_required(VERSION 3.10)

project(SistemaTutorizacion)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif (MSVC)
    add_compile_options(/W4)
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(test)


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
