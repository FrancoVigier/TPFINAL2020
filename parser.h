#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#define LIMITE 300
#include "LSE.h"

typedef struct _Operandos {
  char* aliasOperandoA;
  char* aliasOperandoB;
} Operandos;

/**
* Verificador de errores en la declaracion por comprension
* de un conjunto
*/
int nombre_de_var_igual_com (char* operacion);

/**
* Extraemos los numeros presentes en la def. por extension
*/
GList extraer_ext_conjunto(char* operacion, Conjunto conjunto);

/**
* Extraigo el alias y operacion en el formato 'alias = operacion'
*/
char* parsear_comando_y_operacion(char* comando, char* operacion);

/**
* Verifico si se trata de una declaracion alias = {x}
*/
int conjunto_un_elem(char* operacion);

/**
* Verificador que si una cadera de caracteres
* solo se compone de digitos
*/
int cadena_de_numeros (char* num);

/**
* Verificador de que si la declaracion por extensio de
* un conjunto sus elementos son cadenas de digitos y
* los numeros que estas representan estan dentro de los limites
*/
int check_cadena_num_ext(char* operacion);

/**
* Verificador de errores en la declaracion por extension
* de un conjunto
*/
int cadena_de_numeros_extension (char* num);

/**
* Dado un input del tipo 'alias = operacion' nos
* dirige a una operacion entre las definidas
*/
int comando_int(char* operacion, char* alias);

/**
* Extraemos los operandos de las operaciones del tipo
* 'alias = aliasA cadena aliasB'
*/
Operandos* sacar_operando_union_inters(char* operacion);

/**
* Extraemos el operando de la op. Complemento
*/
Operandos* sacar_operando_complemento(char* operacion);

/**
* Extraemos el operando de la directiva Imprimir
*/
Operandos* sacar_operando_imprimir(char* alias);

/**
* Conseguimos potencias de 10
*/
long long potencia_de_diez_long(int largo);

/**
* Transformamos una cadena a numero
*/
long long numero_char_a_long_long(char* numero);

/**
* Chequeo que una cadena que representa un numero
* este entre los limites de la variable int
*/
int validador_limites_int (char* num);

#endif // PARSER_H_INCLUDED
