#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "pila.h"
#include "conjunto.h"
#include "LSE.h"
#include "intervalo.h"
#include "parser.h"
#include "hash.h"

#define LIMITE 300
#define INT_SUPLIM 32767
#define INT_INFLIM -32767
#define LIST_LIM 10
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

///////////////////////
GList conjunto_union(GList intervalos) { /// [...],[...] UNION
  intervalos = dlist_selectionSort(intervalos);
  printf("HOLAAAAa");
  int largo = largo_glist(intervalos);
  if (largo <= 0) {
    return NULL;
  }
  Stack pila = stack_new();
  stack_push(pila, get_data_glist(intervalos, 0));
  for (int i = 1; i < largo; i++) {
    Intervalo* top = stack_top(pila);
    Intervalo* posi = get_data_glist(intervalos, i);
    if (top->ultimo < posi->inicio)
      stack_push(pila, posi);
    else if (top->ultimo < posi->ultimo) {
      top->ultimo =  posi->ultimo;
      stack_pop(pila);
      stack_push(pila, top);
    }
  }
  GList listaUnion = initialization_glist();
  while (!stack_es_vacio(pila)) {
    Intervalo* intervaloUnion = stack_top(pila);
    listaUnion =  prepend_glist(listaUnion, intervaloUnion);
    printf("[%i,%i]-", intervaloUnion->inicio, intervaloUnion->ultimo);
    stack_pop(pila);
  }
  return listaUnion;
}

GList aplanar_solos_e_intervalos(Conjunto primero, Conjunto segundo) { //1->union 2->interseccion
  GList listaAplanada = initialization_glist();
  Conjunto recursaPrimero = primero;
  Conjunto recursaSegundo = segundo;
  GList primeroBufferIntervalo = initialization_glist();
  GList primeroBufferLista = initialization_glist();
  GList segundoBufferIntervalo = initialization_glist();
  GList segundoBufferLista = initialization_glist();
  primeroBufferIntervalo = glist_copiar_lista(recursaPrimero->intervaloLista);
  primeroBufferLista = glist_copiar_lista(recursaPrimero->lista);
  segundoBufferIntervalo = glist_copiar_lista(recursaSegundo->intervaloLista);
  segundoBufferLista = glist_copiar_lista(recursaSegundo->lista);
  for (; primeroBufferIntervalo != NULL;) {
    Intervalo* mostrar = primeroBufferIntervalo->data;
    printf("APLANAR[%i,%i]-", mostrar->inicio,mostrar->ultimo);
    listaAplanada = prepend_glist(listaAplanada, primeroBufferIntervalo->data);
    primeroBufferIntervalo = primeroBufferIntervalo->next;
  }
  for (; primeroBufferLista != NULL;) {
    Intervalo* numero_solo = malloc(sizeof(struct _Intervalo));
    int extremos = (int)primeroBufferLista->data;
    printf("numero libre -%i-\n", extremos);
    numero_solo->inicio = extremos;
    numero_solo->ultimo = extremos;
    numero_solo->cardinalidad = 1;
    numero_solo->esVacio = 0;
    printf("APLANAR1[%i,%i]-", numero_solo->inicio, numero_solo->ultimo);
    listaAplanada = prepend_glist(listaAplanada, numero_solo);
    primeroBufferLista = primeroBufferLista->next;
  }
  for (; segundoBufferLista != NULL;) {
    Intervalo* numero_solo = malloc(sizeof(struct _Intervalo));
    int extremos = (int)segundoBufferLista->data;
    numero_solo->inicio = extremos;
    numero_solo->ultimo = extremos;
    numero_solo->cardinalidad = 1;
    numero_solo->esVacio = 0;
    printf("APLANAR2[%i,%i]-", numero_solo->inicio, numero_solo->ultimo);
    listaAplanada = prepend_glist(listaAplanada, numero_solo);
    segundoBufferLista = segundoBufferLista->next;
  }
  for (; segundoBufferIntervalo != NULL;) {
    Intervalo* mostrar = segundoBufferIntervalo->data;
    printf("APLANAR[%i,%i]-", mostrar->inicio, mostrar->ultimo);
    listaAplanada = prepend_glist(listaAplanada, segundoBufferIntervalo->data);
    segundoBufferIntervalo = segundoBufferIntervalo->next;
  }
  if (listaAplanada == NULL) {
    return NULL;
  }
  listaAplanada = conjunto_union(listaAplanada);
  return listaAplanada;
}

GList aplanar_lista(Conjunto primero) {
  GList listaAplanada = initialization_glist();
  listaAplanada = glist_copiar_lista(primero->intervaloLista);
  GList aux = initialization_glist();
  aux = glist_copiar_lista(primero->lista);
  for (; aux!= NULL;) {
    Intervalo* numero_solo = malloc(sizeof(struct _Intervalo));
    int extremos = (int)aux->data;
    printf("numero libre -%i-\n", extremos);
    numero_solo->inicio = extremos;
    numero_solo->ultimo = extremos;
    numero_solo->cardinalidad = 1;
    numero_solo->esVacio = 0;
    listaAplanada = prepend_glist(listaAplanada, numero_solo);
    aux = aux->next;
  }
  return listaAplanada;
}

int existe_interseccion(Intervalo* A, Intervalo* B) {
  if (A->inicio <= B->inicio && A->ultimo >= B->inicio) {
    return 1;
  }
  if (B->inicio <= A->inicio && B->ultimo >= A->inicio) {
    return 1;
  }
  return 0;
}

GList conjunto_inters( GList intervaloOperandoA, GList intervaloOperandoB) {
  intervaloOperandoA = dlist_selectionSort(intervaloOperandoA);
  intervaloOperandoB = dlist_selectionSort(intervaloOperandoB);
  GList listaInterseccion = initialization_glist();
  int i = 0;
  int j = 0;
  while (i < largo_glist(intervaloOperandoA) && j < largo_glist(intervaloOperandoB)){
    Intervalo* nodoAEnPosI = malloc (sizeof(struct _Intervalo));
    Intervalo* nodoBEnPosJ = malloc (sizeof(struct _Intervalo));
    nodoAEnPosI = get_data_glist(intervaloOperandoA, i);
    nodoBEnPosJ = get_data_glist(intervaloOperandoB, j);
    if (existe_interseccion(nodoAEnPosI, nodoBEnPosJ)) {
      Intervalo* temporal = malloc (sizeof(struct _Intervalo));
      temporal->inicio = MAX (nodoAEnPosI->inicio, nodoBEnPosJ->inicio);
      temporal->ultimo = MIN (nodoAEnPosI->ultimo, nodoBEnPosJ->ultimo);
      nodoAEnPosI->inicio = temporal->ultimo + 1;
      nodoBEnPosJ->inicio = temporal->ultimo + 1;
      intervaloOperandoA = pisa_data_glist(intervaloOperandoA, i, nodoAEnPosI);
      intervaloOperandoB = pisa_data_glist(intervaloOperandoB, j, nodoBEnPosJ);
      if (nodoAEnPosI->inicio > nodoAEnPosI->ultimo || nodoAEnPosI->ultimo <= temporal->inicio) {
        i += 1;
      }
      if (nodoBEnPosJ->inicio > nodoBEnPosJ->ultimo || nodoBEnPosJ->ultimo <= temporal->inicio) {
        j += 1;
      }
      listaInterseccion = prepend_glist(listaInterseccion, temporal);
      continue;
    }
    if (nodoAEnPosI->inicio > nodoBEnPosJ->ultimo) {
      j += 1;
    }
    else
      i += 1;
  }
  return listaInterseccion;
}


GList conjunto_diferencia(GList intervaloA, Intervalo* intervaloB) {
  GList intervaloResta =  initialization_glist();
  if (largo_glist(intervaloA) <= 0) {
    intervaloResta = prepend_glist(intervaloResta, intervaloB);
    return intervaloResta;
  }
  Intervalo* nodoAEnPosI;
  Intervalo* nodoAEnPosZero;
  for(; largo_glist(intervaloA) > 0; intervaloA = intervaloA->next) {
    for (int i = 1; i < largo_glist(intervaloA); i++){
      nodoAEnPosI = get_data_glist(intervaloA, i);
      nodoAEnPosZero = get_data_glist(intervaloA, 0);
      if (nodoAEnPosI->inicio < nodoAEnPosZero->inicio) {
        intervaloA = pisa_data_glist(intervaloA, i, nodoAEnPosZero);
        intervaloA = pisa_data_glist(intervaloA, 0, nodoAEnPosI);
      }
    }
    nodoAEnPosZero = get_data_glist(intervaloA, 0);
    if (intervaloB->inicio < nodoAEnPosZero->inicio) {
      if (intervaloB->ultimo < nodoAEnPosZero->inicio) {
        intervaloResta = prepend_glist (intervaloResta, intervaloB);
        break;
      }
      Intervalo* temp =  malloc(sizeof(struct _Intervalo));
      temp->inicio =  intervaloB->inicio;
      temp->ultimo = nodoAEnPosZero->inicio - 1;
      intervaloResta =  prepend_glist(intervaloResta, temp);
      intervaloB->inicio = nodoAEnPosZero->inicio;
    }
    if (intervaloB->ultimo <= nodoAEnPosZero->ultimo) {
      break;
    }
    if (intervaloB->inicio <= nodoAEnPosZero->ultimo) {
      intervaloB->inicio = nodoAEnPosZero->ultimo + 1;
    }
    if (largo_glist(intervaloA) == 1) {
      if (intervaloB->inicio <= nodoAEnPosZero->ultimo) {
        intervaloB->inicio =  nodoAEnPosZero->ultimo + 1;
      }
      intervaloResta = prepend_glist(intervaloResta, intervaloB);
      break;
    }
  }
  return intervaloResta;
}

GList definir_conj_dif(Conjunto primero, Conjunto segundo) {
  GList listauno = aplanar_lista(primero);
  GList listados = aplanar_lista(segundo);
  GList lista = initialization_glist();
  GList listaDiferencia = initialization_glist();
  GList buff;
  for (; listauno != NULL; listauno = listauno->next) {
    lista = conjunto_diferencia(listados, (Intervalo*)listauno->data);
    buff = lista;
    for (; buff != NULL; buff = buff->next) {
      listaDiferencia = prepend_glist(listaDiferencia, buff->data);
      Intervalo* data = buff->data;
      printf("FOR:[%i,%i]\n",data->inicio, data->ultimo);
    }
  }
  return listaDiferencia;
}

GList definir_conj_comple(Conjunto operador) { /// [...],[...] UNION
  Intervalo* universal = malloc(sizeof(struct _Intervalo));
  universal->inicio = INT_INFLIM;
  universal->ultimo = INT_SUPLIM;
  Conjunto universo = malloc(sizeof(struct _Conjunto));
  universo->intervaloLista = malloc(sizeof(struct _GNodo));
  universo->intervaloLista = initialization_glist();
  universo->intervaloLista = prepend_glist(universo->intervaloLista, universal);
//a lo sumo inicializar "bien universo"
  GList complemento = initialization_glist();
  complemento = definir_conj_dif(universo, operador);
  return complemento;
}

void mostrar(GList lista) {
  for (; lista != NULL; lista = lista->next) {
    int num = (int)lista->data;
    printf("- %i -\n", num);
  }
}

void mostrar_glist(GList lista) {
  Conjunto var;
  for (; lista != NULL; lista = lista->next) {
    var = lista->data;
    mostrar(var->lista);
  }
}

void mostrar_intervalo(GList intervalll) {
  for (; intervalll != NULL;) {
    Intervalo* mostrar = intervalll->data;
    printf("-[%i,%i]-\n", mostrar->inicio, mostrar->ultimo);
    intervalll = intervalll->next;
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// nunca uso eliminar
int main() {
  int interprete = 0;
  struct _GNodo*** HASH;
  HASH =  inicializar_HASH();
  while (interprete == 0) {
    char* alias = malloc(LIMITE * sizeof(char));
    char* operacion = malloc(LIMITE * sizeof(char));
    fgets(alias, LIMITE, stdin);
    operacion = parsear_comando_y_operacion(alias, operacion); // alias = "alias" , operacion = {..}
    int instruccion = comando_int(operacion, alias);
    switch (instruccion) {
      case 1:
        printf("extension");
        printf("-%s- , -%s-", alias, operacion);
        Conjunto operando = definir_conj_ext(operacion, alias);//hashear operando con el alias
        hash_inserto(HASH, operando->alias, operando->lista, operando->intervaloLista);
        Conjunto aux = hash_busco(HASH, operando->alias);
        mostrar_conjunto(aux);
        free (operando);
        break;
      case 2:
        printf("comprension");
        printf("-%s- , -%s-", operacion, alias);
        Conjunto operandoB = definir_conj_com(operacion, alias);//hashea operando con el alias
        hash_inserto(HASH, operandoB->alias, operandoB->lista, operandoB->intervaloLista);
        Conjunto aux1 = hash_busco(HASH, operandoB->alias);
        mostrar_conjunto(aux1);
        free (operandoB);
        break;
      case 3:
        printf("union");
        Operandos* operandoUnion = sacar_operando_union_inters(operacion);
        printf("\nOPERANDO1.: -%s-\nOPERANDO2.: -%s-\n", operandoUnion->aliasOperandoA, operandoUnion->aliasOperandoB);//parsea a | b
        printf("\n\nUNION\n");
        Conjunto op1 = hash_busco(HASH, operandoUnion->aliasOperandoA);
        Conjunto op2 = hash_busco(HASH, operandoUnion->aliasOperandoB);
        if (op1 != NULL && op2 != NULL) {
          mostrar_conjunto(op1);
          mostrar_conjunto(op2);
          GList resultado = aplanar_solos_e_intervalos(op1, op2);
          Conjunto uniones = crear_conjunto(alias, NULL, resultado);
          hash_inserto(HASH, alias, NULL, resultado);
          mostrar_conjunto(uniones);
        } else {
          printf("\nUno de los operandos no existe...\n");
        }
        break;
      case 4:
        printf("interseccion");
        Operandos* operandoInterseccion = sacar_operando_union_inters(operacion);
        printf("\nOPERANDO1.: -%s-\nOPERANDO2.: -%s-\n", operandoInterseccion->aliasOperandoA, operandoInterseccion->aliasOperandoB);//parsea a | b
        Conjunto op3 = hash_busco(HASH, operandoInterseccion->aliasOperandoA);
        Conjunto op4 = hash_busco(HASH, operandoInterseccion->aliasOperandoB);
        if (op3 != NULL && op4 != NULL) {
          mostrar_conjunto(op3);
          mostrar_conjunto(op4);
          GList aplanada_op3 = aplanar_lista(op3);
          GList aplanada_op4 = aplanar_lista(op4);
          GList intersecciones = conjunto_inters(aplanada_op3, aplanada_op4);
          Conjunto interseccion = crear_conjunto(alias,NULL, intersecciones);
          hash_inserto(HASH, alias, NULL, intersecciones);
          mostrar_conjunto(interseccion);
        } else {
          printf("\nUno de los operandos no existe...\n");
        }
        break;
      case 5:
        printf("resta");
        Operandos* operandoResta = sacar_operando_union_inters(operacion);
        printf("\nOPERANDO1.: -%s-\nOPERANDO2.: -%s-\n", operandoResta->aliasOperandoA, operandoResta->aliasOperandoB);//parsea a | b
        Conjunto op5 = hash_busco(HASH, operandoResta->aliasOperandoA);
        Conjunto op6 = hash_busco(HASH, operandoResta->aliasOperandoB);
        if (op5 != NULL && op6 != NULL) {
          mostrar_conjunto(op5);
          mostrar_conjunto(op6);
          GList restas = definir_conj_dif(op5, op6);
          Conjunto resta = crear_conjunto(alias, NULL, restas);
          hash_inserto(HASH, alias, NULL, restas);
          mostrar_conjunto(resta);
        } else {
          printf("\nUno de los operandos no existe...\n");
        }
        break;
      case 6:
        printf("complemento");
        Operandos* operandoComplemento = sacar_operando_complemento(operacion);
        printf("\nOPERANDO1.: -%s-\nOPERANDO2.: -%s-\n", operandoComplemento->aliasOperandoA, operandoComplemento->aliasOperandoB);//parsea a | b
        Conjunto op7 = hash_busco(HASH, operandoComplemento->aliasOperandoA);
        if (op7 != NULL) {
          mostrar_conjunto(op7);
          GList complemetos = definir_conj_comple(op7);
          Conjunto complemento = crear_conjunto(alias, NULL, complemetos);
          hash_inserto(HASH, alias, NULL, complemetos);
          mostrar_conjunto(complemento);
        } else {
          printf("\nUno de los operandos no existe...\n");
        }
        break;
      case 7:
        printf("imprimir");
        printf("-%s-", alias);
        Operandos* operandoImprimir = sacar_operando_imprimir(alias);
        printf("\nOPERANDO1.: -%s-\nOPERANDO2.: -%s-\n", operandoImprimir->aliasOperandoA, operandoImprimir->aliasOperandoB);//parsea a | b
        Conjunto op8 = hash_busco(HASH, operandoImprimir->aliasOperandoA);
        if (op8 != NULL) {
          mostrar_conjunto_imprimir(op8);
        } else {
          printf("\nEl operando no existe...\n");
        }
        break;
      case 8:
        printf("salir");
        interprete = 1;
        break;
      case 9:
        printf("ERROR DE SINTAXIS");
        break;
    }
  }
  return 0;
}
