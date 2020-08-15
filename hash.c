#include <stdio.h>
#include <string.h>
#include <math.h>
#include "LSE.h"
#include "conjunto.h"

struct _GNodo *** inicializar_HASH() {
  struct _GNodo*** HASH;
  HASH = (struct _GNodo ***)malloc(37*sizeof(struct _GNodo**));
  for (int i = 0; i < 37; i++) {
    HASH[i] = (struct _GNodo**)malloc(37*sizeof(struct _GNodo*));
    for (int j = 0; j < 37; j++) {
      HASH[i][j] = NULL;
    }
  }
  return HASH;
}

int codigo_ascii(char a) {
  switch(a) {
      return a - '0';
  }
}

int hasheo_uno(char* palabra) {
  int largo = strlen(palabra);
  int suma = 0;
  for (int i = 0; i < largo; i++) {
    suma += codigo_ascii(palabra[i]) * pow(2, i);
  }
  return (suma % 37);
}

int hasheo_dos(char* palabra) {
  int largo = strlen(palabra);
  int k = 0, suma = 0;
  for (int i = 0; i < largo; i++) {
    if (i != 0) {
      suma += codigo_ascii(palabra[i]) * pow(2, k++);
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
void hash_inserto(struct _GNodo*** hash, char* alias, GList lista, GList intervaloLista) {
  Conjunto conju = crear_conjunto(alias, lista, intervaloLista);

  int keyUno = hasheo_uno(alias);
  int keyDos = hasheo_dos(alias);

  printf("KEYUNO: %i\nKEYDOS: %i\n",keyUno,keyDos);

  if (hash_busco(hash , alias) == NULL) {
    mostrar_conjunto(conju);
    hash[keyUno][keyDos] = prepend_glist(hash[keyUno][keyDos], conju);

  } else {
    hash[keyUno][keyDos] = pisa_data_glist_nopos(hash[keyUno][keyDos], conju);
  }
  return;
}



void hash_elimino(struct _GNodo*** hash, char* alias) {
  int keyUno = hasheo_uno(alias);
  int keyDos = hasheo_dos(alias);
  if (hash[keyUno][keyDos] == NULL) {
    return;
  }
  hash[keyUno][keyDos] = eliminar_glist_char(hash[keyUno][keyDos], alias);
}

struct _GNodo*** ingresar_conjunto(struct _GNodo*** hasheo, Conjunto pal) {
  int keyUno = hasheo_uno(pal->alias);
  int keyDos = hasheo_dos(pal->alias);
  hasheo[keyUno][keyDos] = prepend_glist(hasheo[keyUno][keyDos], pal);
  return hasheo;
}

struct _GNodo*** eliminar_conjunto(struct _GNodo*** hasheo, Conjunto pal) {
  int keyUno = hasheo_uno(pal->alias);
  int keyDos = hasheo_dos(pal->alias);
  hasheo[keyUno][keyDos] = eliminar_glist (hasheo[keyUno][keyDos], pal);
  return hasheo;
}

void free_table(struct _GNodo*** table) {
  for (int i = 0; i < 37; i++){
    for (int j = 0; j < 37; j++){
      dlist_destruir(table[i][j],(Visitante) destruir_conjunto);
     // free(table[i][j]);
    }
  free(table[i]);
  }
  free(table);
}
