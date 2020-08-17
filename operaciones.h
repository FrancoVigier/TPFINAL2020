#ifndef OPERACIONES_H_INCLUDED
#define OPERACIONES_H_INCLUDED

#include "pila.h"
#include "conjunto.h"
#include "LSE.h"
#include "intervalo.h"
#include "parser.h"
#include "hash.h"

#define LIMITE 300
#define INT_SUPLIM 32767
#define INT_INFLIM -32767
#define LIST_LIM 10
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

GList conjunto_union(GList intervalos);
GList aplanar_lista(Conjunto primero);
GList concatenar_glist (GList listaA, GList listaB);
void mostrar_intervalo(GList intervall);

GList definir_conj_union(Conjunto primero, Conjunto segundo);

GList conjunto_inters( Conjunto primero, Conjunto segundo);
GList conjunto_diferencia_dos(GList intervaloA, Intervalo* intervaloB);
GList definir_conj_dif_dos(Conjunto primero, Conjunto segundo);
void mostrar(GList lista);
void mostrar_glist(GList lista);
void mostrar_glist_intervalos(GList lista);
#endif // OPERACIONES_H_INCLUDED
