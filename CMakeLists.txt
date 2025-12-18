cmake_minimum_required(VERSION 3.10)

project(SistemaTutorizacion)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCES
    main-sistema.cc
    clases.cc
    asignacion.cc
    chat.cc
    alerta.cc
)

add_executable(SistemaTutorizacion ${SOURCES})
