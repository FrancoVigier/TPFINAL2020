#include "pila.h"

/**
* Inicializamos una nueva pila
*/
Stack stack_new() {
  Stack stack = malloc(sizeof(struct _Stack));
  stack->primero = initialization_glist();
  return stack;
}

/**
* Verificamos que la pila sea vacia
*/
int stack_es_vacio(Stack stack) {
  return stack->primero == NULL;
}

/**
* Agregamos un elemento a la pila
*/
void stack_push(Stack stack, void *dato) {
  stack->primero = prepend_glist(stack->primero, dato);
}

/**
* Sacamos el tope de pila
*/
void stack_pop(Stack stack) {
  stack->primero = glist_eliminar_primero(stack->primero);
}

/**
* Devolvemos el dato del tope de pila
*/
void* stack_top(Stack stack) {
  if (stack_es_vacio(stack))
    return NULL;
  return gnodo_dato(stack->primero);
}

/**
* Destruimos la pila
*/
void stack_destruir(Stack stack) {
  glist_destruir_intervalo(stack->primero);
  free (stack);
}
