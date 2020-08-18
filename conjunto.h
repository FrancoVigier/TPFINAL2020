#ifndef CONJUNTO_H_INCLUDED 
#define CONJUNTO_H_INCLUDED
#include "LSE.h"
#include "intervalo.h"
#include "parser.h"
#include "operaciones.h"

/**
* Inicializamos un conjunto
*/
Conjunto inicializar_conjunto(char* alias, char* operacion);

/**
* Creamos un conjunto por listas por copia
*/
Conjunto crear_conjunto(char* alias, GList lista, GList intervaloLista);

/**
* Dada una definicion por comprension creo un intervalo
* y lo cargo a un Conjunto parametro
*/
void extraer_com_conjunto(char* operacion, Conjunto conjunto);

/**
* Defino un conjunto por comprension
*/
Conjunto definir_conj_com(char* operacion, char* alias);

/**
* Definimos un conjunto por extension
*/
Conjunto definir_conj_ext(char* operacion, char* alias);

/**
* Imprimimos un conjunto
*/
void mostrar_conjunto_imprimir(Conjunto muestro);

/**
* Liberamos la memoria de un Conjunto
*/
void destruir_conjunto(Conjunto conjunto);
#endif // CONJUNTO_H_INCLUDED
