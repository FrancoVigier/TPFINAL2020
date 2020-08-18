#include <string.h>
#include <stdio.h> 
#include "LSE.h"
#include "conjunto.h"
#include "intervalo.h"

/**
* Inicializamos una LSE
*/
GList initialization_glist() {
  return NULL;
}

/**
* Designamos memoria al nodo de una LSE
*/
GList alloc_gnodo() {
  GNodo* gn = malloc(sizeof(struct _GNodo));
  return gn;
}

/**
* Agregamos un dato al comienzo de una LSE
*/
GList prepend_glist(GList lista, void* data) {
  GList nuevaLista;
  nuevaLista = alloc_gnodo();
  nuevaLista->data = data;
  nuevaLista->next = lista;
  return nuevaLista;
}

/**
* Eliminamos el primer nodo de una LSE
*/
GList glist_eliminar_primero(GList lista) {
  if (lista == NULL)
    return lista;
  GList nuevoInicio = lista->next;
  free (lista);
  return nuevoInicio;
}

/**
* Devolvemos la data de un nodo de una LSE
*/
void* gnodo_dato(GList nodo) {
  return nodo->data;
}

/**
* Comparamos si un intervalo es menor a otro por su ext.inf
*/
int funcion_comparacio(Intervalo* primero, Intervalo* segundo) {
  return primero->inicio < segundo->inicio;
}

/**
* Ordenamiento de lista, selection sort
*/
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

/**
* Intercambiamos las datas de dos nodos
*/
void glist_intercambiar(GList nodoA, GList nodoB) {
  void* nodoC = nodoB->data;
  nodoB->data = nodoA->data;
  nodoA->data = nodoC;
}

/**
* Verificador de si una lista es vacia o no
*/
int empty_glist(GList lista) {
  return lista == NULL;
}

/**
* Calculamos el largo de una LSE
*/
int largo_glist(GList lista) {
  int largo = 0;
  for (GList start = lista; !empty_glist(start); start = start->next) largo++;
  return largo;
}

/**
* Dada una posicion, devolvemos la data del nodo
* de una LSE en dicha pos
*/
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

/**
* Copiamos una LSE
*/
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

/**
* Dada una LSE y un Conjunto, si el Conjunto esta
* en la LSE lo pisa si no lo esta no hace nada
*/
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

/**
* Liberamos memoria de una LSE, con funcion Visitante
*/
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

/**
* Destruimos el "esqueleto" de una LSE su estructura
* pero no su data
*/
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

/**
* Liberamos memoria de una LSE de Intervalos
*/
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
