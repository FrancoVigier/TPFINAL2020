#include <stdio.h>
#include <string.h>
#include <math.h>

#include "hash.h"

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
  switch (caracter) {
      return caracter - '0';
  }
}

int hasheo_uno(char* palabra) {
  int largo = strlen(palabra);
  int suma = 0;
  for (int indice = 0; indice < largo; indice++) {
    suma += codigo_ascii(palabra[indice]) * pow(2, indice);
  }
  return suma % 37;
}

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

void free_table(struct _GNodo*** table) {
  for (int i = 0; i < 37; i++) {
    for (int j = 0; j < 37; j++) {
      glist_destruir(table[i][j], (Visitante)destruir_conjunto);
    }
  free (table[i]);
  }
  free (table);
}