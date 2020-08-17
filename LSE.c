#include <string.h>
#include <stdio.h>
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

GList prepend_glist(GList lista, void* data) {
  GList nuevaLista;
  nuevaLista = alloc_gnodo();
  nuevaLista->data = data;
  nuevaLista->next = lista;
  return nuevaLista;
}

GList glist_eliminar_primero(GList lista) {
  if (lista == NULL)
    return lista;
  GList nuevoInicio = lista->next;
  free (lista);
  return nuevoInicio;
}

void* gnodo_dato(GList nodo) {
  return nodo->data;
}

int funcion_comparacio(Intervalo* primero, Intervalo* segundo) {
  return primero->inicio < segundo->inicio;
}

GList glist_selection_sort(GList lista) {
  GList nodo = lista;
  for (;nodo->next != NULL; nodo = nodo->next) {
    GList aux = nodo;
    GList nodo2 = nodo->next;
    for (;nodo2 != NULL; nodo2 = nodo2->next) {
      if (funcion_comparacio(nodo2->data, aux->data)) {
        aux = nodo2;
      }
    }
    if (aux != nodo) {
      glist_intercambiar(nodo, aux);
    }
  }
  return lista;
}

void glist_intercambiar(GList nodoA, GList nodoB) {
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

struct _GNodo* glist_copiar_lista(struct _GNodo* cabecera) {
  struct _GNodo* actual = cabecera;
  struct _GNodo* nuevaCabecera = NULL;
  struct _GNodo* nuevoCuerpo = NULL;
  while (actual != NULL) {
    if (nuevaCabecera == NULL) {
      nuevaCabecera = (struct _GNodo*)malloc(sizeof(struct _GNodo));
      nuevaCabecera->data = actual->data;
      nuevaCabecera->next = NULL;
      nuevoCuerpo = nuevaCabecera;
    } else {
      nuevoCuerpo->next = (struct _GNodo*)malloc(sizeof(struct _GNodo));
      nuevoCuerpo = nuevoCuerpo->next;
      nuevoCuerpo->data = actual->data;
      nuevoCuerpo->next = NULL;
    }
    actual = actual->next;
	}
	return nuevaCabecera;
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

void glist_destruir(GList lista, Visitante liberar) {
  GList proximo = lista;
  GList actual;
  for (; proximo != NULL;) {
    actual = proximo;
    proximo = proximo->next;
    if (liberar != NULL) {
      liberar((Conjunto)actual->data, NULL);
    }
    free (actual);
  }
  lista = NULL;
}

void glist_destruir_int(GList lista){
  GList proximo = lista;
  GList actual;
  for (; proximo != NULL;) {
    actual = proximo;
    proximo = proximo->next;
    free (actual);
  }
  lista = NULL;
  }

void glist_destruir_intervalo(GList lista){
  GList proximoDos = lista;
  GList actualDos;
  for (; proximoDos != NULL;) {
    actualDos = proximoDos;
    proximoDos = proximoDos->next;
    Intervalo* data = actualDos->data;
    free (data);
    free (actualDos);
  }
}
