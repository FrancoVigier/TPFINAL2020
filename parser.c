#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "parser.h"
#include <limits.h>

#define LIMITE 300

long long potencia_de_diez_long(int largo){
long long potencia = 1;

while(largo > 0){
 potencia = 10 * potencia;
 largo--;
}
return potencia;
}

long long numero_char_a_long_long(char* numero) {
  int indice = 0;
  int largo = strlen(numero);
  long long cifra = 0;
  int decimal;
  int negativo = 0;
  if (numero[0] == '-') {
    negativo = 1;
    indice = 1;
    largo--;
  }
 // printf("\nEL LARGO ES:\n%i", largo);
  int buff = largo;
  while (numero[indice] != '\0') {
    decimal = numero[indice] - '0';
   // printf("\nLA DECIMA CONFORMADA ES:\n%i", decimal);
   // printf("\nLA DECIMA SE MULTIPLICA POR:\n%i", potencia_de_diez(--buff));
    cifra += decimal * potencia_de_diez_long(--largo);
  //  printf("\nLA CIFRA PARCIAL CONFORMADA ES:\n%i", cifra);
    indice++;
  }

  if (negativo == 1) {
    cifra = cifra * -1;
  }

  printf("\nLA CIFRA CONFORMADA LONG LONG ES:\n%lld", cifra);

  return cifra;
}


int potencia_de_diez(int largo){
int potencia = 1;

while(largo > 0){
 potencia = 10 * potencia;
 largo--;
}
return potencia;
}

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
 // printf("\nEL LARGO ES:\n%i", largo);
  int buff = largo;
  while (numero[indice] != '\0') {
    decimal = numero[indice] - '0';
   // printf("\nLA DECIMA CONFORMADA ES:\n%i", decimal);
   // printf("\nLA DECIMA SE MULTIPLICA POR:\n%i", potencia_de_diez(--buff));
    cifra += decimal * potencia_de_diez(--largo);
  //  printf("\nLA CIFRA PARCIAL CONFORMADA ES:\n%i", cifra);
    indice++;
  }

  if (negativo == 1) {
    cifra = cifra * -1;
  }

  printf("\nLA CIFRA CONFORMADA ES:\n%i", cifra);

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
    while (fraccion != NULL) {// S�lo en la primera pasamos la cadena; en las siguientes pasamos NULL
      long long numConjunto =  numero_char_a_long_long(fraccion);
      conjunto->lista = prepend_glist(conjunto->lista, (long long*)numConjunto);
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
    while (fraccion != NULL) {// S�lo en la primera pasamos la cadena; en las siguientes pasamos NULL
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

int validador_limites_int (char* num){
  long long numero = numero_char_a_long_long(num);
  if(numero > INT_MAX || numero < INT_MIN){
    return 1;
  }
  return 0;
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

int cadena_de_numeros (char* num){
  char letra;
  int i = 0;

  if(strcmp(num, "") == 0){ // ""
    return 1;
  }

  if(num[i] == '-' && strlen(num) > 1){ //-
    i++;
  }
  else {
    if(num[i] == '-' && strlen(num) == 1){
      return 1;
    }
  }

  for (; num[i] != '\0'; i++){
    letra = num[i];
    if( letra != '0' && letra != '1' && letra != '2' && letra != '3' && letra != '4' && letra != '5' && letra != '6' && letra != '7' && letra != '8' && letra != '9'){
      return 1;
    }
  }
  return 0;
}

int check_cadena_num_ext(char* operacion) {
  operacion[strlen(operacion) - 1] = ','; //si voy a leer entrecomas para el caso {x} no sirve pero si altero y es {x, si sirve
  char separadorInicial[] = "{";
  char* buffer = operacion;
  char* fraccion = strtok(buffer,separadorInicial);
  char* numeros;
  int cdn = 0;
  int vli = 0;
  if (fraccion != NULL) {
    while (fraccion != NULL) {
      numeros = fraccion;
      fraccion = strtok(NULL, separadorInicial);
    }
  }//printf("%s\n",numeros);//10,0,6,4,3... pero char*
  separadorInicial[0] = ',';
  fraccion = strtok(numeros, separadorInicial);
  if (fraccion != NULL) { //fraccion = "10" i.e
    while (fraccion != NULL) {// S�lo en la primera pasamos la cadena; en las siguientes pasamos NULL
      if(cadena_de_numeros(fraccion) == 1){
        cdn = 1;
      }
      if(validador_limites_int(fraccion) == 1){
        vli = 1;
      }
      fraccion = strtok(NULL, separadorInicial);
    }
  }
  if(cdn == 1 && vli == 1){
    printf("Error del tipo {x1,'x',...,xn}, con x distinto a un numero entero\n");
    printf("Error del tipo {x1,'x',...,xn}, con x fuera de rango INT\n");
    return 3;
  }
  if(cdn == 1 && vli == 0){
    printf("Error del tipo {x1,'x',...,xn}, con x distinto a un numero entero\n");
    return 1;
  }
  if(cdn == 0 && vli == 1){
    printf("Error del tipo {x1,'x',...,xn}, con x fuera de rango INT\n");
    return 2;
  }

  if(cdn == 0 && vli == 0){
  return 0;
  }
}


int cadena_de_numeros_extension (char* num){
  char letra;
  int ok = 0;

  if(strcmp(num, " {}") == 0){
    return ok;
  }

  if(num[0] != ' '){
    printf("Error del tipo 'a'{x1,x2,...,xn}, con a distinto a ' '\n");
    ok = 1;
  }
  if(num[1] != '{'){
    printf("Error del tipo 'l'x1,x2,...,xn}, con l distinto a '{'\n");
    ok = 1;
  }
  if(num[strlen(num)-1] != '}'){
    printf("Error del tipo {x1,x2,...,xn'l', con l distinto a '}'\n");
    ok = 1;
  }

  char* buffer = malloc(sizeof(char)* LIMITE);
  strcpy(buffer, num);

  if(check_cadena_num_ext(buffer) != 0 ){
    ok = 1;
  }

  free(buffer);

  return ok;

}


int nombre_de_var_igual_com (char* operacion){//free aliasA aliasB
  char separador[] = " ";

  int ok = 0; //0 es ok

  if(operacion[1] != '{'){
    printf("Error de sintaxis en la primera llave de definicion '{'alias : x1 <= alias <= x2}\n");
    ok = 1;
    }

  if (operacion[strlen(operacion) - 1] != '}'){
    printf("Error de sintaxis en la segunda llave de definicion {alias : x1 <= alias <= x2'}'\n");
    ok = 1;
  }

  char *fraccion = strtok(operacion, separador);
  char* aliasA = malloc(sizeof(char)*20);
  char* aliasB = malloc(sizeof(char)*20);

  char* numeroA = malloc(sizeof(char)*20);
  char* numeroB = malloc(sizeof(char)*20);

  char* signoA = malloc(sizeof(char)*20);
  char* signoB = malloc(sizeof(char)*20);

  char* operador = malloc(sizeof(char)*20);

  int diferencia = 0;
  printf("STAGE1 INTERNO\n");
  if (fraccion != NULL) {
    while (fraccion != NULL) {// S�lo en la primera pasamos la cadena; en las siguientes pasamos NULL
      fraccion[strlen(fraccion)] = '\0';
      if (diferencia == 0) { // "{alias"
        strcpy(aliasA,fraccion);
      }

      if (diferencia == 1){ // ":"
        strcpy(operador, fraccion);
      }

      if (diferencia == 2){ // "x1"
        strcpy(numeroA, fraccion);
        printf("\nX1 : -%s-\n", numeroA);
      }

      if (diferencia == 3){ // "<="
        strcpy(signoA, fraccion);
      }

      if (diferencia == 4){// "alias"
        strcpy(aliasB,fraccion);
      }

      if (diferencia == 5){ // "<="
        strcpy(signoB, fraccion);
      }

      if (diferencia == 6){ // "x2}"
        strcpy(numeroB, fraccion);
        numeroB[strlen(numeroB) - 1] = '\0';
        printf("\nX2: -%s-\n", numeroB);

      }

      fraccion = strtok(NULL, separador);
      diferencia++;
    }
  }
  printf("\nLOS 'ALIAS' DE LA DEFINICION POR COMPRENSION SON: -%s- -%s-\n", aliasA,aliasB);
  aliasA++;//"{x"
  printf("\nLOS 'ALIAS' DE LA DEFINICION POR COMPRENSION SON: -%s- -%s-\n", aliasA,aliasB);
  if(strcmp(aliasA,aliasB) != 0){
    printf("Error de sintaxis del tipo {'alias1' : x1 <= 'alias2' <= x2}\n");
    ok = 1;
  }

  if(strcmp(operador, ":") != 0){
    printf("Error de sintaxis del tipo {alias 'x' x1 <= alias <= x2} con x distinto a ':'\n");
    ok = 1;
  }

  if (strcmp(signoA, "<=") != 0 || strcmp(signoB, "<=") != 0){
    printf("Error de sintaxis del tipo {alias : x1 'x' alias 'y' x2} con x e y distinto a '<='\n");
    ok = 1;
  }


  if( cadena_de_numeros(numeroA) == 1 || cadena_de_numeros(numeroB) == 1){
    printf("Error de sintaxis del tipo {alias : 'x' <= alias <= 'y'} con x e y no n�meros enteros\n");
    ok = 1;
  }

  if(validador_limites_int(numeroA) == 1){
    printf("Error de sintaxis del tipo {alias : 'x' <= alias <= y} con x fuera de rango INT\n");
    ok = 1;
  }
  if(validador_limites_int(numeroB) == 1){
    printf("Error de sintaxis del tipo {alias : x <= alias <= 'y'} con y fuera de rango INT\n");
    ok = 1;
  }

  free(aliasA);
  free(aliasB);
  free(numeroA);
  free(numeroB);
  free(signoA);
  free(signoB);
  free(operador);

  return ok;
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
    if(strcmp(operacion, "") != 0 && cadena_de_numeros_extension(operacion) == 0){
    return 1;
    }
    else{
      return 9;
    }
  }
  if (strstr(operacion, " : ")){////// free ope
    printf("STAGE1\n");
    char* ope = malloc(sizeof(char) * LIMITE);
    printf("STAGE2\n");
    strcpy(ope, operacion);
    printf("STAGE3\n");
    if (nombre_de_var_igual_com(ope) == 0){ //test
      printf("STAGE4");
      free(ope);
      return 2;
   } else {
        free(ope);
        return 9;
     }
  }
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
