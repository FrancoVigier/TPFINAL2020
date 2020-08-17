cmake_minimum_required(VERSION 3.15)
project(EdDyA_I_Vallejos_Vigier C)

set(CMAKE_C_STANDARD 99)

add_executable(EdDyA_I_Vallejos_Vigier main.c conjunto.c conjunto.h hash.c hash.h intervalo.c intervalo.c LSE.c LSE.h operaciones.c operaciones.h parser.c parser.h pila.c pila.h)
