#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "intervalo.h"

/**
* Extraemos los intervalos inf y sup de la def. por comprension
*/
Intervalo* extraer_ini_y_fin(char* operacionA) {
  char* operacion = malloc(sizeof(char) * LIMITE);
  strcpy(operacion,operacionA);
  char separadorInicial[] = " ";
  //Dividimos la cadena por espacios en blanco
  char *fraccion = strtok(operacion, separadorInicial);
  char *inicio = NULL;
  char *fin = NULL;
  int contador = 0;
  if (fraccion != NULL) {
    while (fraccion != NULL) {
  //Obtengo las cadenas que representan los extremos
      if (contador == 2)
        inicio = fraccion;
      if (contador == 6)
        fin = fraccion;
    fraccion = strtok(NULL, separadorInicial);
    contador++;
    }
  }
  fin[strlen(fin) - 1] = '\0';
  //Convierto las cadenas a numeros
  long long init = numero_char_a_long_long(inicio);
  long long fina = numero_char_a_long_long(fin);
  //Chekeo si el conjunto declarado es vacio o no
  if (fina < init) {
    free(operacion);
    return NULL;
  }

  Intervalo* intervalo = malloc(sizeof(struct _Intervalo));
  intervalo->inicio = init;
  intervalo->ultimo = fina;
  intervalo->esVacio = 0;
  intervalo->cardinalidad = 0;
  //Calculo la cardinalidad del intervalo declarado
  if (intervalo->esVacio == 0 && intervalo->inicio >= 0 &&
      intervalo->ultimo >= 0) {
    intervalo->cardinalidad = intervalo->ultimo - intervalo->inicio;
    intervalo->cardinalidad++;
  }
  if (intervalo->esVacio == 0 && intervalo->inicio < 0 &&
      intervalo->ultimo < 0) {
    intervalo->cardinalidad = abs(intervalo->inicio - intervalo->ultimo);
    intervalo->cardinalidad++;
  }
  if (intervalo->esVacio == 0 && intervalo->inicio < 0 &&
      intervalo->ultimo > 0) {
    intervalo->cardinalidad = intervalo->ultimo - intervalo->inicio;
    intervalo->cardinalidad++;
  }
  free (operacion);
  return intervalo;
}
