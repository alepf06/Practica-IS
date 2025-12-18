add_library(sistema clases.cc chat.cc asignacion.cc alerta.cc sistema.h)
target_include_directories(sistema PUBLIC ${CMAKE_CURRENT_LIST_DIR})
add_executable(main-sistema main-sistema.cc)
target_link_libraries(main-sistema PUBLIC sistema)
