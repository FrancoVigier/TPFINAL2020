#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include "operaciones.h"
#include "pila.h"
#include "conjunto.h"
#include "LSE.h"
#include "intervalo.h"
#include "parser.h"
#include "hash.h"
#define LIMITE 300

int main() {
  int interprete = 0;
  int test = 0;
  struct _GNodo*** HASH;
  HASH = inicializar_HASH();
  GList freeLista = initialization_glist();
  int inicializarUniversal = 0;
  while (interprete == 0) {
    char* alias = malloc(LIMITE * sizeof(char));
    //fgets(alias, LIMITE, stdin);
    if(test == 3){
      strcpy(alias,"imprimir c ");
    }
    if(test == 2){
      strcpy(alias,"c = ~b ");
      test++;
    }
    if(test == 1){
      strcpy(alias,"b = {1,-1,2,-1000,3,-1313,4,-10,5} ");
      test++;
    }
    if(test == 0){
      strcpy(alias,"universal = {} ");
      test++;
    }
    char* operacion = NULL;
    operacion = parsear_comando_y_operacion(alias, operacion);
    int instruccion = comando_int(operacion, alias);
    switch (instruccion) {
      case 1:
        printf("Definicion de un conj. por extension...\n");
        if (strcmp(alias, "universal") != 0){
          Conjunto oper = definir_conj_ext(operacion, alias);
          hash_inserto(HASH, oper->alias, oper->lista, oper->intervaloLista);
          freeLista = prepend_glist(freeLista, oper);
          free (alias);
        }
        else {
          printf("El alias 'universal' es exclusivo de la op. Complemento\n");
          free (alias);
        }
        break;
      case 2:
        printf("Definicion de un conj. por comprension...\n");
        if (strcmp(alias, "universal") != 0){
          Conjunto opeB = definir_conj_com(operacion, alias);
          hash_inserto(HASH, opeB->alias, opeB->lista, opeB->intervaloLista);
          freeLista = prepend_glist(freeLista, opeB);
          free(alias);
        }
        else {
          printf("El alias 'universal' es exclusivo de la op. Complemento\n");
          free (alias);
        }
        break;
      case 3:
        printf("Operacion de Union de conjuntos...\n");
        if (strcmp(alias, "universal") != 0){
          Operandos* opeUnion = sacar_operando_union_inters(operacion);
          Conjunto op1 = hash_busco(HASH, opeUnion->aliasOperandoA);
          Conjunto op2 = hash_busco(HASH, opeUnion->aliasOperandoB);
          if (op1 != NULL && op2 != NULL) {
            GList resultado = definir_conj_union(op1, op2);
            Conjunto uniones = crear_conjunto(alias, NULL, resultado);
            hash_inserto(HASH, alias, NULL, resultado);
            freeLista = prepend_glist(freeLista, uniones);
            glist_destruir_int(resultado);
          }
          else {
            printf("Uno de los operandos no existe...\n");
            if (op1 == NULL) {
              printf("%s NO EXISTE COMO OPERANDO\n", opeUnion->aliasOperandoA);
            }
            if (op2 == NULL) {
              printf("%s NO EXISTE COMO OPERANDO\n", opeUnion->aliasOperandoB);
            }
          }
          free(alias);
          free(opeUnion);
        }
        else {
          printf("El alias 'universal' es exclusivo de la op. Complemento\n");
          free (alias);
        }
        break;
      case 4:
        printf("Operacion de Interseccion de conjuntos...\n");
        if (strcmp(alias, "universal") != 0){
          Operandos* opeInter = sacar_operando_union_inters(operacion);
          Conjunto op3 = hash_busco(HASH, opeInter->aliasOperandoA);
          Conjunto op4 = hash_busco(HASH, opeInter->aliasOperandoB);
          if (op3 != NULL && op4 != NULL) {
            GList intersecciones = conjunto_inters(op3, op4);
            Conjunto interseccion = crear_conjunto(alias, NULL, intersecciones);
            hash_inserto(HASH, alias, NULL, intersecciones);
            freeLista = prepend_glist(freeLista, interseccion);
            glist_destruir_int(intersecciones);
          }
          else {
            printf("Uno de los operandos no existe...\n");
            if (op3 == NULL) {
              printf("%s NO EXISTE COMO OPERANDO\n", opeInter->aliasOperandoA);
            }
            if (op4 == NULL) {
              printf("%s NO EXISTE COMO OPERANDO\n", opeInter->aliasOperandoB);
            }
          }
          free(alias);
          free(opeInter);
        }
        else {
          printf("El alias 'universal' es exclusivo de la op. Complemento\n");
          free (alias);
        }
        break;
      case 5:
        printf("Operacion de Resta de conjuntos...\n");
        if (strcmp(alias, "universal") != 0){
          Operandos* opeResta = sacar_operando_union_inters(operacion);
          Conjunto op5 = hash_busco(HASH, opeResta->aliasOperandoA);
          Conjunto op6 = hash_busco(HASH, opeResta->aliasOperandoB);
          if (op5 != NULL && op6 != NULL) {
            GList restas = definir_conj_dif_dos(op5, op6);
            Conjunto resta = crear_conjunto(alias, NULL, restas);
            hash_inserto(HASH, alias, NULL, restas);
            freeLista = prepend_glist(freeLista, resta);
            glist_destruir_int(restas);
          }
          else {
            printf("Uno de los operandos no existe...\n");
            if (op5 == NULL) {
              printf("%s NO EXISTE COMO OPERANDO\n", opeResta->aliasOperandoA);
            }
            if (op6 == NULL) {
              printf("%s NO EXISTE COMO OPERANDO\n", opeResta->aliasOperandoB);
            }
          }
          free (alias);
          free (opeResta);
        }
        else {
          printf("El alias 'universal' es exclusivo de la op. Complemento\n");
          free (alias);
        }
        break;
      case 6:
        printf("Operacion Complemento de un conjunto...\n");
        if (strcmp(alias, "universal") != 0){
          Operandos* opeComp = sacar_operando_complemento(operacion);
          if (inicializarUniversal == 0) {
            char aliasa[] = "universal";
            char operacione[] = " {x : -2147483648 <= x <= 2147483647}";
            Conjunto uni = definir_conj_com(operacione, aliasa);
            hash_inserto(HASH, uni->alias, uni->lista, uni->intervaloLista);
            freeLista = prepend_glist(freeLista, uni);
            inicializarUniversal = 1;
          }
          Conjunto op8 = hash_busco(HASH, "universal");
          Conjunto op7 = hash_busco(HASH, opeComp->aliasOperandoA);
          if (op7 != NULL) {
            GList complemetos = definir_conj_dif_dos(op8, op7);
            Conjunto complemento = crear_conjunto(alias, NULL, complemetos);
            hash_inserto(HASH, alias, NULL, complemetos);
            freeLista = prepend_glist(freeLista, complemento);
            glist_destruir_int(complemetos);
          }
          else {
            printf("Uno de los operandos no existe...\n");
            if (op7 == NULL) {
              printf("%s NO EXISTE COMO OPERANDO\n", opeComp->aliasOperandoA);
            }
          }
          free(alias);
          free(opeComp);
        }
        else {
          printf("El alias 'universal' es invariante no se puede pisar\n");
          free (alias);
        }
        break;
      case 7:
        printf("Imprimiendo conjunto...\n");
        Operandos* opeImp = sacar_operando_imprimir(alias);
        Conjunto op9 = hash_busco(HASH, opeImp->aliasOperandoA);
        if (op9 != NULL) {
          mostrar_conjunto_imprimir(op9);
        }
        else {
          printf("El operando %s no existe...\n", opeImp->aliasOperandoA);
        }
        free (alias);
        free (opeImp);
        interprete = 1;
        break;
      case 8:
        printf("Saliendo del programa...\n");
        free (alias);
        interprete = 1;
        break;
      case 9:
        printf("ERROR DE SINTAXIS\n");
        free (alias);
        break;
    }
  }
  free_table(HASH);
//FREE COMPRENSION Y "EXTENSION" ESQUELETO
  GList proximo = freeLista;
  GList actual;
  for (; proximo != NULL;) {
    actual = proximo;
    proximo = proximo->next;
    Conjunto fr = (Conjunto)actual->data;
    free (fr->alias);
    glist_destruir_int(fr->lista);
    glist_destruir_int(fr->intervaloLista);
    free (fr);
    free (actual);
  }
  return 0;
}
