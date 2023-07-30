cmake_minimum_required(VERSION 3.0)
project(ssii_practica2)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/..)

include_directories(.)

add_executable(
        ssii_practica2
        Funciones.cpp
        Funciones.hpp
        leerFicheros.cpp
        leerFicheros.hpp
        SBR.cpp
)
