cmake_minimum_required(VERSION 3.0)
project(ssii_practica2)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(ssii_practica2
        Funciones.cpp
        Funciones.h
        leerFicheros.cpp
        leerFicheros.h
        SBR.cpp)
