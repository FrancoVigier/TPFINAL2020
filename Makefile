  
CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99

.PHONY: default_target all clean

default_target: Interprete
all: default_target

OBJECTS_LSE = $(patsubst %.c, compilados/.obj/%.o, $(wildcard LSE/*.c))
HEADERS_LSE = $(wildcard LSE/*.h)

OBJECTS_CONJUNTO = $(patsubst %.c, compilados/.obj/%.o, $(wildcard conjunto/*.c))
HEADERS_CONJUNTO = $(wildcard conjunto/*.h)

OBJECTS_HASH = $(patsubst %.c, compilados/.obj/%.o, $(wildcard hash/*.c))
HEADERS_HASH = $(wildcard hash/*.h)

OBJECTS_INTERVALO = $(patsubst %.c, compilados/.obj/%.o, $(wildcard intervalo/*.c))
HEADERS_INTERVALO = $(wildcard intervalo/*.h)

OBJECTS_PARSER = $(patsubst %.c, compilados/.obj/%.o, $(wildcard parser/*.c))
HEADERS_PARSER = $(wildcard parser/*.h)

OBJECTS_PILA = $(patsubst %.c, compilados/.obj/%.o, $(wildcard pila/*.c))
HEADERS_PILA = $(wildcard pila/*.h)

OBJECTS_INTERPRETE = $(patsubst %.c, compilados/.obj/%.o, $(wildcard *.c))
HEADERS_INTERPRETE = $(wildcard *.h)

compilados/.obj/%.o: %.c $(HEADERS_LSE) $(HEADERS_CONJUNTO) $(HEADERS_HASH) $(HEADERS_INTERVALO) $(HEADERS_PARSER) $(HEADERS_PILA) $(HEADERS_INTERPRETE)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: Interprete $(OBJECTS_LSE) $(OBJECTS_CONJUNTO) $(OBJECTS_HASH) $(OBJECTS_INTERVALO) $(OBJECTS_PARSER) $(OBJECTS_PILA) $(OBJECTS_INTERPRETE)

Interprete: compilados compilados/.obj compilados/.obj/LSE compilados/.obj/conjunto compilados/.obj/hash compilados/.obj/intervalo compilados/.obj/parser compilados/.obj/pila $(OBJECTS_LSE) $(OBJECTS_CONJUNTO) $(OBJECTS_HASH) $(OBJECTS_INTERVALO) $(OBJECTS_PARSER) $(OBJECTS_PILA) $(OBJECTS_INTERPRETE)
	$(CC) $(OBJECTS_LSE) $(OBJECTS_CONJUNTO) $(OBJECTS_HASH) $(OBJECTS_INTERVALO) $(OBJECTS_PARSER) $(OBJECTS_PILA) $(OBJECTS_INTERPRETE) $(CFLAGS) -o compilados/$@

compilados:
	mkdir -p $@

compilados/.obj/LSE:
	mkdir -p $@

compilados/.obj/conjunto:
	mkdir -p $@

compilados/.obj/hash:
	mkdir -p $@
	
compilados/.obj/intervalo:
	mkdir -p $@

compilados/.obj/parser:
	mkdir -p $@
	
compilados/.obj/pila:
	mkdir -p $@	

compilados/.obj:
	mkdir -p $@

clean:
	-rm -rf compilados
