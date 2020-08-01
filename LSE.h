#ifndef LSE_H_INCLUDED
#define LSE_H_INCLUDED
#include <malloc.h>

typedef struct _GNodo { //
  void* data;
  struct _GNodo* next;
} GNodo;

typedef GNodo* GList ;
typedef struct GNodo* list;

typedef struct _Conjunto {
  char* alias;
  int comprenExtens; // 1->{10,1,2} 2->{x | x<4} //2 ocurrencias
  GList lista;
  int abiertoCerrado; // 1->[] 2->() 3->[) 4->(] //2 ocurrencias
  GList intervaloLista;
  int extInferior; //2 ocurrencias
  int extSuperior; // ocurrencias
  int vacio;
}* Conjunto;

typedef void (*Visitante) (void *, void*);


GList initialization_glist();
GList alloc_gnodo();
GList prepend_glist(GList lista, void* data);
GList dlist_eliminar_primero(GList lista);
void* dnodo_dato(GList nodo);
GList dlist_selectionSort(GList lista);
void dlist_intercambiar(GList nodoA, GList nodoB);
int empty_glist(GList lista);
int largo_glist(GList lista);
void* get_data_glist(GList lista, int pos);
GList pisa_data_glist(GList lista, int pos, void* data);
struct _GNodo* glist_copiar_lista(struct _GNodo* head);
struct _GNodo* eliminar_glist_char(struct _GNodo* lista, char* dato);
struct _GNodo* eliminar_glist(struct _GNodo* lista, Conjunto dato);
struct _GNodo* buscar(struct _GNodo* lista, Conjunto pala);
GList pisa_data_glist_nopos(GList lista, Conjunto data);
int esta_data_glist(GList lista, Conjunto data);
void dlist_destruir (GList lista, Visitante liberar);
void dlist_destruir_int(GList lista);
void dlist_destruir_intervalo(GList lista);
#endif // LSE_H_INCLUDED
