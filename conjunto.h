#ifndef CONJUNTO_H_INCLUDED
#define CONJUNTO_H_INCLUDED

#include "LSE.h"
#include "intervalo.h"
#include "parser.h"
#include "operaciones.h"

#define INT_SUPLIM 32767
#define INT_INFLIM -32767

Conjunto inicializar_conjunto(char* alias, char* operacion);
Conjunto crear_conjunto(char* alias, GList lista, GList intervaloLista);
void extraer_com_conjunto(char* operacion, Conjunto conjunto);
Conjunto definir_conj_com(char* operacion, char* alias);
Conjunto definir_conj_ext(char* operacion, char* alias);
void mostrar_conjunto(Conjunto muestro);
void mostrar_conjunto_imprimir(Conjunto muestro);
void destruir_conjunto(Conjunto conjunto, void* aux);
#endif // CONJUNTO_H_INCLUDED
