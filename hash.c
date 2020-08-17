#include <stdio.h>
#include <string.h>
#include <math.h>

#include "hash.h"
//Inicializo cada posicion de mi tabla hash
struct _GNodo *** inicializar_HASH() {
  struct _GNodo*** HASH;
  HASH = (struct _GNodo ***)malloc(37 * sizeof(struct _GNodo**));
  for (int prime = 0; prime < 37; prime++) {
    HASH[prime] = (struct _GNodo**)malloc(37 * sizeof(struct _GNodo*));
    for (int segu = 0; segu < 37; segu++) {
      HASH[prime][segu] = NULL;
    }
  }
  return HASH;
}

int codigo_ascii(char caracter) {
  return caracter - '0';
}

//Funcion de hash 1
int hasheo_uno(char* palabra) {
  int largo = strlen(palabra);
  int suma = 0;
  for (int indice = 0; indice < largo; indice++) {
    suma += codigo_ascii(palabra[indice]) * pow(2, indice);
  }
  return suma % 37;
}

//Funcion de hash 2
int hasheo_dos(char* palabra) {
  int largo = strlen(palabra);
  int subind = 0, suma = 0;
  for (int indice = 0; indice < largo; indice++) {
    if (indice != 0) {
      suma += codigo_ascii(palabra[indice]) * pow(2, subind++);
    }
  }
  return suma % 37;
}

//Buscamos en la tabla hash un elemento
Conjunto hash_busco(struct _GNodo*** hash, char* alias) {
  int keyUno = hasheo_uno(alias);
  int keyDos = hasheo_dos(alias);
  GList aux = hash[keyUno][keyDos];
  for (; aux != NULL; aux = aux->next) {
    Conjunto ver = aux->data;
    if (strcmp(ver->alias, alias) == 0) {
      return ver;
    }
  }
  return NULL;
}

//Insertamos en una tabla hash
void hash_inserto(struct _GNodo*** hash, char* nom, GList lista, GList iLista) {
  Conjunto conju = crear_conjunto(nom, lista, iLista);

  int keyUno = hasheo_uno(nom);
  int keyDos = hasheo_dos(nom);
  if (hash_busco(hash, nom) == NULL) {
    hash[keyUno][keyDos] = prepend_glist(hash[keyUno][keyDos], conju);
  } else {
      hash[keyUno][keyDos] = pisa_data_glist_nopos(hash[keyUno][keyDos], conju);
    }
  return;
}

//Liberacion de memoria de la tabla
void free_table(struct _GNodo*** table) {
  for (int indiceI = 0; indiceI < 37; indiceI++) {
    for (int indiceJ = 0; indiceJ < 37; indiceJ++) {
      glist_destruir(table[indiceI][indiceJ], (Visitante)destruir_conjunto);
    }
  free (table[indiceI]);
  }
  free (table);
}
