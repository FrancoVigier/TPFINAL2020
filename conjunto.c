#include <stdio.h>
#include <string.h>

#include "conjunto.h"
#include "intervalo.h"
#include "parser.h"

#define INT_SUPLIM 32767
#define INT_INFLIM -32767

Conjunto inicializar_conjunto(Conjunto conjunto, char* alias, char* operacion) {
  char vacio[] = " {}";
  //conjunto->alias = malloc(20 * sizeof(char));
  conjunto->alias = alias;
  conjunto->comprenExtens = 0;
  conjunto->lista=initialization_glist();
  conjunto->abiertoCerrado = 0;
  conjunto->intervaloLista = initialization_glist();
  conjunto->extInferior = INT_INFLIM;
  conjunto->extSuperior = INT_SUPLIM;
  if (strcmp(operacion, vacio))
    conjunto->vacio = 0;// "no vacio" solamente por la notacion {}
  else
    conjunto->vacio = 1;// " vacio" solamente por la notacion {}
  return conjunto;
}

Conjunto crear_conjunto(char* alias, GList lista, GList intervaloLista) {
  Conjunto conju = malloc(sizeof(struct _Conjunto));
//  conju->alias = malloc(sizeof(char*) * 40);
//  strcpy(conju->alias, alias);
  conju->alias = alias;
  conju->lista = initialization_glist();
  conju->intervaloLista = initialization_glist();
  conju->lista = glist_copiar_lista(lista);
  conju->intervaloLista = glist_copiar_lista(intervaloLista);
  return conju;
}

Conjunto extraer_com_conjunto(char* operacion, Conjunto conjunto) {
  Intervalo* intervalo = extraer_ini_y_fin(operacion);
  conjunto->vacio = intervalo->esVacio;
  printf("\nINICIO -%i-\nFINAL -%i-\n", intervalo->inicio, intervalo->ultimo);
  if (conjunto->vacio == 0) {
    conjunto->intervaloLista = prepend_glist(conjunto->intervaloLista, intervalo);
  }
  return conjunto;
}

Conjunto definir_conj_com(char* operacion, char* alias) {
  Conjunto nuevoConjunto = malloc(sizeof (struct _Conjunto));
  nuevoConjunto = inicializar_conjunto(nuevoConjunto, alias, operacion);
  nuevoConjunto = extraer_com_conjunto(operacion, nuevoConjunto);
  Intervalo* inter = nuevoConjunto->intervaloLista->data; //GUARDA BIEN
  if (nuevoConjunto->vacio == 1)
    printf("\nVACIO POR COMPRENSION\n");
  else
    printf("\n[%i:%i], CARDINAL: %i\n", inter->inicio, inter->ultimo, inter->cardinalidad);
  return nuevoConjunto;
}

Conjunto definir_conj_ext(char* operacion, char* alias) {
  Conjunto nuevoConjunto = malloc(sizeof(struct _Conjunto));
  nuevoConjunto = inicializar_conjunto(nuevoConjunto, alias, operacion);
  if (nuevoConjunto->vacio == 0)
    nuevoConjunto->lista = extraer_ext_conjunto(operacion, nuevoConjunto);
  else
    printf("Es vacio");
  return nuevoConjunto;
}

void mostrar_conjunto(Conjunto muestro) {
  GList bufferLista = muestro->lista;
  GList bufferIntervaloLista = muestro->intervaloLista;
  printf("\nAlias : -%s-\n", muestro->alias);
  printf("Lista solitarios :\n");
  for (; muestro->lista != NULL; muestro->lista = muestro->lista->next) {
    printf("- %i -", muestro->lista->data);
  }
  printf("\nLista intervalos :\n");
  for (; muestro->intervaloLista != NULL; muestro->intervaloLista = muestro->intervaloLista->next) {
    Intervalo* ver = muestro->intervaloLista->data;
    printf("- [%i,%i] -", ver->inicio, ver->ultimo);
  }
  printf("\n");
  muestro->lista = bufferLista;
  muestro->intervaloLista = bufferIntervaloLista;
}

void mostrar_conjunto_imprimir(Conjunto muestro) {
  if ( muestro->lista == NULL && muestro->intervaloLista == NULL){
    printf("{}\n");
  } else {
  GList bufferLista = muestro->lista;
  GList bufferIntervaloLista = muestro->intervaloLista;
  printf("\n");
  for (; muestro->lista != NULL;muestro->lista = muestro->lista->next) {
    printf("%i", muestro->lista->data);
    if (muestro->lista->next != NULL) {
      printf(",");
    }
  }
  for (; muestro->intervaloLista != NULL; muestro->intervaloLista = muestro->intervaloLista->next) {
    Intervalo * ver = muestro->intervaloLista->data;
    if (ver->inicio == ver->ultimo) {
      printf("%i", ver->inicio);
    } else {
      printf("%i:%i", ver->inicio, ver->ultimo);
    }
    if (muestro->intervaloLista->next != NULL) {
      printf(",");
    }
  }
  printf("\n");
  muestro->lista = bufferLista;
  muestro->intervaloLista = bufferIntervaloLista;
  }
}

void destruir_conjunto(Conjunto conjunto, void* aux){

  //char* alias = conjunto->alias;
  //free(alias);

  GList proximo = conjunto->lista;
  GList actual;
  for (; proximo != NULL ; ) {
    // Guardo un puntero al nodo actual, me muevo al siguiente y libero.
    actual = proximo;
    proximo = proximo->next;
    //int* data = (int*)actual->data;
    //free(data);
    free(actual);
  }
  conjunto->lista = NULL;

  GList proximoDos = conjunto->intervaloLista;
  GList actualDos;
  for (; proximoDos != NULL ; ) {
    // Guardo un puntero al nodo actual, me muevo al siguiente y libero.
    actualDos = proximoDos;
    proximoDos = proximoDos->next;
    Intervalo* data = (Intervalo*)actualDos->data;
    free(data);
    free(actualDos);
  }
  //free(conjunto->intervaloLista);
  conjunto->intervaloLista = NULL;
  //dlist_destruir(conjunto->lista,(Visitante)free_int_punt);
  //dlist_destruir(conjunto->intervaloLista,(Visitante)free_intervalo);
  free(conjunto);
}

