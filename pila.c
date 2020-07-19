#include "pila.h"

Stack stack_new() {
  Stack stack = malloc(sizeof(struct _Stack));
  stack->primero = initialization_glist();
  return stack;
}

int stack_es_vacio(Stack stack) {
  return stack->primero == NULL;
}

void stack_push(Stack stack, void *dato) {
  stack->primero = prepend_glist(stack->primero, dato);
}
void stack_pop(Stack stack) {
  stack->primero = dlist_eliminar_primero(stack->primero);
}

void* stack_top(Stack stack) {
  if (stack_es_vacio(stack))
    return NULL;
  return dnodo_dato(stack->primero);
}
