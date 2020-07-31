#include <string.h>

#include "LSE.h"
#include "conjunto.h"
#include "intervalo.h"
GList initialization_glist() {
  return NULL;
}

GList alloc_gnodo() {
  GNodo* gn = malloc(sizeof(struct _GNodo));
  return gn;
}

GList prepend_glist(GList list, void* data) {
  GList newList;
  newList = alloc_gnodo();
  newList->data = data;
  newList->next = list;
  return newList;
}

GList dlist_eliminar_primero(GList lista) {
  if (lista == NULL)
    return lista;
  GList nuevoInicio = lista->next;
  free (lista);
  return nuevoInicio;
}

void* dnodo_dato(GList nodo) {
  return nodo->data;
}

int funcion_comparacio(Intervalo* a, Intervalo* b) {
  return a->inicio < b->inicio;
}

GList dlist_selectionSort(GList lista) {
  GList nodo = lista;
  for (;nodo->next != NULL; nodo = nodo->next) {
    // Guardo en aux el nodo que tenga el dato menor segun la comparacion.
    GList aux = nodo;
    // Itero sobre el siguiente elemento de la lista
    GList nodo2 = nodo->next;
    for (;nodo2 != NULL; nodo2 = nodo2->next) {
      // Si el nodo sobre el que se itera es menor al guardado, lo guardo.
      if (funcion_comparacio(nodo2->data, aux->data)){
        aux = nodo2;
      }
    }
    // Si hubo cambios en el nodo auxiliar, entonces intercambio los valores.
    if (aux != nodo) {
      dlist_intercambiar(nodo, aux);
    }
  }
  return lista;
}

void dlist_intercambiar(GList nodoA, GList nodoB) {// Intercambio los punteros de los nodos que contienen los datos.
  void* nodoC = nodoB->data;
  nodoB->data = nodoA->data;
  nodoA->data = nodoC;
}

int empty_glist(GList lista) {
  return lista == NULL;
}

int largo_glist(GList lista) {
  int largo = 0;
  for (GList start = lista; !empty_glist(start); start = start->next) largo++;
  return largo;
}

void* get_data_glist(GList lista, int pos) {
  GList tmp = NULL;
  while (pos-- > 0 && lista) {
    tmp = lista->next;
    lista = NULL;
    lista = tmp;
    tmp = NULL;
  }
  return lista ? lista->data : 0;
}

GList pisa_data_glist(GList lista, int pos, void* data) {
  int largo = 0;
  if (lista == NULL){
    return NULL;
  }
  GList start = lista;
  for (; !empty_glist(lista); lista = lista->next, largo++){
    if (largo == pos) {
      lista->data = data;
    }
  }
  return start;
}

struct _GNodo* glist_copiar_lista(struct _GNodo* head) {
  struct _GNodo* current = head;	// used to iterate over original list
  struct _GNodo* newList = NULL; // head of the new list
  struct _GNodo* tail = NULL;	// point to last node in new list
  while (current != NULL) {// special case for the first new Node
    if (newList == NULL) {
      newList = (struct _GNodo*)malloc(sizeof(struct _GNodo));
      newList->data = current->data;
      newList->next = NULL;
      tail = newList;
    } else {
      tail->next = (struct _GNodo*)malloc(sizeof(struct _GNodo));
      tail = tail->next;
      tail->data = current->data;
      tail->next = NULL;
    }
    current = current->next;
  }
  dlist_destruir(tail, NULL);
  dlist_destruir(current, NULL);
  return newList;
}

struct _GNodo* eliminar_glist_char(struct _GNodo* lista, char* dato) {
  GList ptr = lista;
  GList anterior = NULL;
  while (ptr != NULL) {
    Conjunto extraer = malloc(sizeof(struct _Conjunto));
    extraer = ptr->data;
    if (strcmp(extraer->alias, dato) == 0) {
      if (anterior) {
        anterior->next = ptr->next;
      } else {
        lista = ptr->next;
      }
      GList borrarAuxiliar = ptr;
      ptr = ptr->next;
      free (borrarAuxiliar);
    } else {
      anterior = ptr;
      ptr = ptr->next;
    }
  }
  return lista;
}

struct _GNodo* eliminar_glist(struct _GNodo* lista, Conjunto dato) {
  GList ptr = lista;
  GList anterior = NULL;
  while (ptr != NULL) {
    Conjunto extraer = malloc(sizeof(struct _Conjunto));
    extraer = ptr->data;
    if (strcmp(extraer->alias, dato->alias) == 0) {
      if (anterior) {
        anterior->next = ptr->next;
      } else {
        lista = ptr ->next;
      }
      GList borrarAuxiliar = ptr;
      ptr = ptr->next;
      free (borrarAuxiliar);
    } else {
      anterior = ptr;
      ptr = ptr->next;
    }
  }
  return lista;
}

struct _GNodo* buscar(struct _GNodo* lista, Conjunto pala) {
  if (lista == NULL)
    return NULL;
  struct _GNodo * listaNum = NULL;
  GList start = lista;
  for (; lista != NULL; lista = lista->next) {
    Conjunto ver = lista->data;
    if (strcmp(pala->alias, ver->alias) == 0) {
      listaNum = prepend_glist(listaNum, ver);
    }
  }
  lista = start;
  return listaNum;
}

GList pisa_data_glist_nopos(GList lista, Conjunto data) {
  if (lista == NULL) {
    return NULL;
  }
  GList start = lista;
  for (; !empty_glist(lista); lista = lista->next) {
    Conjunto ver = lista->data;
    if (strcmp(ver->alias, data->alias) == 0) {
        lista->data = data;
    }
  }
  return start;
}

int esta_data_glist(GList lista, Conjunto data) {
  if (lista == NULL) {
    return 0;
  }
  for (; !empty_glist(lista); lista = lista->next) {
    Conjunto ver = lista->data;
    if (strcmp(ver->alias, data->alias) == 0) {
      return 1;
    }
  }
  return 0;
}

void dlist_destruir(GList lista, Visitante liberar) {
  GList proximo = lista;
  GList actual;
  for (; proximo != NULL;) {
    // Guardo un puntero al nodo actual, me muevo al siguiente y libero.
    actual = proximo;
    proximo = proximo->next;
    if (liberar != NULL)
      liberar(actual->data, NULL);
    free(actual);
  }
}
