#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include "LSE.h"
typedef struct _Stack {
  GList primero;
}* Stack;

/**
* Inicializamos una nueva pila
*/
Stack stack_new();

/**
* Verificamos que la pila sea vacia
*/
int stack_es_vacio(Stack stack);

/**
* Agregamos un elemento a la pila
*/
void stack_push(Stack stack, void *dato);

/**
* Sacamos el tope de pila
*/
void stack_pop(Stack stack);

/**
* Devolvemos el dato del tope de pila
*/
void* stack_top(Stack stack);

/**
* Destruimos la pila
*/
void stack_destruir(Stack stack);
#endif // PILA_H_INCLUDED
