#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "LSE.h"

typedef struct _Operandos {
  char* aliasOperandoA;
  char* aliasOperandoB;
} Operandos;

int numero_char_a_int(char* numero);
GList extraer_ext_conjunto(char* operacion, Conjunto conjunto);
char* parsear_comando_y_operacion(char* comando, char* operacion);
int conjunto_un_elem(char* operacion);
int comando_int(char* operacion, char* alias);
Operandos* sacar_operando_union_inters(char* operacion);
Operandos* sacar_operando_complemento(char* operacion);
Operandos* sacar_operando_imprimir(char* alias);


#endif // PARSER_H_INCLUDED
