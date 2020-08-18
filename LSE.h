#ifndef LSE_H_INCLUDED
#define LSE_H_INCLUDED
#include <malloc.h>

typedef struct _GNodo {
  void* data;
  struct _GNodo* next;
} GNodo;

typedef GNodo* GList ;
typedef struct GNodo* list;

typedef struct _Conjunto {
  char* alias;
  GList lista;
  GList intervaloLista;
  int vacio;
}* Conjunto;

typedef void (*Visitante) (void*, void*);

/**
* Inicializamos una LSE
*/
GList initialization_glist();

/**
* Designamos memoria al nodo de una LSE
*/
GList alloc_gnodo();

/**
* Agregamos un dato al comienzo de una LSE
*/
GList prepend_glist(GList lista, void* data);

/**
* Eliminamos el primer nodo de una LSE
*/
GList glist_eliminar_primero(GList lista);

/**
* Devolvemos la data de un nodo de una LSE
*/
void* gnodo_dato(GList nodo);

/**
* Ordenamiento de lista, selection sort
*/
GList glist_selection_sort(GList lista);

/**
* Intercambiamos las datas de dos nodos
*/
void glist_intercambiar(GList nodoA, GList nodoB);

/**
* Verificador de si una lista es vacia o no
*/
int empty_glist(GList lista);

/**
* Calculamos el largo de una LSE
*/
int largo_glist(GList lista);

/**
* Dada una posicion, devolvemos la data del nodo
* de una LSE en dicha pos
*/
void* get_data_glist(GList lista, int pos);

/**
* Copiamos una LSE
*/
struct _GNodo* glist_copiar_lista(struct _GNodo* inicio);

/**
* Dada una LSE y un Conjunto, si el Conjunto esta
* en la LSE lo pisa si no lo esta no hace nada
*/
GList pisa_data_glist_nopos(GList lista, Conjunto data);

/**
* Liberamos memoria de una LSE, con funcion Visitante
*/
void glist_destruir (GList lista, Visitante liberar);

/**
* Destruimos el "esqueleto" de una LSE su estructura
* pero no su data
*/
void glist_destruir_int(GList lista);

/**
* Liberamos memoria de una LSE de Intervalos
*/
void glist_destruir_intervalo(GList lista);
#endif // LSE_H_INCLUDED

