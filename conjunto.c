#include <stdio.h>
#include <string.h>
#include "operaciones.h"
#include "conjunto.h"

//Inicializamos un conjunto
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

//Creamos un conjunto por listas por copia
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

//Dada una definicion por comprension creo un intervalo
//y lo cargo a un Conjunto parametro
void extraer_com_conjunto(char* operacion, Conjunto conj) {
//Extraigo limites de la definicion
  Intervalo* intervalo = extraer_ini_y_fin(operacion);
//Verifico si es valido el intervalo
  if (intervalo == NULL) {
    conj->vacio = 1;
    return;
  }
  conj->vacio = intervalo->esVacio;
//Si es valido lo cargo al conjunto parametro
  if (conj->vacio == 0) {
    conj->intervaloLista = prepend_glist(conj->intervaloLista, intervalo);
  }
  return;
}

//Defino un conjunto por comprension
Conjunto definir_conj_com(char* operacion, char* alias) {
  Conjunto nuevoConjunto = inicializar_conjunto(alias, operacion);
//Extraigo el intervalo presente en la declaracion
  extraer_com_conjunto(operacion, nuevoConjunto);
  if (nuevoConjunto->vacio == 1) {
    printf("El conjunto definido por comprension es vacio\n");
  }
  return nuevoConjunto;
}

//Definimos un conjunto por extension
Conjunto definir_conj_ext(char* operacion, char* alias) {
  Conjunto nuevoConjunto = inicializar_conjunto(alias, operacion);
//Si el conjunto no es vacio en la declaracion por extension
//es decir '{}' extraigo su contenido
  if (nuevoConjunto->vacio == 0)
    nuevoConjunto->lista = extraer_ext_conjunto(operacion, nuevoConjunto);
  else
    printf("El conjunto definido es vacio...\n");
  return nuevoConjunto;
}

//Imprimimos un conjunto
void mostrar_conjunto_imprimir(Conjunto muestro) {
//Si el conjunto es nulo, imprimimos "{}"
  if (muestro->lista == NULL && muestro->intervaloLista == NULL) {
    printf("{}\n");
  } else {
//Si no lo es aplano su contenido, es decir paso
//todo a intervalo
      GList bufferListaConj = aplanar_lista(muestro);
      GList bufferLista = glist_selection_sort(bufferListaConj);
      for (; bufferLista != NULL;) {
        Intervalo * ver = bufferLista->data;
//Si son intervalos [x,x] expreso como x
        if (ver->inicio == ver->ultimo) {
          printf("%lld", ver->inicio);
        }
//Si no expreso como [x,y]
        else {
          printf("%lld:%lld", ver->inicio, ver->ultimo);
        }
        if (bufferLista->next != NULL) {
          printf(",");
        }
        bufferLista = bufferLista->next;
      }
      printf("\n");
      glist_destruir_intervalo(bufferListaConj);
    }
}

//Liberamos la memoria de un Conjunto
void destruir_conjunto(Conjunto conjunto) {
//Libero el alias
  free (conjunto->alias);
  GList proximo = conjunto->lista;
  GList actual;
//Libero la lista de elementos tipo x
  for (; proximo != NULL;) {
    actual = proximo;
    proximo = proximo->next;
    free (actual);
  }
  conjunto->lista = NULL;
  GList proximoDos = conjunto->intervaloLista;
  GList actualDos;
//Libero la lista de elementos tipo [x,y]
  for (; proximoDos != NULL;) {
    actualDos = proximoDos;
    proximoDos = proximoDos->next;
    Intervalo* data = (Intervalo*)actualDos->data;
    free (data);
    free (actualDos);
  }
  conjunto->intervaloLista = NULL;
//Libero el conjunto
  free (conjunto);
}
