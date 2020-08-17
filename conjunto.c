#include <stdio.h>
#include <string.h>

#include "conjunto.h"
//20 limite de alias
Conjunto inicializar_conjunto(char* alias, char* operacion) {
  Conjunto conjunto = malloc(sizeof (struct _Conjunto));
  char vacio[] = " {}";
  conjunto->alias = malloc(20 * sizeof(char));
  strcpy(conjunto->alias, alias);
  conjunto->lista = initialization_glist();
  conjunto->intervaloLista = initialization_glist();
  if (strcmp(operacion, vacio))
    conjunto->vacio = 0;// "no vacio" solamente por la notacion {}
  else
    conjunto->vacio = 1;// " vacio" solamente por la notacion {}
  return conjunto;
}

Conjunto crear_conjunto(char* alias, GList lista, GList intervaloLista) {
  Conjunto conju = malloc(sizeof(struct _Conjunto));
  conju->alias = malloc(sizeof(char) * 20);
  strcpy(conju->alias, alias);
  conju->lista = initialization_glist();
  conju->intervaloLista = initialization_glist();
  conju->lista = glist_copiar_lista(lista);
  conju->intervaloLista = glist_copiar_lista(intervaloLista);
  return conju;
}

void extraer_com_conjunto(char* operacion, Conjunto conj) {
  Intervalo* intervalo = extraer_ini_y_fin(operacion);
  if (intervalo == NULL) {
    conj->vacio = 1;
    return;
  }
  conj->vacio = intervalo->esVacio;
  if (conj->vacio == 0) {
    conj->intervaloLista = prepend_glist(conj->intervaloLista, intervalo);
  }
  return;
}

Conjunto definir_conj_com(char* operacion, char* alias) {
  Conjunto nuevoConjunto = inicializar_conjunto(alias, operacion);
  extraer_com_conjunto(operacion, nuevoConjunto);
  if (nuevoConjunto->vacio == 1){
    printf("El conjunto definido por comprension es vacio\n");
  }
  return nuevoConjunto;
}

Conjunto definir_conj_ext(char* operacion, char* alias) {
  Conjunto nuevoConjunto = inicializar_conjunto(alias, operacion);
  if (nuevoConjunto->vacio == 0)
    nuevoConjunto->lista = extraer_ext_conjunto(operacion, nuevoConjunto);
  else
    printf("El conjunto definido es vacio...\n");
  return nuevoConjunto;
}

void mostrar_conjunto(Conjunto muestro) {
  GList bufferLista = muestro->lista;
  GList bufferIntervaloLista = muestro->intervaloLista;
  printf("\nAlias : -%s-\n", muestro->alias);
  printf("Lista solitarios :\n");
  for (; muestro->lista != NULL; muestro->lista = muestro->lista->next) {
    printf("- %lld -",(long long) muestro->lista->data);
  }
  printf("\nLista intervalos :\n");
  for (; muestro->intervaloLista != NULL;) {
    Intervalo* ver = muestro->intervaloLista->data;
    printf("- [%lld,%lld] -", ver->inicio, ver->ultimo);
    muestro->intervaloLista = muestro->intervaloLista->next;
  }
  printf("\n");
  muestro->lista = bufferLista;
  muestro->intervaloLista = bufferIntervaloLista;
}

void mostrar_conjunto_imprimir(Conjunto muestro) {
  if (muestro->lista == NULL && muestro->intervaloLista == NULL) {
    printf("{}\n");
  } else {
      GList bufferListaConj = aplanar_lista(muestro);

      GList bufferLista = glist_selection_sort(bufferListaConj);

      for (; bufferLista != NULL;) {
        Intervalo * ver = bufferLista->data;
        if (ver->inicio == ver->ultimo) {
          printf("%lld", ver->inicio);
        } else {
            printf("%lld:%lld", ver->inicio, ver->ultimo);
          }
        if (bufferLista->next != NULL) {
          printf(",");
        }
        bufferLista = bufferLista->next;
      }
      printf("\n");
      glist_destruir_int(bufferListaConj);
    }
}

void mostrar_intervalos(GList intervall) {
  GList intervalll = intervall;
  for (; intervalll != NULL;) {
    Intervalo* mostrar = intervalll->data;
    printf("-[%lld,%lld]-\n", mostrar->inicio, mostrar->ultimo);
    intervalll = intervalll->next;
  }
}

void destruir_conjunto(Conjunto conjunto, void* aux){
  free (conjunto->alias);
  GList proximo = conjunto->lista;
  GList actual;
  for (; proximo != NULL;) {
    actual = proximo;
    proximo = proximo->next;
    free (actual);
  }
  conjunto->lista = NULL;
  GList proximoDos = conjunto->intervaloLista;
  GList actualDos;
  for (; proximoDos != NULL;) {
    actualDos = proximoDos;
    proximoDos = proximoDos->next;
    Intervalo* data = (Intervalo*)actualDos->data;
    free (data);
    free (actualDos);
  }
  conjunto->intervaloLista = NULL;
  free(conjunto);
}
