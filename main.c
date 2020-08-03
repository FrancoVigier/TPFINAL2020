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
  //segundoBufferLista = recursaSegundo->lista;
  for (; primeroBufferIntervalo != NULL;) {
    Intervalo* mostrar = primeroBufferIntervalo->data;

    Intervalo* cpy = malloc(sizeof(struct _Intervalo));
    cpy->cardinalidad = mostrar->cardinalidad;
    cpy->esVacio = mostrar->esVacio;
    cpy->inicio = mostrar->inicio;
    cpy->ultimo = mostrar->ultimo;

    printf("APLANAR[%i,%i]-", mostrar->inicio,mostrar->ultimo);
    listaAplanada = prepend_glist(listaAplanada, cpy);
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

    Intervalo* cpy = malloc(sizeof(struct _Intervalo));
    cpy->cardinalidad = mostrar->cardinalidad;
    cpy->esVacio = mostrar->esVacio;
    cpy->inicio = mostrar->inicio;
    cpy->ultimo = mostrar->ultimo;

    printf("APLANAR[%i,%i]-", mostrar->inicio, mostrar->ultimo);
    listaAplanada = prepend_glist(listaAplanada, cpy);
    segundoBufferIntervalo = segundoBufferIntervalo->next;
  }
  if (listaAplanada == NULL) {
    return NULL;
  }

  GList listaAplana = conjunto_union(listaAplanada);
  return listaAplana;
}

GList aplanar_lista(Conjunto primero) {


  GList listaAplanada = initialization_glist();
  Conjunto recursaPrimero = primero;

  GList primeroBufferIntervalo = initialization_glist();
  GList primeroBufferLista = initialization_glist();

  primeroBufferIntervalo = glist_copiar_lista(recursaPrimero->intervaloLista);
  primeroBufferLista = glist_copiar_lista(recursaPrimero->lista);

 for (; primeroBufferIntervalo != NULL;) {
    Intervalo* mostrar = primeroBufferIntervalo->data;

    Intervalo* cpy = malloc(sizeof(struct _Intervalo));
    cpy->cardinalidad = mostrar->cardinalidad;
    cpy->esVacio = mostrar->esVacio;
    cpy->inicio = mostrar->inicio;
    cpy->ultimo = mostrar->ultimo;

    printf("APLANAR[%i,%i]-", mostrar->inicio,mostrar->ultimo);
    listaAplanada = prepend_glist(listaAplanada, cpy);
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

GList conjunto_inters( GList intervaloOperandoAA, GList intervaloOperandoBB) {
  GList intervaloOperandoA = dlist_selectionSort(intervaloOperandoAA);
  GList intervaloOperandoB = dlist_selectionSort(intervaloOperandoBB);
  GList listaInterseccion = initialization_glist();
  int i = 0;
  int j = 0;
  while (i < largo_glist(intervaloOperandoA) && j < largo_glist(intervaloOperandoB)){
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

    if (existe_interseccion(nodoAEnPosI, nodoBEnPosJ)) {
      Intervalo* temporal = malloc (sizeof(struct _Intervalo));
      temporal->inicio = MAX (nodoAEnPosI->inicio, nodoBEnPosJ->inicio);
      temporal->ultimo = MIN (nodoAEnPosI->ultimo, nodoBEnPosJ->ultimo);

      temporal->cardinalidad = (temporal->ultimo - temporal->inicio) + 1;
      if(temporal->inicio <= temporal->ultimo){
        temporal->esVacio = 0;
      }
      if(temporal->inicio > temporal->ultimo){
        temporal->esVacio = 1;
      }

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

void mostrar_intervalo(GList intervalll) {
  for (; intervalll != NULL;) {
    Intervalo* mostrar = intervalll->data;
    printf("-[%i,%i]-\n", mostrar->inicio, mostrar->ultimo);
    intervalll = intervalll->next;
  }
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
  GList listauno = aplanar_lista(primero);
  GList listados = aplanar_lista(segundo);
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
    buff = lista;
    for (; buff != NULL; buff = buff->next) {
      listaDiferencia = prepend_glist(listaDiferencia, buff->data);
      Intervalo* data = buff->data;
      printf("FOR:[%i,%i] %i %i\n",data->inicio, data->ultimo, data->cardinalidad, data->esVacio);
    }
  }
  printf("\nQUEDAAAAAAA3:\n");
  mostrar_intervalo(primero->intervaloLista);
  return listaDiferencia;
}

GList definir_conj_comple(Conjunto operador) { /// [...],[...] UNION
  Intervalo* universal = malloc(sizeof(struct _Intervalo));
  universal->inicio = INT_INFLIM;
  universal->ultimo = INT_SUPLIM;
  universal->cardinalidad = 0;
  universal->esVacio = 0;

  GList lista = initialization_glist();
  lista = prepend_glist(lista, universal);

  Conjunto uni = crear_conjunto("universo", NULL, lista);

//a lo sumo inicializar "bien universo"
  GList complemento = initialization_glist();
  complemento = definir_conj_dif(uni, operador);
  dlist_destruir_intervalo(lista);
  destruir_conjunto(uni, NULL);
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

  int instruccion = 2;
  int test = 1;
  Conjunto testt;
  Conjunto testt2;
  GList freeLista = initialization_glist();
  while (interprete == 0) {
///    char* alias = malloc(LIMITE * sizeof(char));
///    char* operacion = malloc(LIMITE * sizeof(char));
///    fgets(alias, LIMITE, stdin);
///    operacion = parsear_comando_y_operacion(alias, operacion); // alias = "alias" , operacion = {..}
///    int instruccion = comando_int(operacion, alias);

    switch (instruccion) {
      case 1:
        printf("extension");
/*
        if(test == 1){
          char alias[] = "pepe";
          char operacion[] = " {10,11,12,13}";

        printf("-%s- , -%s-", alias, operacion);
        Conjunto operando = definir_conj_ext(operacion, alias);//hashear operando con el alias
        hash_inserto(HASH, operando->alias, operando->lista, operando->intervaloLista);
        Conjunto aux = hash_busco(HASH, operando->alias);
        mostrar_conjunto(aux);
        //free (operando);
        destruir_conjunto(operando,NULL);

        }
        if(test == 2){
          char alias[] = "papa";
          char operacion[] = " {1,3,6,7}";

        printf("-%s- , -%s-", alias, operacion);
        Conjunto operando = definir_conj_ext(operacion, alias);//hashear operando con el alias
        hash_inserto(HASH, operando->alias, operando->lista, operando->intervaloLista);
        Conjunto aux = hash_busco(HASH, operando->alias);
        mostrar_conjunto(aux);
        //free (operando);
        destruir_conjunto(operando,NULL);
        }
        if(test == 2){
          instruccion = 3;
        }
        test++;
      ///  system("pause");
      */
        break;
      case 2:
        printf("comprension");

      //  char alias[] = "pepe";
      //  char operacion[] = " {x : 2 <= x <= 100}";

        if(test == 1){
        char alias[] = "pepe";
        char operacion[] = " {x : 2 <= x <= 100}";
        printf("-%s- , -%s-", operacion, alias);
        Conjunto operandoB = definir_conj_com(operacion, alias);//hashea operando con el alias
        hash_inserto(HASH, operandoB->alias, operandoB->lista, operandoB->intervaloLista);
        Conjunto aux1 = hash_busco(HASH, operandoB->alias);
        mostrar_conjunto(aux1);
        //free (operandoB);
        testt = operandoB;
        freeLista = prepend_glist(freeLista,operandoB);
        //destruir_conjunto(operandoB,NULL);
        }
        if(test == 2){
        char alias[] = "papa";
        char operacion[] = " {x : 50 <= x <= 200}";
        printf("-%s- , -%s-", operacion, alias);
        Conjunto operandoB = definir_conj_com(operacion, alias);//hashea operando con el alias
        hash_inserto(HASH, operandoB->alias, operandoB->lista, operandoB->intervaloLista);
        Conjunto aux1 = hash_busco(HASH, operandoB->alias);
        mostrar_conjunto(aux1);
        //free (operandoB);
        testt2 = operandoB;
        freeLista = prepend_glist(freeLista,operandoB);
        //destruir_conjunto(operandoB,NULL);
        }
        if(test == 2){
          instruccion = 6;
        }
        test++;
      //  interprete = 1;
      system("pause");
        break;
      case 3:
        printf("union");
        /*
        Operandos* operandoUnion = sacar_operando_union_inters(operacion);
        printf("\nOPERANDO1.: -%s-\nOPERANDO2.: -%s-\n", operandoUnion->aliasOperandoA, operandoUnion->aliasOperandoB);//parsea a | b
        printf("\n\nUNION\n");
        Conjunto op1 = hash_busco(HASH, operandoUnion->aliasOperandoA);
        Conjunto op2 = hash_busco(HASH, operandoUnion->aliasOperandoB);
        */
        Conjunto op1 = hash_busco(HASH, "pepe");
        Conjunto op2 = hash_busco(HASH, "papa");
        if(op1 == NULL){printf("\nOP1 NULL\n");}
        if(op2 == NULL){printf("\nOP2 NULL\n");}

        if (op1 != NULL && op2 != NULL) {

          GList resultado = aplanar_solos_e_intervalos(op1, op2);
          mostrar_conjunto(op1);
          mostrar_conjunto(op2);
          Conjunto uniones = crear_conjunto("carlos", NULL, resultado);
          hash_inserto(HASH, "carlos", NULL, resultado);
          mostrar_conjunto(uniones);


        } else {
          printf("\nUno de los operandos no existe...\n");
        }

/*
        if (op1 != NULL && op2 != NULL) {
          mostrar_conjunto(op1);
          mostrar_conjunto(op2);}
          GList resultado = aplanar_solos_e_intervalos(op1, op2);
          Conjunto uniones = crear_conjunto(alias, NULL, resultado);
          hash_inserto(HASH, alias, NULL, resultado);
          mostrar_conjunto(uniones);
        } else {
          printf("\nUno de los operandos no existe...\n");
        }
*/
        interprete = 1;

        break;
      case 4:
          /*

        Operandos* operandoInterseccion = sacar_operando_union_inters(operacion);
        printf("\nOPERANDO1.: -%s-\nOPERANDO2.: -%s-\n", operandoInterseccion->aliasOperandoA, operandoInterseccion->aliasOperandoB);//parsea a | b
        Conjunto op3 = hash_busco(HASH, operandoInterseccion->aliasOperandoA);
        Conjunto op4 = hash_busco(HASH, operandoInterseccion->aliasOperandoB);
        */
        printf("interseccion");
        Conjunto op3 = hash_busco(HASH, "pepe");
        Conjunto op4 = hash_busco(HASH, "papa");
        if(op3 == NULL){printf("\nOP1 NULL\n");}
        if(op4 == NULL){printf("\nOP2 NULL\n");}


        if (op3 != NULL && op4 != NULL) {
          mostrar_conjunto(op3);
          mostrar_conjunto(op4);
          GList aplanada_op3 = aplanar_lista(op3);
          GList aplanada_op4 = aplanar_lista(op4);
          GList intersecciones = conjunto_inters(aplanada_op3, aplanada_op4);
          Conjunto interseccion = crear_conjunto("carlos",NULL, intersecciones);
          hash_inserto(HASH, "carlos", NULL, intersecciones);
          mostrar_conjunto(interseccion);
        } else {
          printf("\nUno de los operandos no existe...\n");
        }
        interprete = 1;
        break;
      case 5:
          /*
        printf("resta");
        Operandos* operandoResta = sacar_operando_union_inters(operacion);
        printf("\nOPERANDO1.: -%s-\nOPERANDO2.: -%s-\n", operandoResta->aliasOperandoA, operandoResta->aliasOperandoB);//parsea a | b
        Conjunto op5 = hash_busco(HASH, operandoResta->aliasOperandoA);
        Conjunto op6 = hash_busco(HASH, operandoResta->aliasOperandoB);
        */
        printf("resta");
                Conjunto op5 = hash_busco(HASH, "pepe");
        Conjunto op6 = hash_busco(HASH, "papa");
        if(op5 == NULL){printf("\nOP1 NULL\n");}
        if(op6 == NULL){printf("\nOP2 NULL\n");}
        if (op5 != NULL && op6 != NULL) {
          mostrar_conjunto(op5);
          mostrar_conjunto(op6);
          GList restas = definir_conj_dif(op5, op6);
          Conjunto resta = crear_conjunto("carlos", NULL, restas);
          hash_inserto(HASH, "carlos", NULL, restas);
          mostrar_conjunto(resta);
          //freeLista = prepend_glist(freeLista, resta);
        } else {
          printf("\nUno de los operandos no existe...\n");
        }
        interprete = 1;
        break;
      case 6:

        printf("complemento");
          /*
        Operandos* operandoComplemento = sacar_operando_complemento(operacion);
        printf("\nOPERANDO1.: -%s-\nOPERANDO2.: -%s-\n", operandoComplemento->aliasOperandoA, operandoComplemento->aliasOperandoB);//parsea a | b
        Conjunto op7 = hash_busco(HASH, operandoComplemento->aliasOperandoA);
        */


        Conjunto op7 = hash_busco(HASH, "papa");
        if(op7 == NULL){printf("\nOP1 NULL\n");}

        if (op7 != NULL) {
          GList complemetos = initialization_glist();
          complemetos = definir_conj_comple(op7);
          Conjunto complemento = crear_conjunto("carlos", NULL, complemetos);
          hash_inserto(HASH, "carlos", NULL, complemetos);
          mostrar_conjunto(complemento);
          mostrar_conjunto(op7);

          //dlist_destruir_intervalo(complemetos);
       //   freeLista = prepend_glist(freeLista,complemento);
        } else {
          printf("\nUno de los operandos no existe...\n");
        }

        interprete = 1;

        break;

      case 7:
          /*
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
        */
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
  //Conjunto op3 = hash_busco(HASH, "papa");
  //mostrar_conjunto(op3);
  //system("pause");


  free_table(HASH);

//FREE COMPRENSION Y "EXTENSION"
  GList proximo = freeLista;
  GList actual;
  for(; proximo != NULL;){
    actual = proximo;
    proximo = proximo->next;
    Conjunto fr = (Conjunto) actual->data;
    free(fr->lista);
    free(fr->intervaloLista);
    free(fr);
    free(actual);
  }

  /*
  free(testt->intervaloLista);
  free(testt->lista);
  free(testt);
  free(testt2->intervaloLista);
  free(testt2->lista);
  free(testt2);
  */
  //mostrar_conjunto(testt);
  return 0;
}
