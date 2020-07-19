#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "parser.h"

int numero_char_a_int(char* numero) {
  int indice = 0;
  int largo = strlen(numero);
  int cifra = 0;
  int decimal;
  int negativo = 0;
  if (numero[0] == '-') {
    negativo = 1;
    indice = 1;
    largo--;
  }
  while (numero[indice] != '\0') {
    decimal = numero[indice] - '0';
    cifra += decimal * pow(10, --largo);
    indice++;
  }
  if (negativo == 1) {
    cifra = cifra * -1;
  }
  return cifra;
}

GList extraer_ext_conjunto(char* operacion, Conjunto conjunto) {
  operacion[strlen(operacion) - 1] = ','; //si voy a leer entrecomas para el caso {x} no sirve pero si altero y es {x, si sirve
  char separadorInicial[] = "{";
  char* buffer = operacion;
  char* fraccion = strtok(buffer,separadorInicial);
  char* numeros;
  if (fraccion != NULL) {
    while (fraccion != NULL) {
      numeros = fraccion;
      fraccion = strtok(NULL, separadorInicial);
    }
  }//printf("%s\n",numeros);//10,0,6,4,3... pero char*
  separadorInicial[0] = ',';
  fraccion = strtok(numeros, separadorInicial);
  if (fraccion != NULL) { //fraccion = "10" i.e
    while (fraccion != NULL) {// Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
      int numConjunto =  numero_char_a_int(fraccion);
      int* numConj = (int*)numConjunto;
      conjunto->lista = prepend_glist(conjunto->lista, numConj);
      fraccion = strtok(NULL, separadorInicial);
    }
  }
  return conjunto->lista;
}

char* parsear_comando_y_operacion(char* comando, char* operacion) {
  char separador[] = "=";
  char *fraccion = strtok(comando, separador);
  int diferencia = 0;
  char separadorDiferencial[] = "\0";
  if (fraccion != NULL) {
    while (fraccion != NULL) {// Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
      fraccion[strlen(fraccion) - 1] = '\0';
      if (diferencia == 0) {
        comando = fraccion;
      } else {
        operacion = fraccion;
        printf("OPERACION ITE: -%s-", operacion);
      }
      fraccion = strtok(NULL, separadorDiferencial);
      diferencia++;
    }
  }
  return operacion;
}

int conjunto_un_elem(char* operacion) {
  int indice = 2;
  if (operacion[indice] == '-') {
    indice++;
  }
  printf("OPEEEER: %s", operacion);
  for (; operacion[indice] != '\0' && operacion[indice] != '}'; indice++) {//avanzo hasta
    if (!isdigit(operacion[indice]))
      return 1;//1 no es un num
    printf("ERRRRRO");
  }
  return 0; //0 es un num
}

int comando_int(char* operacion, char* alias) { //1-> creacion extension 2->creacion comprension 3->union 4->interseccion 5->resta 6->complemento 7->imprimir 8->salir
  if (strstr(alias, "imprimir "))
    return 7;
  if (strstr(operacion, ",") || operacion == " {}" || conjunto_un_elem(operacion) == 0) {
    printf("hola");
    if (strstr(operacion, ","))
      printf("es el 1\n");
    if (operacion == " {}")
      printf("es el 2\n oper: %s\n", operacion);
    if (conjunto_un_elem(operacion) == 0)
      printf("es el 3\n");
    return 1;
  }
  if (strstr(operacion, ":"))
    return 2;
  if (strstr(operacion, " | "))
    return 3;
  if (strstr(operacion, " & "))
    return 4;
  if (strstr(operacion, " - "))
    return 5;
  if (strstr(operacion, "~"))
    return 6;
  if (strstr(alias, "salir"))
    return 8;
  return 9;
}

Operandos* sacar_operando_union_inters(char* operacion) {
  char separadorInicial[] = " ";
  char *fraccion = strtok(operacion, separadorInicial);
  char *inicio;
  char *fin;
  int contador = 0;
  if (fraccion != NULL) {
    while (fraccion != NULL) {
      if (contador == 0)
        inicio = fraccion;
      if (contador == 2)
        fin = fraccion;
      fraccion = strtok(NULL, separadorInicial);
      contador++;
    }
  }//printf("UNION E INTER\nCONJ1.: -%s-\nCONJ2.: -%s-\n",inicio,fin);
  Operandos* operandos = malloc(sizeof(struct _Operandos));
  operandos->aliasOperandoA = inicio;
  operandos->aliasOperandoB = fin;
  return operandos;
}

Operandos* sacar_operando_complemento(char* operacion) {
  char separadorInicial[] = "~";
  char *fraccion = strtok(operacion, separadorInicial);
  char *inicio;
  char *fin = NULL;
  int contador = 0;
  if (fraccion != NULL) {
    while (fraccion != NULL) {
      if (contador == 1)
        inicio = fraccion;
      fraccion = strtok(NULL, separadorInicial);
      contador++;
    }
  }// printf("UNION E INTER\nCONJ1.: -%s-\nCONJ2.: -%s-\n",inicio,fin);
  Operandos* operandos = malloc(sizeof(struct _Operandos));
  operandos->aliasOperandoA = inicio;
  operandos->aliasOperandoB = fin;
  return operandos;
}

Operandos* sacar_operando_imprimir(char* alias) {
  char separadorInicial[] = " ";
  char *fraccion = strtok(alias, separadorInicial);
  char *inicio;
  char *fin = NULL;
  int contador = 0;
  if (fraccion != NULL) {
    while (fraccion != NULL) {
      if (contador == 1)
        inicio = fraccion;
      fraccion = strtok(NULL, separadorInicial);
      contador++;
    }
  }// printf("UNION E INTER\nCONJ1.: -%s-\nCONJ2.: -%s-\n",inicio,fin);
  Operandos* operandos = malloc(sizeof(struct _Operandos));
  operandos->aliasOperandoA = inicio;
  operandos->aliasOperandoB = fin;
  return operandos;
}
