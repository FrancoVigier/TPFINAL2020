#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

#include "operaciones.h"

GList conjunto_union(GList intervalos) {
//Si la lista es vacia, la union es vacia
  if (intervalos == NULL) {
    return NULL;
  }
  intervalos = glist_selection_sort(intervalos);
  int largo = largo_glist(intervalos);

  Stack pila = stack_new();
  Intervalo* inicio = get_data_glist(intervalos, 0);
  for (int indiceI = 1; indiceI < largo; indiceI++) {
    Intervalo* posi = get_data_glist(intervalos, indiceI);
//Si son intervalos disjuntos, inicio es solucion
    if (inicio->ultimo + 1 < posi->inicio) {
      stack_push(pila, inicio);
      inicio = posi;
    }
//Si hay solapamiento actualizo inicio y sigo comparando
    if (inicio->ultimo  >= posi->inicio) {
      if (inicio->ultimo < posi->ultimo) {
        inicio->ultimo = posi->ultimo;
      }
      continue;
    }
//Solapamiento tipo [x,y] [y+1,z] porque es en Z enteros
    if (inicio->ultimo + 1 == posi->inicio) {
      inicio->ultimo = posi->ultimo;
      continue;
    }
  }
//El ultimo intervalo al comparar es parte de solucion
  stack_push(pila, inicio);
  GList listaUnion = initialization_glist();
//Vacio la stack con los intervalos solucion
  while (!stack_es_vacio(pila)) {
    Intervalo* intervaloUnion = stack_top(pila);
    Intervalo* poner = malloc(sizeof(struct _Intervalo));
    poner->cardinalidad = intervaloUnion->cardinalidad;
    poner->esVacio = intervaloUnion->esVacio;
    poner->ultimo = intervaloUnion->ultimo;
    poner->inicio = intervaloUnion->inicio;
    listaUnion = prepend_glist(listaUnion, poner);
    stack_pop(pila);
  }
  stack_destruir(pila);
  return listaUnion;
}

//Pasa los elementos en extension a intervalos [x,x]
GList aplanar_lista(Conjunto primero) {
  GList listaAplanada = initialization_glist();
  Conjunto recursaPrimero = primero;

  GList primeroBufferIntervalo = initialization_glist();
  GList primeroBufferLista = initialization_glist();

  primeroBufferIntervalo = recursaPrimero->intervaloLista;
  primeroBufferLista = recursaPrimero->lista;
//Recorro la lista que contiene intervalos y la copio
  for (; primeroBufferIntervalo != NULL;) {
    Intervalo* mostrar = primeroBufferIntervalo->data;
//Copias del intervalo
    Intervalo* cpy = malloc(sizeof(struct _Intervalo));
    cpy->cardinalidad = mostrar->cardinalidad;
    cpy->esVacio = mostrar->esVacio;
    cpy->inicio = mostrar->inicio;
    cpy->ultimo = mostrar->ultimo;
    listaAplanada = prepend_glist(listaAplanada, cpy);
    primeroBufferIntervalo = primeroBufferIntervalo->next;
  }
//Recorro la lista en extension
  for (; primeroBufferLista != NULL;) {
//Extraigo el numero
    long long extremos = (long long)primeroBufferLista->data;
//Creo un intervalo [x,x] con el anterior num
    Intervalo* numero_solo = malloc(sizeof(struct _Intervalo));
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
//Casos de concatenacion NULL-Lista
  if (listaA == NULL) {
    GList listaSave = glist_copiar_lista(listaB);
    return listaSave;
  }
  if (listaB == NULL) {
    GList listaSave = glist_copiar_lista(listaA);
    return listaSave;
  }
//Si las dos listas no son vacias
  GList listaSave = glist_copiar_lista(listaA);
  GList lista = listaSave;
//Recorro hasta el final la primera y le agrego la segunda(copia)
  for (; lista->next != NULL; lista = lista->next);
  lista->next = glist_copiar_lista(listaB);
  return listaSave;
}

GList definir_conj_union(Conjunto primero, Conjunto segundo) {
  GList listaAplanada = initialization_glist();
//Uno la lista de intervalos y la numeros solitarios de cada conj.
  GList intervaloOperandoAA = aplanar_lista(primero);
  GList intervaloOperandoBB = aplanar_lista(segundo);
//Las copio
  GList intervaloOperandoA = glist_copiar_lista(intervaloOperandoAA);
  GList intervaloOperandoB = glist_copiar_lista(intervaloOperandoBB);
//Las concateno
  GList unionCadenas = concatenar_glist(intervaloOperandoA, intervaloOperandoB);
//Si la union es nula, es el caso NULL union NULL
  if (unionCadenas == NULL) {
    return NULL;
  }
//Si no es nula la concatenacion, checkeo los solapamientos en ella
  listaAplanada = conjunto_union(unionCadenas);

  glist_destruir_intervalo(intervaloOperandoA);
  glist_destruir_intervalo(intervaloOperandoB);

  glist_destruir_int(intervaloOperandoAA);
  glist_destruir_int(intervaloOperandoBB);

  glist_destruir_int(unionCadenas);
  return listaAplanada;
}

GList conjunto_inters( Conjunto primero, Conjunto segundo) {
//Caso base NULL interseccion A
  if (primero->lista == NULL && primero->intervaloLista == NULL) {
    return NULL;
  }
//Caso base A interseccion NULL
  if (segundo->lista == NULL && segundo->intervaloLista == NULL) {
    return NULL;
  }
//Convierto la lista de enteros y la de intervalos en una en ambos conj.
  GList intervaloOperandoAA = aplanar_lista(primero);
  GList intervaloOperandoBB = aplanar_lista(segundo);
//Ordeno las anteriores listas
  GList intervaloOperandoAAA = glist_selection_sort(intervaloOperandoAA);
  GList intervaloOperandoBBB = glist_selection_sort(intervaloOperandoBB);
//Paso por copia las listas
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
//Creo una referencia por copia de cada nodo en los indices
    nodoAEnPosI->cardinalidad = nodoAEnPosII->cardinalidad;
    nodoAEnPosI->esVacio = nodoAEnPosII->esVacio;
    nodoAEnPosI->inicio = nodoAEnPosII->inicio;
    nodoAEnPosI->ultimo = nodoAEnPosII->ultimo;

    nodoBEnPosJ->cardinalidad = nodoBEnPosJJ->cardinalidad;
    nodoBEnPosJ->esVacio = nodoBEnPosJJ->esVacio;
    nodoBEnPosJ->inicio = nodoBEnPosJJ->inicio;
    nodoBEnPosJ->ultimo = nodoBEnPosJJ->ultimo;
//Parto de la premisa que existe la interseccion entre los nodos
    Intervalo* temporal = malloc (sizeof(struct _Intervalo));
    temporal->inicio = MAX (nodoAEnPosI->inicio, nodoBEnPosJ->inicio);
    temporal->ultimo = MIN (nodoAEnPosI->ultimo, nodoBEnPosJ->ultimo);
//Si esa hipotetica interseccion es "validable" entonces:
    if (temporal->inicio <= temporal->ultimo) {
        temporal->cardinalidad = (temporal->ultimo - temporal->inicio) + 1;
        temporal->esVacio = 0;
    }
//Si no lo es, es "vacia"
    if (temporal->inicio > temporal->ultimo) {
        temporal->cardinalidad = 0;
        temporal->esVacio = 1;
    }
    if (nodoAEnPosI->inicio > nodoBEnPosJ->inicio) {
//Solapamiento tipo C
        if (nodoAEnPosI->ultimo <= nodoBEnPosJ->ultimo) {
//Contencion de nodo A en nodo B busco el sigiente nodo en la lista A
            ++indiceI;
        }
        else{
//Solapamiento tipo B
//Nodo B no "cubre" a nodo A lo suficiente y hay un remanente
//Busco el siguiente nodo en la lista B
            ++indiceJ;
        }
//Si mi hipotetica interseccion es valida, es parte de resultado
        if (temporal->esVacio == 0) {
            listaInterseccion = prepend_glist(listaInterseccion, temporal);
        }
        if (temporal->esVacio == 1) {
            free (temporal);
        }
    }
    else if (nodoAEnPosI->inicio < nodoBEnPosJ->inicio) {
//Solapamiento tipo C
        if (nodoAEnPosI->ultimo >= nodoBEnPosJ->ultimo) {
//Contencion de nodo B en nodo A busco el sigiente nodo en la lista B
            ++indiceJ;
        }
        else {
//Solapamiento tipo B o A( pensando al reves los nodos)
//Nodo A no "cubre" a nodo B lo suficiente y hay un remanente
//Busco el siguiente nodo en la lista A
            ++indiceI;
        }
//Si mi hipotetica interseccion es valida, es parte de resultado
        if (temporal->esVacio == 0) {
            listaInterseccion = prepend_glist(listaInterseccion, temporal);
        }
        if (temporal->esVacio == 1) {
          free (temporal);
        }
    }
    else {
      if (nodoAEnPosI->ultimo < nodoBEnPosJ->ultimo) {
//Contencion de nodo A en nodo B busco el sigiente nodo en la lista A
        ++indiceI;
        }
      else if (nodoAEnPosI->ultimo > nodoBEnPosJ->ultimo) {
//Nodo B no "cubre" a nodo A lo suficiente y hay un remanente
//Busco el siguiente nodo en la lista B
        ++indiceJ;
      }
      else {
//Son totalmente IGUALES los nodos avanzo en ambas listas
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
  GList resta = initialization_glist();
//Recorro la lista
  for (int indice = 0; indice < len; indice++) {
//Extraigo la data de la lista en el indice
    Intervalo* data = get_data_glist(intervaloA,indice);
//Desgloso la data
    long long izq = data->inicio;
    long long der = data->ultimo;
//Si el intervaloB es igual a la data, no agrego nada al resultado
    if(der == intervaloB->ultimo && izq == intervaloB->inicio) {
      continue;
    }
//Si el intervaloB se intersecan del tipo [x,y] [y,z] o no
    if (der <= intervaloB->inicio) {
//Si son disjuntos, agrego mi data como un intervalo y parte de la resta
      if (der < intervaloB->inicio) {
        Intervalo* interval = malloc(sizeof(struct _Intervalo));
        interval->inicio = izq;
        interval->ultimo = der;
        interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
        interval->esVacio = 0;
        resta = prepend_glist(resta, interval);
      }
//Si colisiona mi data([x,y]) solamente en el ext.sup. Creo un int. [x,y-1]
      if (der == intervaloB->inicio) {
        Intervalo* interval = malloc(sizeof(struct _Intervalo));
        interval->inicio = izq;
        interval->ultimo = der - 1;
        interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
        interval->esVacio = 0;
        resta = prepend_glist(resta, interval);
      }
    }
//Solapamiento Tipo A, conformo un intervalo con los inicios
    else if (izq < intervaloB->inicio && der <= intervaloB->ultimo) {
      Intervalo* interval = malloc(sizeof(struct _Intervalo));
      interval->inicio = izq;
      interval->ultimo = intervaloB->inicio - 1;
      interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
      interval->esVacio = 0;
      resta = prepend_glist(resta, interval);
    }
//Solapamiento Tipo C, se subdivide mi data en dos intervalos
    else if (izq < intervaloB->inicio && der > intervaloB->ultimo) {
      Intervalo* interval1 = malloc(sizeof(struct _Intervalo));
      interval1->inicio = izq;
      interval1->ultimo = intervaloB->inicio - 1;
      interval1->cardinalidad = (interval1->ultimo - interval1->inicio) + 1;
      interval1->esVacio = 0;
      resta = prepend_glist(resta, interval1);
      Intervalo* interval2 =  malloc(sizeof(struct _Intervalo));
      interval2->inicio = intervaloB->ultimo + 1;
      interval2->ultimo = der;
      interval2->cardinalidad = (interval2->ultimo - interval2->inicio) + 1;
      interval2->esVacio = 0;
      resta = prepend_glist(resta, interval2);
    }
//Solapamiento Tipo A se desprecia el segmento de data contenido en intervaloB
    else if (izq >= intervaloB->inicio && izq <= intervaloB->ultimo &&
             der > intervaloB->ultimo) {
      Intervalo* interval = malloc(sizeof(struct _Intervalo));
      interval->inicio = intervaloB->ultimo + 1;
      interval->ultimo = der;
      interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
      interval->esVacio = 0;
      resta = prepend_glist(resta, interval);
    }
//Intervalos disjuntos o coincidentes en un solo punto
    else if (izq >= intervaloB->ultimo) {
//Intervalos disjuntos mi data es parte del resultado ya que exede a intervaloB
      if (izq > intervaloB->ultimo) {
        Intervalo* interval = malloc(sizeof(struct _Intervalo));
        interval->inicio = izq;
        interval->ultimo = der;
        interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
        interval->esVacio = 0;
        resta = prepend_glist(resta, interval);
      }
//Si colisiona mi data([x,y]) solamente en el ext.inf. Creo un int. [x+1,y]
      if (izq == intervaloB->ultimo) {
        Intervalo* interval = malloc(sizeof(struct _Intervalo));
        interval->inicio = izq + 1;
        interval->ultimo = der;
        interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
        interval->esVacio = 0;
        resta = prepend_glist(resta, interval);
      }
    }
  }
  return resta;
}

GList definir_conj_dif_dos(Conjunto primero, Conjunto segundo) {
//Caso base R - R = NULL
  if (strcmp(primero->alias, segundo->alias) == 0) {
    return NULL;
  }
//Caso base NULL - R = NULL
  if (primero->lista == NULL && primero->intervaloLista == NULL) {
    return NULL;
  }
//Caso base R - NULL = R
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
//Por cada elemento en mi segunda lista obtengo una cantidad igual
//de pseudorestas Tipo C y las almaceno en una pila
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
//Si la pila es vacia, la resta lo es tambien
  if (stack_es_vacio(pila)) {
    resultado = NULL;
  }
  else {
//Si no es vacia interseco su contenido
    while (!stack_es_vacio(pila)) {
//Saco el primer elemento
      GList opA = stack_top(pila);
      stack_pop(pila);
//Si despues de sacarlo la pila es vacia, ese es el resultado
      if (stack_es_vacio(pila)) {
        resultado = opA;
      }
      else {
//Si no, saco un segundo elemento
        GList opB = stack_top(pila);
        stack_pop(pila);
        Conjunto A = crear_conjunto("", NULL, opA);
        Conjunto B = crear_conjunto("", NULL, opB);
//Los interseco
        GList intermedio = conjunto_inters(A, B);
//Ingreso el resultado de la interseccion
        stack_push(pila, intermedio);

        glist_destruir_intervalo(opA);
        glist_destruir_intervalo(opB);
        glist_destruir_int(A->lista);
        glist_destruir_int(A->intervaloLista);
        free (A->alias);
        free (A);
        glist_destruir_int(B->lista);
        glist_destruir_int(B->intervaloLista);
        free (B->alias);
        free (B);
      }
    }
  }
  glist_destruir_intervalo(bufferlistauno);
  glist_destruir_intervalo(bufferlistados);
  free (pila);
  return resultado;
}
