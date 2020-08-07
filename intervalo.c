#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "intervalo.h"
#include "parser.h"
Intervalo* extraer_ini_y_fin(char* operacion) {
  char separadorInicial[] = " ";
  char *fraccion = strtok(operacion, separadorInicial);
  char *inicio;
  char *fin;
  int contador = 0;
  if (fraccion != NULL) {
    while (fraccion != NULL) {
      if (contador == 2)
        inicio = fraccion;
      if (contador == 6)
        fin = fraccion;
    fraccion = strtok(NULL, separadorInicial);
    contador++;
    }
  }
  printf("INICIO: -%s-\nFIN: -%s-", inicio, fin);
  fin[strlen(fin) - 1] = '\0';
  int init = numero_char_a_int(inicio);
  int fina = numero_char_a_int(fin);
  if (fina < init) {
    return NULL;
  }
  //  intervalo->inicio = init;
  //  intervalo->ultimo = fina;
  //    intervalo->esVacio = 1;
  //  intervalo->cardinalidad = 0;
  Intervalo* intervalo = malloc(sizeof(struct _Intervalo));

    intervalo->inicio = init;
    intervalo->ultimo = fina;
    intervalo->esVacio = 0;
    intervalo->cardinalidad = 0;  
  
  printf("INICIO: -%i-\nFIN: -%i-", init, fina);
  if (intervalo->esVacio == 0 && intervalo->inicio >= 0 && intervalo->ultimo >= 0) {
    intervalo->cardinalidad = intervalo->ultimo - intervalo->inicio;
    intervalo->cardinalidad++;
  }
  if (intervalo->esVacio == 0 && intervalo->inicio < 0 && intervalo->ultimo < 0) {
    intervalo->cardinalidad = abs(intervalo->inicio - intervalo->ultimo);
    intervalo->cardinalidad++;
  }
  if (intervalo->esVacio == 0 && intervalo->inicio < 0 && intervalo->ultimo > 0) {
    intervalo->cardinalidad = intervalo->ultimo - intervalo->inicio;
    intervalo->cardinalidad++;
  }
  return intervalo;
}

