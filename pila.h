#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include "LSE.h"
typedef struct _Stack {
  GList primero;
}* Stack;

Stack stack_new();
int stack_es_vacio(Stack stack);
void stack_push(Stack stack, void *dato);
void stack_pop(Stack stack);
void* stack_top(Stack stack);
void stack_destruir(Stack stack);
#endif // PILA_H_INCLUDED
