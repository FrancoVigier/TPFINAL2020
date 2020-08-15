#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "LSE.h"

typedef struct _Operandos {
  char* aliasOperandoA;
  char* aliasOperandoB;
} Operandos;


int nombre_de_var_igual_com (char* operacion);
int potencia_de_diez(int largo);
int numero_char_a_int(char* numero);
GList extraer_ext_conjunto(char* operacion, Conjunto conjunto);
char* parsear_comando_y_operacion(char* comando, char* operacion);
int conjunto_un_elem(char* operacion);
int cadena_de_numeros (char* num);
int check_cadena_num_ext(char* operacion);
int cadena_de_numeros_extension (char* num);
int comando_int(char* operacion, char* alias);
Operandos* sacar_operando_union_inters(char* operacion);
Operandos* sacar_operando_complemento(char* operacion);
Operandos* sacar_operando_imprimir(char* alias);

long long potencia_de_diez_long(int largo);
long long numero_char_a_long_long(char* numero);
int validador_limites_int (char* num);

#endif // PARSER_H_INCLUDED
