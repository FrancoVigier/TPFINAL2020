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

GList initialization_glist();
GList alloc_gnodo();
GList prepend_glist(GList lista, void* data);
GList glist_eliminar_primero(GList lista);
void* gnodo_dato(GList nodo);
GList glist_selection_sort(GList lista);
void glist_intercambiar(GList nodoA, GList nodoB);
int empty_glist(GList lista);
int largo_glist(GList lista);
void* get_data_glist(GList lista, int pos);
struct _GNodo* glist_copiar_lista(struct _GNodo* head);
GList pisa_data_glist_nopos(GList lista, Conjunto data);
void glist_destruir (GList lista, Visitante liberar);
void glist_destruir_int(GList lista);
void glist_destruir_intervalo(GList lista);
#endif // LSE_H_INCLUDED
