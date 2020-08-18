#ifndef OPERACIONES_H_INCLUDED
#define OPERACIONES_H_INCLUDED

#include "pila.h"
#include "conjunto.h"
#include "LSE.h"
#include "intervalo.h"
#include "parser.h"
#include "hash.h"

#define LIMITE 300
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/**
* Dada una lista de intervalos, devuelve una sin solapamientos
*/
GList conjunto_union(GList intervalos);

/**
* Dada un Conjunto, mergea sus listas de componentes
* Conjunto->lista y Conjunto->intervaloLista a una sola
* lista de intervalos
*/
GList aplanar_lista(Conjunto primero);

/**
* Dada dos listas, devuelve la concatenacion de ellas
*/
GList concatenar_glist (GList listaA, GList listaB);

/**
* Dado dos conjuntos, devuelve la unión de ellos
*/
GList definir_conj_union(Conjunto primero, Conjunto segundo);

/**
* Dados dos conjuntos, devuelve la interseccion de ellos
*/
GList conjunto_inters( Conjunto primero, Conjunto segundo);

/**
* Dada una lista de intervalos y un intervalo, devuelve
* todos los elementos que pertenecen a la lista y no al
* intervalo solitario
*/
GList conjunto_diferencia_dos(GList intervaloA, Intervalo* intervaloB);

/**
* Dados dos conjuntos, devuelve la resta de ellos
*/
GList definir_conj_dif_dos(Conjunto primero, Conjunto segundo);

#endif // OPERACIONES_H_INCLUDED
