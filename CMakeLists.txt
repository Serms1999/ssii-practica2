cmake_minimum_required(VERSION 3.0)
project(ssii_practica2)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/..)

link_libraries("-static")

include_directories(.)

add_executable(
        Practica2
        Funciones.cpp
        Funciones.hpp
        leerFicheros.cpp
        leerFicheros.hpp
        SBR.cpp
)
