#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include "LSE.h"
#include "conjunto.h"

/**
* Inicializo cada posicion de mi tabla hash
*/
struct _GNodo *** inicializar_HASH();

/**
* Dado un caracter devuelvo su codigo ascii menos el
* del '0'
*/
int codigo_ascii(char a);

/**
* Funcion de hash 1
*/
int hasheo_uno(char* palabra);

/**
* Funcion de hash 2
*/
int hasheo_dos(char* palabra);

/**
* Insertamos en una tabla hash
*/
void hash_inserto(struct _GNodo*** hash, char* nom, GList lista, GList iLista);

/**
* Buscamos en la tabla hash un elemento
*/
Conjunto hash_busco(struct _GNodo*** hash, char* alias);

/**
* Liberacion de memoria de la tabla
*/
void free_table(struct _GNodo*** table);
#endif // HASH_H_INCLUDED
