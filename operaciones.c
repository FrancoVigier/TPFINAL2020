#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

#include "operaciones.h"

GList conjunto_union(GList intervalos) {
  if (intervalos == NULL) {
    return NULL;
  }
  intervalos = glist_selection_sort(intervalos);
  int largo = largo_glist(intervalos);

  Stack pila = stack_new();
  Intervalo* inicio = get_data_glist(intervalos, 0);
  for (int i = 1; i < largo; i++) {
    Intervalo* posi = get_data_glist(intervalos, i);
    if (inicio->ultimo + 1 < posi->inicio) {
      stack_push(pila, inicio);
      inicio = posi;
    }
    if (inicio->ultimo  >= posi->inicio) {
      if (inicio->ultimo < posi->ultimo) {
        inicio->ultimo = posi->ultimo;
      }
      continue;
    }
    if (inicio->ultimo + 1 == posi->inicio) {
      inicio->ultimo = posi->ultimo;
      continue;
    }
  }
  stack_push(pila,inicio);
  GList listaUnion = initialization_glist();
  while (!stack_es_vacio(pila)) {
    Intervalo* intervaloUnion = stack_top(pila);
    Intervalo* poner = malloc(sizeof(struct _Intervalo));
    poner->cardinalidad = intervaloUnion->cardinalidad;
    poner->esVacio = intervaloUnion->esVacio;
    poner->ultimo = intervaloUnion->ultimo;
    poner->inicio = intervaloUnion->inicio;
    listaUnion =  prepend_glist(listaUnion, poner);
    stack_pop(pila);
  }
  stack_destruir(pila);
  return listaUnion;
}

GList aplanar_lista(Conjunto primero) {
  GList listaAplanada = initialization_glist();
  Conjunto recursaPrimero = primero;

  GList primeroBufferIntervalo = initialization_glist();
  GList primeroBufferLista = initialization_glist();

  primeroBufferIntervalo = recursaPrimero->intervaloLista;
  primeroBufferLista = recursaPrimero->lista;

  for (; primeroBufferIntervalo != NULL;) {
    Intervalo* mostrar = primeroBufferIntervalo->data;
    Intervalo* cpy = malloc(sizeof(struct _Intervalo));
    cpy->cardinalidad = mostrar->cardinalidad;
    cpy->esVacio = mostrar->esVacio;
    cpy->inicio = mostrar->inicio;
    cpy->ultimo = mostrar->ultimo;
    listaAplanada = prepend_glist(listaAplanada, cpy);
    primeroBufferIntervalo = primeroBufferIntervalo->next;
  }
  for (; primeroBufferLista != NULL;) {
    Intervalo* numero_solo = malloc(sizeof(struct _Intervalo));
    long long extremos = (long long)primeroBufferLista->data;
    numero_solo->inicio = extremos;
    numero_solo->ultimo = extremos;
    numero_solo->cardinalidad = 1;
    numero_solo->esVacio = 0;
    listaAplanada = prepend_glist(listaAplanada, numero_solo);
    primeroBufferLista = primeroBufferLista->next;
  }
  return listaAplanada;
}

GList concatenar_glist (GList listaA, GList listaB) {
  if (listaA == NULL) {
    GList listaSave = glist_copiar_lista(listaB);
    return listaSave;
  }
  if (listaB == NULL) {
    GList listaSave = glist_copiar_lista(listaA);
    return listaSave;
  }
  GList listaSave = glist_copiar_lista(listaA);
  GList lista = listaSave;
  for (; lista->next != NULL; lista = lista->next);
  lista->next = glist_copiar_lista(listaB);
  return listaSave;
}

void mostrar_intervalo(GList intervall) {
  GList intervalll = intervall;
  for (; intervalll != NULL;) {
    Intervalo* mostrar = intervalll->data;
    printf("-[%lld,%lld]-\n", mostrar->inicio, mostrar->ultimo);
    intervalll = intervalll->next;
  }
}

GList definir_conj_union(Conjunto primero, Conjunto segundo) {
  GList listaAplanada = initialization_glist();

  GList intervaloOperandoAA = aplanar_lista(primero);
  GList intervaloOperandoBB = aplanar_lista(segundo);

  GList intervaloOperandoA = glist_copiar_lista(intervaloOperandoAA);
  GList intervaloOperandoB = glist_copiar_lista(intervaloOperandoBB);

  GList unionCadenas = concatenar_glist(intervaloOperandoA,intervaloOperandoB);

  if (unionCadenas == NULL) {
    return NULL;
  }
  listaAplanada = conjunto_union(unionCadenas);

  glist_destruir_intervalo(intervaloOperandoA);
  glist_destruir_intervalo(intervaloOperandoB);

  glist_destruir_int(intervaloOperandoAA);
  glist_destruir_int(intervaloOperandoBB);

  glist_destruir_int(unionCadenas);
  return listaAplanada;
}

GList conjunto_inters( Conjunto primero, Conjunto segundo) {
  if (primero->lista == NULL && primero->intervaloLista == NULL) {
    return NULL;
  }
  if (segundo->lista == NULL && segundo->intervaloLista == NULL) {
    return NULL;
  }
  GList intervaloOperandoAA = aplanar_lista(primero);
  GList intervaloOperandoBB = aplanar_lista(segundo);

  GList intervaloOperandoAAA = glist_selection_sort(intervaloOperandoAA);
  GList intervaloOperandoBBB = glist_selection_sort(intervaloOperandoBB);

  GList intervaloOperandoA = glist_copiar_lista(intervaloOperandoAAA);
  GList intervaloOperandoB = glist_copiar_lista(intervaloOperandoBBB);

  GList listaInterseccion = initialization_glist();
  int indiceI = 0;
  int indiceJ = 0;
  int largoOpeA = largo_glist(intervaloOperandoA);
  int largoOpeB = largo_glist(intervaloOperandoB);
  for (;indiceI < largoOpeA && indiceJ < largoOpeB;) {
    Intervalo* nodoAEnPosI = malloc (sizeof(struct _Intervalo));
    Intervalo* nodoBEnPosJ = malloc (sizeof(struct _Intervalo));

    Intervalo* nodoAEnPosII = get_data_glist(intervaloOperandoA, indiceI);
    Intervalo* nodoBEnPosJJ = get_data_glist(intervaloOperandoB, indiceJ);

    nodoAEnPosI->cardinalidad = nodoAEnPosII->cardinalidad;
    nodoAEnPosI->esVacio = nodoAEnPosII->esVacio;
    nodoAEnPosI->inicio = nodoAEnPosII->inicio;
    nodoAEnPosI->ultimo = nodoAEnPosII->ultimo;

    nodoBEnPosJ->cardinalidad = nodoBEnPosJJ->cardinalidad;
    nodoBEnPosJ->esVacio = nodoBEnPosJJ->esVacio;
    nodoBEnPosJ->inicio = nodoBEnPosJJ->inicio;
    nodoBEnPosJ->ultimo = nodoBEnPosJJ->ultimo;

    Intervalo* temporal = malloc (sizeof(struct _Intervalo));
    temporal->inicio = MAX (nodoAEnPosI->inicio, nodoBEnPosJ->inicio);
    temporal->ultimo = MIN (nodoAEnPosI->ultimo, nodoBEnPosJ->ultimo);

    if(temporal->inicio <= temporal->ultimo){
        temporal->cardinalidad = (temporal->ultimo - temporal->inicio) + 1;
        temporal->esVacio = 0;
      }
    if(temporal->inicio > temporal->ultimo){
        temporal->cardinalidad = 0;
        temporal->esVacio = 1;
      }
    if(nodoAEnPosI->inicio > nodoBEnPosJ->inicio){
        if(nodoAEnPosI->ultimo <= nodoBEnPosJ->ultimo){
            ++indiceI;
        }
        else{
            ++indiceJ;
        }
        if(temporal->esVacio == 0){
            listaInterseccion = prepend_glist(listaInterseccion, temporal);
        }
        if(temporal->esVacio == 1){
            free (temporal);
        }
    }
    else if(nodoAEnPosI->inicio < nodoBEnPosJ->inicio){
        if(nodoAEnPosI->ultimo >= nodoBEnPosJ->ultimo){
            ++indiceJ;
        }
        else{
            ++indiceI;
        }
        if(temporal->esVacio == 0){
            listaInterseccion = prepend_glist(listaInterseccion, temporal);
        }
        if(temporal->esVacio == 1){
          free (temporal);
        }
    }
    else{
        if(nodoAEnPosI->ultimo < nodoBEnPosJ->ultimo){
            ++indiceI;
        }
        else if(nodoAEnPosI->ultimo > nodoBEnPosJ->ultimo){
            ++indiceJ;
        }
        else{
            ++indiceI;
            ++indiceJ;
        }
        listaInterseccion = prepend_glist(listaInterseccion, temporal);
    }
    free (nodoAEnPosI);
    free (nodoBEnPosJ);

  }
  glist_destruir_intervalo(intervaloOperandoA);
  glist_destruir_intervalo(intervaloOperandoB);
  glist_destruir_int(intervaloOperandoAA);
  glist_destruir_int(intervaloOperandoBB);

  return listaInterseccion;
}

GList conjunto_diferencia_dos(GList intervaloA, Intervalo* intervaloB) {
  intervaloA = glist_selection_sort(intervaloA);
  int len = largo_glist(intervaloA);
  GList res = initialization_glist();
  for (int indice = 0; indice < len; indice++) {
    Intervalo* data = get_data_glist(intervaloA,indice);
    long long izq = data->inicio;
    long long der = data->ultimo;
    if(der == intervaloB->ultimo && izq == intervaloB->inicio) {
      continue;
    }
    if (der <= intervaloB->inicio) {
      if (der < intervaloB->inicio) {
        Intervalo* interval = malloc(sizeof(struct _Intervalo));
        interval->inicio = izq;
        interval->ultimo = der;
        interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
        interval->esVacio = 0;
        res = prepend_glist(res, interval);
      }
      if (der == intervaloB->inicio) {
        Intervalo* interval = malloc(sizeof(struct _Intervalo));
        interval->inicio = izq;
        interval->ultimo = der-1;
        interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
        interval->esVacio = 0;
        res = prepend_glist(res, interval);
      }
    }
    else if (izq < intervaloB->inicio && der <= intervaloB->ultimo) {
      Intervalo* interval = malloc(sizeof(struct _Intervalo));
      interval->inicio = izq;
      interval->ultimo = intervaloB->inicio-1;
      interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
      interval->esVacio = 0;
      res = prepend_glist(res, interval);
    }
    else if (izq < intervaloB->inicio && der > intervaloB->ultimo) {
      Intervalo* interval1 = malloc(sizeof(struct _Intervalo));
      interval1->inicio = izq;
      interval1->ultimo = intervaloB->inicio-1;
      interval1->cardinalidad = (interval1->ultimo - interval1->inicio) + 1;
      interval1->esVacio = 0;
      res = prepend_glist(res, interval1);
      Intervalo* interval2 =  malloc(sizeof(struct _Intervalo));
      interval2->inicio = intervaloB->ultimo+1;
      interval2->ultimo = der;
      interval2->cardinalidad = (interval2->ultimo - interval2->inicio) + 1;
      interval2->esVacio = 0;
      res = prepend_glist(res, interval2);
    }
    else if (izq >= intervaloB->inicio && izq <= intervaloB->ultimo &&
             der > intervaloB->ultimo) {
      Intervalo* interval = malloc(sizeof(struct _Intervalo));
      interval->inicio = intervaloB->ultimo+1;//
      interval->ultimo = der;
      interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
      interval->esVacio = 0;
      res = prepend_glist(res, interval);
    }
    else if (izq >= intervaloB->ultimo) {
      if (izq > intervaloB->ultimo) {
        Intervalo* interval = malloc(sizeof(struct _Intervalo));
        interval->inicio = izq;
        interval->ultimo = der;
        interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
        interval->esVacio = 0;
        res = prepend_glist(res, interval);
      }
      if (izq == intervaloB->ultimo) {
        Intervalo* interval = malloc(sizeof(struct _Intervalo));
        interval->inicio = izq+1;
        interval->ultimo = der;
        interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
        interval->esVacio = 0;
        res = prepend_glist(res, interval);
      }
    }
  }
  return res;
}

GList definir_conj_dif_dos(Conjunto primero, Conjunto segundo) {
  if (strcmp(primero->alias, segundo->alias) == 0) {// R - R = NULL
    return NULL;
  }

  if (primero->lista == NULL && primero->intervaloLista == NULL) {
    return NULL;
  }

  if (segundo->lista == NULL && segundo->intervaloLista == NULL) {
    GList base = aplanar_lista(primero);
    return base;
  }

  GList bufferlistauno = aplanar_lista(primero);
  GList bufferlistados = aplanar_lista(segundo);

  GList listauno = bufferlistauno;
  GList listados = bufferlistados;

  if (listauno == NULL) {// NULL - R = NULL
    return NULL;
  }

  Stack pila = stack_new();

  for (; listados != NULL; listados = listados->next) {
    Intervalo* datazo = (Intervalo*)listados->data;
    Intervalo* dato = malloc(sizeof(struct _Intervalo));
    dato->inicio = datazo->inicio;
    dato->ultimo = datazo->ultimo;
    dato->cardinalidad = datazo->cardinalidad;
    dato->esVacio = datazo->esVacio;
    GList lista = conjunto_diferencia_dos(listauno, dato);
    stack_push(pila,lista);
    free (dato);
  }
  GList resultado = initialization_glist();
  if (stack_es_vacio(pila)) {
    resultado = NULL;
  }
  else {
    while (!stack_es_vacio(pila)) {
      GList opA = stack_top(pila);
      stack_pop(pila);
      if (stack_es_vacio(pila)) {
        resultado = opA;
      }
      else {
        GList opB = stack_top(pila);
        stack_pop(pila);
        Conjunto A = crear_conjunto("", NULL, opA);
        Conjunto B = crear_conjunto("", NULL, opB);

        GList intermedio = conjunto_inters(A, B);
        stack_push(pila, intermedio);

        glist_destruir_intervalo(opA);
        glist_destruir_intervalo(opB);

        glist_destruir_int(A->lista);
        glist_destruir_int(A->intervaloLista);
        free (A->alias);
        free (A);
        glist_destruir_int(B->lista);
        glist_destruir_int(B->intervaloLista);
        free(B->alias);
        free(B);
      }
    }
  }

  glist_destruir_intervalo(bufferlistauno);
  glist_destruir_intervalo(bufferlistados);
  free (pila);
  return resultado;
}

void mostrar(GList lista) {
  for (; lista != NULL; lista = lista->next) {
    long long num = (long long)lista->data;
    printf("- %lld -\n", num);
  }
}

void mostrar_glist(GList lista) {
  Conjunto var;
  for (; lista != NULL; lista = lista->next) {
    var = lista->data;
    mostrar(var->lista);
  }
}


void mostrar_glist_intervalos(GList lista) {
  GList buff = lista->next;
  Conjunto var;
  mostrar(buff);
  for (; lista != NULL; lista = lista->next) {
    var = lista->data;
    mostrar_intervalo(var->intervaloLista);
  }
}
