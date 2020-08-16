#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

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
  if(intervalos == NULL){
    return NULL;
  }
  intervalos = dlist_selectionSort(intervalos);
  printf("HOLAAAAa");

  int largo = largo_glist(intervalos);

  Stack pila = stack_new();
  Intervalo* inicio = get_data_glist(intervalos, 0);
  for (int i = 1; i < largo; i++) {
    Intervalo* posi = get_data_glist(intervalos, i);
    if(inicio->ultimo + 1 < posi->inicio ){
      stack_push(pila, inicio);
      inicio = posi;
    }
    if (inicio->ultimo  >= posi->inicio ){
      if(inicio->ultimo < posi->ultimo){
        inicio->ultimo = posi->ultimo;
      }
      continue;
    }
    if(inicio->ultimo + 1 == posi->inicio){
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
    printf("[%lld,%lld]-", intervaloUnion->inicio, intervaloUnion->ultimo);
    stack_pop(pila);
  }
  //
  stack_destruir(pila);
  //
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

    printf("APLANAR[%lld,%lld]-", mostrar->inicio,mostrar->ultimo);
    listaAplanada = prepend_glist(listaAplanada, cpy);
    primeroBufferIntervalo = primeroBufferIntervalo->next;
  }
  for (; primeroBufferLista != NULL;) {
    Intervalo* numero_solo = malloc(sizeof(struct _Intervalo));
    long long extremos = (long long)primeroBufferLista->data;
    printf("numero libre -%lld-\n", extremos);
    numero_solo->inicio = extremos;
    numero_solo->ultimo = extremos;
    numero_solo->cardinalidad = 1;
    numero_solo->esVacio = 0;
    printf("APLANAR1[%lld,%lld]-", numero_solo->inicio, numero_solo->ultimo);
    listaAplanada = prepend_glist(listaAplanada, numero_solo);
    primeroBufferLista = primeroBufferLista->next;
  }
  return listaAplanada;
}

GList concatenar_glist (GList listaA, GList listaB){
  if(listaA == NULL){
    GList listaSave = glist_copiar_lista(listaB);
    return listaSave;
  }
  if(listaB == NULL){
    GList listaSave = glist_copiar_lista(listaA);
    return listaSave;
  }

  GList listaSave = glist_copiar_lista(listaA);
  GList lista = listaSave;

  for(;lista->next != NULL; lista = lista->next);

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

GList definir_conj_union(Conjunto primero, Conjunto segundo) { //1->union 2->interseccion
  GList listaAplanada = initialization_glist();

  GList intervaloOperandoAA = aplanar_lista(primero);
  GList intervaloOperandoBB = aplanar_lista(segundo);

  GList intervaloOperandoA = glist_copiar_lista(intervaloOperandoAA);
  GList intervaloOperandoB = glist_copiar_lista(intervaloOperandoBB);

  GList unionCadenas = concatenar_glist(intervaloOperandoA,intervaloOperandoB);

  printf("PRIMEEEERO\n");
  mostrar_intervalo(intervaloOperandoA);
  printf("SEGUNDO\n");
  mostrar_intervalo(intervaloOperandoB);
  printf("UNION\n");
  mostrar_intervalo(unionCadenas);

  if (unionCadenas == NULL) {
    return NULL;
  }

  listaAplanada = conjunto_union(unionCadenas);
 //
dlist_destruir_intervalo(intervaloOperandoA);
dlist_destruir_intervalo(intervaloOperandoB);

dlist_destruir_int(intervaloOperandoAA);
dlist_destruir_int(intervaloOperandoBB);

dlist_destruir_int(unionCadenas);
  //

  //
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

GList conjunto_inters( Conjunto primero, Conjunto segundo) {

  if(primero->lista == NULL && primero->intervaloLista == NULL){
    return NULL;
  }
  if(segundo->lista == NULL && segundo->intervaloLista == NULL){
    return NULL;
  }

  GList intervaloOperandoAA = aplanar_lista(primero);
  GList intervaloOperandoBB = aplanar_lista(segundo);
  printf("\nINTERSECCION DENTRO ANTES\n");
  mostrar_intervalo(intervaloOperandoAA);

  GList intervaloOperandoAAA = dlist_selectionSort(intervaloOperandoAA);
  GList intervaloOperandoBBB = dlist_selectionSort(intervaloOperandoBB);

  GList intervaloOperandoA = glist_copiar_lista(intervaloOperandoAAA);
  GList intervaloOperandoB = glist_copiar_lista(intervaloOperandoBBB);

    printf("\nINTERSECCION DENTRO DESPUES DEL SORT\n");
  mostrar_intervalo(intervaloOperandoAA);

  GList listaInterseccion = initialization_glist();
  int i = 0;
  int j = 0;
  for (;i < largo_glist(intervaloOperandoA) && j < largo_glist(intervaloOperandoB);){
    Intervalo* nodoAEnPosI = malloc (sizeof(struct _Intervalo));
    Intervalo* nodoBEnPosJ = malloc (sizeof(struct _Intervalo));

    Intervalo* nodoAEnPosII = get_data_glist(intervaloOperandoA, i);
    Intervalo* nodoBEnPosJJ = get_data_glist(intervaloOperandoB, j);

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
            ++i;
        }
        else{
            ++j;
        }
        if(temporal->esVacio == 0){
            listaInterseccion = prepend_glist(listaInterseccion, temporal);
        }
        if(temporal->esVacio == 1){
            free(temporal);
        }
    }
    else if(nodoAEnPosI->inicio < nodoBEnPosJ->inicio){
        if(nodoAEnPosI->ultimo >= nodoBEnPosJ->ultimo){
            ++j;
        }
        else{
            ++i;
        }
        if(temporal->esVacio == 0){
            listaInterseccion = prepend_glist(listaInterseccion, temporal);
        }
        if(temporal->esVacio == 1){
          free(temporal);
        }
    }
    else{
        if(nodoAEnPosI->ultimo < nodoBEnPosJ->ultimo){
            ++i;
        }
        else if(nodoAEnPosI->ultimo > nodoBEnPosJ->ultimo){
            ++j;
        }
        else{
            ++i;
            ++j;
        }
        listaInterseccion = prepend_glist(listaInterseccion, temporal);
    }
    free(nodoAEnPosI);
    free(nodoBEnPosJ);

  }
////

  printf("INTERSECCION DENTRO\n");

  mostrar_intervalo(intervaloOperandoAA);
  mostrar_intervalo(intervaloOperandoA);
  printf("RESULTADO 420:\n");
  mostrar_intervalo(listaInterseccion);



    printf("DESTRUIR 1:\n");
  dlist_destruir_intervalo(intervaloOperandoA);
  printf("DESTRUIR 2:\n");
  dlist_destruir_intervalo(intervaloOperandoB);
//  printf("______________\n");
//  dlist_destruir_intervalo(intervaloOperandoAAA);
//    printf("______________\n");
//  dlist_destruir_intervalo(intervaloOperandoBBB);
///    printf("______________\n");
printf("DESTRUIR 3:\n");
  dlist_destruir_int(intervaloOperandoAA);

  printf("DESTRUIR 4:\n");
  dlist_destruir_int(intervaloOperandoBB);

  //free(intervaloOperandoAA);
  //free(intervaloOperandoBB);

  return listaInterseccion;
}


GList conjunto_diferencia_dos(GList intervaloA, Intervalo* intervaloB){
intervaloA = dlist_selectionSort(intervaloA);
int len = largo_glist(intervaloA);
GList res = initialization_glist();
        for (int i = 0; i < len; i++) {
            Intervalo* data = get_data_glist(intervaloA,i);

            long long left = data->inicio;
            long long right = data->ultimo;

            if(right == intervaloB->ultimo && left == intervaloB->inicio){
                continue;
            }
            if (right <= intervaloB->inicio) {
                if(right < intervaloB->inicio){
                Intervalo* interval = malloc(sizeof(struct _Intervalo));
                interval->inicio = left;
                interval->ultimo = right;

                interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
                interval->esVacio = 0;

                res = prepend_glist(res, interval);
                }
                if(right == intervaloB->inicio){
                Intervalo* interval = malloc(sizeof(struct _Intervalo));
                interval->inicio = left;
                interval->ultimo = right-1;

                interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
                interval->esVacio = 0;

                res = prepend_glist(res, interval);
                }
            } else if (left < intervaloB->inicio && right <= intervaloB->ultimo) {
                  Intervalo* interval = malloc(sizeof(struct _Intervalo));
                interval->inicio = left;
                interval->ultimo = intervaloB->inicio-1;

                interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
                interval->esVacio = 0;

                res = prepend_glist(res, interval);
            } else if (left < intervaloB->inicio && right > intervaloB->ultimo) {
                   Intervalo* interval1 = malloc(sizeof(struct _Intervalo));
                interval1->inicio = left;
                interval1->ultimo = intervaloB->inicio-1;
                interval1->cardinalidad = (interval1->ultimo - interval1->inicio) + 1;
                interval1->esVacio = 0;

                res = prepend_glist(res, interval1);

                Intervalo* interval2 =  malloc(sizeof(struct _Intervalo));
                interval2->inicio = intervaloB->ultimo+1;
                interval2->ultimo = right;
                interval2->cardinalidad = (interval2->ultimo - interval2->inicio) + 1;
                interval2->esVacio = 0;
                res = prepend_glist(res, interval2);
            } else if (left >= intervaloB->inicio && left <= intervaloB->ultimo && right > intervaloB->ultimo) {
                Intervalo* interval = malloc(sizeof(struct _Intervalo));
                interval->inicio = intervaloB->ultimo+1;//
                interval->ultimo = right;
                interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
                interval->esVacio = 0;
                res = prepend_glist(res, interval);
            } else if (left >= intervaloB->ultimo) {
                if(left > intervaloB->ultimo){
                Intervalo* interval = malloc(sizeof(struct _Intervalo));
                interval->inicio = left;
                interval->ultimo = right;
                interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
                interval->esVacio = 0;
                res = prepend_glist(res, interval);
                }
                if(left == intervaloB->ultimo){
                Intervalo* interval = malloc(sizeof(struct _Intervalo));
                interval->inicio = left+1;
                interval->ultimo = right;
                interval->cardinalidad = (interval->ultimo - interval->inicio) + 1;
                interval->esVacio = 0;
                res = prepend_glist(res, interval);
                }
            }
        }
        return res;
    }


GList definir_conj_dif_dos(Conjunto primero, Conjunto segundo) {
  if(strcmp(primero->alias, segundo->alias) == 0){// R - R = NULL
    return NULL;
  }

  if(primero->lista == NULL && primero->intervaloLista == NULL){
    return NULL;
  }

  if(segundo->lista == NULL && segundo->intervaloLista == NULL){
    GList base = aplanar_lista(primero);
    return base;
  }

  GList bufferlistauno = aplanar_lista(primero);
  GList bufferlistados = aplanar_lista(segundo);

  GList listauno = bufferlistauno;
  GList listados = bufferlistados;

  if(listauno == NULL){// NULL - R = NULL
    return NULL;
  }

  Stack pila = stack_new();
  GList listaDiferencia = initialization_glist();
  GList buff;
  for (; listados != NULL; listados = listados->next) {
    Intervalo* datazo = (Intervalo*)listados->data;

    Intervalo* dato = malloc(sizeof(struct _Intervalo));
    dato->inicio = datazo->inicio;
    dato->ultimo = datazo->ultimo;
    dato->cardinalidad = datazo->cardinalidad;
    dato->esVacio = datazo->esVacio;
    printf("\nQUEDAAAAAAA1:\n");
    mostrar_intervalo(primero->intervaloLista);
    GList lista = conjunto_diferencia_dos(listauno, dato);
    stack_push(pila,lista);
    printf("\nQUEDAAAAAAA2:\n");
    mostrar_intervalo(primero->intervaloLista);
    mostrar_intervalo(lista);

    free(dato);
   // listauno = lista;

  }
  GList resultado = initialization_glist();
  if(stack_es_vacio(pila)){
    resultado = NULL;
  }
  else{
  while(!stack_es_vacio(pila)){
    GList opA = stack_top(pila);
    stack_pop(pila);
    if(stack_es_vacio(pila)){
        resultado = opA;
    }
    else{
        GList opB = stack_top(pila);
        stack_pop(pila);
        Conjunto A = crear_conjunto("",NULL,opA);
        Conjunto B = crear_conjunto("",NULL,opB);

        GList intermedio = conjunto_inters(A,B);
        stack_push(pila,intermedio);

        dlist_destruir_intervalo(opA);
        dlist_destruir_intervalo(opB);

        dlist_destruir_int(A->lista);
        dlist_destruir_int(A->intervaloLista);
        free(A->alias);
        free(A);

        dlist_destruir_int(B->lista);
        dlist_destruir_int(B->intervaloLista);
        free(B->alias);
        free(B);
       //destruir_conjunto(A,NULL);///
      //  destruir_conjunto(B,NULL);///

    }
  }
  }

  printf("\nQUEDAAAAAAA3:\n");
  mostrar_intervalo(primero->intervaloLista);

  //
  dlist_destruir_intervalo(bufferlistauno);
  dlist_destruir_intervalo(bufferlistados);
  free(pila);
  //
  return resultado;
}


GList conjunto_diferencia(GList intervaloA, Intervalo* intervaloB) {

  GList intervaloABuffer = intervaloA;
  GList intervaloResta =  initialization_glist();
  if (largo_glist(intervaloA) <= 0) {
    intervaloResta = prepend_glist(intervaloResta, intervaloB);
    return intervaloResta;
  }
  Intervalo* nodoAEnPosI;
  Intervalo* nodoAEnPosZero;
  for(; largo_glist(intervaloABuffer) > 0; intervaloABuffer = intervaloABuffer->next) {
    for (int i = 1; i < largo_glist(intervaloABuffer); i++){
      nodoAEnPosI = get_data_glist(intervaloABuffer, i);
      nodoAEnPosZero = get_data_glist(intervaloABuffer, 0);
      if (nodoAEnPosI->inicio < nodoAEnPosZero->inicio) {
        intervaloABuffer = pisa_data_glist(intervaloABuffer, i, nodoAEnPosZero);
        intervaloABuffer = pisa_data_glist(intervaloABuffer, 0, nodoAEnPosI);
      }
    }
    nodoAEnPosZero = get_data_glist(intervaloABuffer, 0);
    if (intervaloB->inicio < nodoAEnPosZero->inicio) {
      if (intervaloB->ultimo < nodoAEnPosZero->inicio) {
        intervaloResta = prepend_glist (intervaloResta, intervaloB);
        break;
      }
      Intervalo* temp =  malloc(sizeof(struct _Intervalo));
      temp->inicio =  intervaloB->inicio;
      temp->ultimo = nodoAEnPosZero->inicio - 1;
      temp->cardinalidad = (temp->ultimo - temp->inicio) + 1;
      if(temp->inicio <= temp->ultimo){
        temp->esVacio = 0;
      }
      if(temp->inicio > temp->ultimo){
        temp->esVacio = 1;
      }
      intervaloResta =  prepend_glist(intervaloResta, temp);
      intervaloB->inicio = nodoAEnPosZero->inicio;
    }
    if (intervaloB->ultimo <= nodoAEnPosZero->ultimo) {
      break;
    }
    if (intervaloB->inicio <= nodoAEnPosZero->ultimo) {
      intervaloB->inicio = nodoAEnPosZero->ultimo + 1;
    }
    if (largo_glist(intervaloABuffer) == 1) {
      if (intervaloB->inicio <= nodoAEnPosZero->ultimo) {
        intervaloB->inicio =  nodoAEnPosZero->ultimo + 1;
      }
      intervaloResta = prepend_glist(intervaloResta, intervaloB);
      break;
    }
  }
  printf("\nRESTAAAAAAAAA:\n");
  mostrar_intervalo(intervaloA);
  return intervaloResta;
}

GList definir_conj_dif(Conjunto primero, Conjunto segundo) {
  if(strcmp(primero->alias, segundo->alias) == 0){// R - R = NULL
    return NULL;
  }

  GList bufferlistauno = aplanar_lista(primero);
  GList bufferlistados = aplanar_lista(segundo);

  GList listauno = bufferlistauno;
  GList listados = bufferlistados;

  if(listauno == NULL){// NULL - R = NULL
    return NULL;
  }

  GList lista = initialization_glist();
  GList listaDiferencia = initialization_glist();
  GList buff;
  for (; listauno != NULL; listauno = listauno->next) {
    Intervalo* datazo = (Intervalo*)listauno->data;

    Intervalo* dato = malloc(sizeof(struct _Intervalo));
    dato->inicio = datazo->inicio;
    dato->ultimo = datazo->ultimo;
    dato->cardinalidad = datazo->cardinalidad;
    dato->esVacio = datazo->esVacio;
    printf("\nQUEDAAAAAAA1:\n");
    mostrar_intervalo(primero->intervaloLista);
    lista = conjunto_diferencia(listados, dato);
    printf("\nQUEDAAAAAAA2:\n");
    mostrar_intervalo(primero->intervaloLista);
    mostrar_intervalo(lista);

    buff = lista;
    for (; buff != NULL; buff = buff->next) {
      Intervalo* dat = (Intervalo*) buff->data;

      Intervalo* date = malloc(sizeof(struct _Intervalo));
      date->inicio = dat->inicio;
      date->ultimo = dat->ultimo;
      date->cardinalidad = dat->cardinalidad;
      date->esVacio = dat->esVacio;
      listaDiferencia = prepend_glist(listaDiferencia, date);
      Intervalo* data = buff->data;
      printf("FOR:[%lld,%lld] %lld %i\n",date->inicio, date->ultimo, date->cardinalidad, date->esVacio);
    }
  }
  printf("\nQUEDAAAAAAA3:\n");
  mostrar_intervalo(primero->intervaloLista);

  //
  dlist_destruir_intervalo(bufferlistauno);
  dlist_destruir_intervalo(bufferlistados);
  dlist_destruir_intervalo(lista);
  //
  return listaDiferencia;
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// nunca uso eliminar
int main() {
  int interprete = 0;
  int test = 0;
  struct _GNodo*** HASH;
  HASH =  inicializar_HASH();

  GList freeLista = initialization_glist(); //ext y com
  int inicializarUniversal = 0;

  while (interprete == 0) {

    char* alias = malloc(LIMITE * sizeof(char));
    //char* operacion = malloc(LIMITE * sizeof(char));

    //fgets(alias, LIMITE, stdin);

        if(test == 2){
        strcpy(alias,"c = ~a ");
        test++;
    }

        if(test == 1){
        strcpy(alias,"b = {1,-1,2,-1000,3,-1313,4,-10,5} ");
        test++;
    }

    if(test == 0){
        strcpy(alias,"a = {-1,-1000,-1313,-10} ");
        test++;
    }

  //  printf("OPERACION ANTERS DE PARSER: %s\n",operacionA);
    char* operacion = parsear_comando_y_operacion(alias, operacion); // alias = "alias" , operacion = {..}
  //  printf("OPERACION DESPUES DE PARSER: %s\n",operacionA);
  //  printf("OPERACION DESPUES DE PARSER: %s\n",operacion);
    int instruccion = comando_int(operacion, alias);
  //  printf("OPERACION DESPUES DE COMANDO: %s\n",operacion);
    system("pause");

    switch (instruccion) {
      case 1:
        printf("extension");
        printf("-%s- , -%s-", alias, operacion);
        Conjunto operando = definir_conj_ext(operacion, alias);//hashear operando con el alias
        mostrar_conjunto(operando);
        printf("QUILOMBO");
        hash_inserto(HASH, operando->alias, operando->lista, operando->intervaloLista);
        Conjunto aux = hash_busco(HASH, operando->alias);
        mostrar_conjunto(aux);
        freeLista = prepend_glist(freeLista, operando);
        free(alias);
    //    system("pause");
        break;
      case 2:
        printf("comprension");
        printf("-%s- , -%s-", operacion, alias);
    //    printf("OPERACION ANTES DE DEFINICION: %s\n",operacion);
        Conjunto operandoB = definir_conj_com(operacion, alias);//hashea operando con el alias
    //    printf("OPERACION DEspues DE DEFINICION1: %s\n",operacion);
        mostrar_conjunto(operandoB);
        printf("HOLAAAAA");
        hash_inserto(HASH, operandoB->alias, operandoB->lista, operandoB->intervaloLista);
        printf("HOLAAAAA");
        Conjunto aux1 = hash_busco(HASH, operandoB->alias);
        mostrar_conjunto(aux1);
        freeLista = prepend_glist(freeLista,operandoB);
    //    printf("OPERACION DESPUES DE DEFINICION2: %s\n",operacion);
    //    printf("ALIAS DESPUES DE DEFINICION2: %s\n",alias);

     //   printf("ALIAS DESPUES DE DEFINICION2: %s\n",alias);
     //   printf("OPERACION DESPUES DE DEFINICION: %s\n",operacion);
        free(alias);
    //    printf("OPERACION DESPUES DE DEFINICION: %s\n",operacion);
    //    system("pause");

        //system("pause");
        break;
      case 3:
        printf("union");

        Operandos* operandoUnion = sacar_operando_union_inters(operacion);
        printf("\nOPERANDO1.: -%s-\nOPERANDO2.: -%s-\n", operandoUnion->aliasOperandoA, operandoUnion->aliasOperandoB);//parsea a | b
        Conjunto op1 = hash_busco(HASH, operandoUnion->aliasOperandoA);
        Conjunto op2 = hash_busco(HASH, operandoUnion->aliasOperandoB);

        if (op1 != NULL && op2 != NULL) {

          GList resultado = definir_conj_union(op1, op2);
          mostrar_conjunto(op1);
          mostrar_conjunto(op2);
          Conjunto uniones = crear_conjunto(alias, NULL, resultado);
          hash_inserto(HASH, alias, NULL, resultado);
          mostrar_conjunto(uniones);
          printf("OPERANDOS UNION:\n");
          mostrar_conjunto(op1);
          mostrar_conjunto(op2);
          printf("____________________\n");
          freeLista = prepend_glist(freeLista, uniones);
          dlist_destruir_int(resultado);

        } else {
            printf("\nUno de los operandos no existe...\n");
            if (op1 == NULL){
              printf("\n%s NO EXISTE COMO OPERANDO\n", operandoUnion->aliasOperandoA);
            }
            if (op2 == NULL){
              printf("\n%s NO EXISTE COMO OPERANDO\n", operandoUnion->aliasOperandoB);
            }
          }

        free(alias);
        free(operandoUnion);

        //system("pause");
        interprete = 1;
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
          GList intersecciones = conjunto_inters(op3, op4);
          Conjunto interseccion = crear_conjunto(alias,NULL, intersecciones);
          hash_inserto(HASH, alias, NULL, intersecciones);
          mostrar_conjunto(interseccion);
          printf("OPERANDOS INTERSECCION:\n");
          mostrar_conjunto(op3);
          mostrar_conjunto(op4);
          printf("____________________\n");
          freeLista = prepend_glist(freeLista, interseccion);
          dlist_destruir_int(intersecciones);

        } else {
          printf("\nUno de los operandos no existe...\n");
            if (op3 == NULL){
              printf("\n%s NO EXISTE COMO OPERANDO\n", operandoInterseccion->aliasOperandoA);
            }
            if (op4 == NULL){
              printf("\n%s NO EXISTE COMO OPERANDO\n", operandoInterseccion->aliasOperandoB);
            }
          }
        free(alias);
        free(operandoInterseccion);
        interprete = 1;
       // system("pause");
        break;
      case 5:
        printf("resta");
        Operandos* operandoResta = sacar_operando_union_inters(operacion);//free operandos
        printf("\nOPERANDO1.: -%s-\nOPERANDO2.: -%s-\n", operandoResta->aliasOperandoA, operandoResta->aliasOperandoB);//parsea a | b
        Conjunto op5 = hash_busco(HASH, operandoResta->aliasOperandoA);
        Conjunto op6 = hash_busco(HASH, operandoResta->aliasOperandoB);

        if (op5 != NULL && op6 != NULL) {
          GList restas = definir_conj_dif_dos(op5, op6);
          Conjunto resta = crear_conjunto(alias, NULL, restas);
          hash_inserto(HASH, alias, NULL, restas);
          mostrar_conjunto(resta);
          printf("OPERANDOS DE LA OPERACION:\n\n");
          mostrar_conjunto(op5);
          printf("________________\n");
          mostrar_conjunto(op6);
          freeLista = prepend_glist(freeLista,resta);
          dlist_destruir_int(restas);
        } else {
            printf("\nUno de los operandos no existe...\n");
            if (op5 == NULL){
              printf("\n%s NO EXISTE COMO OPERANDO\n", operandoResta->aliasOperandoA);
            }
            if (op6 == NULL){
              printf("\n%s NO EXISTE COMO OPERANDO\n", operandoResta->aliasOperandoB);
            }
          }

        free(alias);
        free(operandoResta);

interprete = 1;

        break;
      case 6:

        printf("complemento");

        Operandos* operandoComplemento = sacar_operando_complemento(operacion);
        printf("\nOPERANDO1.: -%s-\nOPERANDO2.: -%s-\n", operandoComplemento->aliasOperandoA, operandoComplemento->aliasOperandoB);//parsea a | b
        Conjunto op7 = hash_busco(HASH, operandoComplemento->aliasOperandoA);

        if (inicializarUniversal == 0){
         char aliasa[] = "universal";
         char operacione[] = " {x : -2147483648 <= x <= 2147483647}";//{x : -32767 <= x <= 32767}
         printf("-%s- , -%s-", operacione, aliasa);
         Conjunto operandoBB = definir_conj_com(operacione, aliasa);//hashea operando con el alias
         hash_inserto(HASH, operandoBB->alias, operandoBB->lista, operandoBB->intervaloLista);
         Conjunto aux1 = hash_busco(HASH, operandoBB->alias);
         mostrar_conjunto(aux1);
         freeLista = prepend_glist(freeLista,operandoBB);
         inicializarUniversal = 1;
       }

        Conjunto op8 = hash_busco(HASH, "universal");
        if (op8 == NULL){printf("\nOP1 NULL\n");}

        if (op7 != NULL) {
          mostrar_conjunto(op7);
          mostrar_conjunto(op8);
          GList complemetos = definir_conj_dif_dos(op8, op7);
          Conjunto complemento = crear_conjunto(alias, NULL, complemetos);
          hash_inserto(HASH, alias, NULL, complemetos);
          mostrar_conjunto(complemento);
          mostrar_conjunto(op7);
          freeLista = prepend_glist(freeLista,complemento);
          dlist_destruir_int(complemetos);
        } else {
            printf("\nUno de los operandos no existe...\n");
            if (op7 == NULL){
              printf("\n%s NO EXISTE COMO OPERANDO\n", operandoComplemento->aliasOperandoA);
            }
          }
        free(alias);
        free(operandoComplemento);

   //     system("pause");
   interprete = 1;
        break;
      case 7:
        printf("imprimir");
        printf("-%s-", alias);
        Operandos* operandoImprimir = sacar_operando_imprimir(alias);
        printf("\nOPERANDO1.: -%s-\nOPERANDO2.: -%s-\n", operandoImprimir->aliasOperandoA, operandoImprimir->aliasOperandoB);//parsea a | b
        Conjunto op9 = hash_busco(HASH, operandoImprimir->aliasOperandoA);
        if (op9 != NULL) {
          mostrar_conjunto_imprimir(op9);
        } else {
          printf("\nEl operando %s no existe...\n", operandoImprimir->aliasOperandoA);
        }
        free(alias);
        free(operandoImprimir);
        //system("pause");
        break;
      case 8:
        printf("salir");
        free(alias);
        interprete = 1;
        break;
      case 9:
        printf("\nERROR DE SINTAXIS\n");
        free(alias);
        break;
    }
  }

  free_table(HASH);

//FREE COMPRENSION Y "EXTENSION" ESQUELETO
  GList proximo = freeLista;
  GList actual;
  for(; proximo != NULL;){
    actual = proximo;
    proximo = proximo->next;
    Conjunto fr = (Conjunto) actual->data;
    printf("\nALIAS A ELIMINAR X2\n");

    free(fr->alias);

    dlist_destruir_int(fr->lista);
    dlist_destruir_int(fr->intervaloLista);
    free(fr);
    free(actual);
  }

 // system("pause");
  return 0;
}
