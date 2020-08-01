#include <stdio.h>
#include <string.h>
#include <math.h>
#include "LSE.h"
#include "conjunto.h"

struct _GNodo *** inicializar_HASH() {
  struct _GNodo*** HASH;
  HASH = (struct _GNodo ***)malloc(41*sizeof(struct _GNodo**));
  for (int i = 0; i < 41; i++) {
    HASH[i] = (struct _GNodo**)malloc(41*sizeof(struct _GNodo*));
    for (int j = 0; j < 41; j++) {
      HASH[i][j] = NULL;
    }
  }
  return HASH;
}

int codigo_ascii(char a) {
  switch(a) {
    case 'ñ':
      return 26;
    case ' ':
      return 27;
    case '-':
      return 28;
    case '´':
      return 29;
    case '?':
      return 30;
    case 'ü':
      return 31;
    case 'è':
      return 32;
    case 'î':
      return 33;
    case 'á':
      return 34;
    case 'é':
      return 35;
    case 'í':
      return 36;
    case 'ó':
      return 37;
    case 'ú':
      return 38;
    default:
      return a - 'a';
  }
}

int hasheo_uno(char* palabra) {
  int largo = strlen(palabra);
  int suma = 0;
  for (int i = 0; i < largo; i++) {
    suma += codigo_ascii(palabra[i]) * pow(2, i);
  }
  return (suma % 41);
}

int hasheo_dos(char* palabra) {
  int largo = strlen(palabra);
  int k = 0, suma = 0;
  for (int i = 0; i < largo; i++) {
    if (i != 0) {
      suma += codigo_ascii(palabra[i]) * pow(2, k++);
    }
  }
  return suma % 41;
}

void hash_inserto(struct _GNodo*** hash, char* alias, GList lista, GList intervaloLista) {
  Conjunto conju = crear_conjunto(alias, lista, intervaloLista);
  int keyUno = hasheo_uno(alias);
  int keyDos = hasheo_dos(alias);
  struct _GNodo* aux = glist_copiar_lista(hash[keyUno][keyDos]);
  if (esta_data_glist(aux , conju) == 0) {
    hash[keyUno][keyDos] = prepend_glist(hash[keyUno][keyDos], conju);
  } else {
    hash[keyUno][keyDos] = pisa_data_glist_nopos(hash[keyUno][keyDos], conju);
  }
  return;
}

Conjunto hash_busco(struct _GNodo*** hash, char* alias) {
  int keyUno = hasheo_uno(alias);
  int keyDos = hasheo_dos(alias);
  struct _GNodo* aux = glist_copiar_lista(hash[keyUno][keyDos]);
  
  GList buffer = aux;
  
  for (; aux != NULL; aux = aux->next) {
    Conjunto ver = aux->data;
    if (strcmp(ver->alias, alias) == 0) {
      
      aux = buffer;
      dlist_destruir(aux,(Visitante)destruir_conjunto);
      
      return ver;
    }
  }
  
  aux = buffer;
  dlist_destruir(aux,(Visitante)destruir_conjunto);
  
  return NULL;
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
  for (int i = 0; i < 41; i++){
    for (int j = 0; j < 41; j++){
      dlist_destruir(table[i][j],(Visitante) destruir_conjunto);
    }
  free(table[i]);
  }
  free(table);
}

