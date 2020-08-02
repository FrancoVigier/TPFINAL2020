#ifndef CONJUNTO_H_INCLUDED
#define CONJUNTO_H_INCLUDED
#include "LSE.h"
/*
typedef struct _Conjunto {
  char* alias;
  int comprenExtens; // 1->{10,1,2} 2->{x | x<4} //2 ocurrencias
  GList lista;
  int abiertoCerrado; // 1->[] 2->() 3->[) 4->(] //2 ocurrencias
  GList intervaloLista;
  int extInferior; //2 ocurrencias
  int extSuperior; // ocurrencias
  int vacio;
}* Conjunto;
*/

Conjunto inicializar_conjunto(char* alias, char* operacion);
Conjunto crear_conjunto(char* alias, GList lista, GList intervaloLista);
void extraer_com_conjunto(char* operacion, Conjunto conjunto);
Conjunto definir_conj_com(char* operacion, char* alias);
Conjunto definir_conj_ext(char* operacion, char* alias);
void mostrar_conjunto(Conjunto muestro);
void mostrar_conjunto_imprimir(Conjunto muestro);
void destruir_conjunto(Conjunto conjunto, void* aux);
#endif // CONJUNTO_H_INCLUDED
