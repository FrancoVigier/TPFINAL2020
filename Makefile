all: main

main: main.c LSE.o conjunto.o hash.o intervalo.o pila.o parser.o
	gcc  -std=c99 -o main main.c LSE.o conjunto.o hash.o intervalo.o pila.o parser.o -lm

hash.o: hash.c hash.h LSE.o conjunto.o
	gcc -c -Wall -Wextra -Werror -std=c99 hash.c

pila.o: pila.c pila.h LSE.o
  gcc -c -Wall -Wextra -Werror -std=c99 pila.c
parser.o: parser.c parser.h LSE.o
  gcc -c -Wall -Wextra -Werror -std=c99 parser.c 

LSE.o: LSE.c LSE.h conjunto.o intervalo.o
  gcc -c -Wall -Wextra -Werror -std=c99 LSE.c
  
conjunto.o: conjunto.c conjunto.h intervalo.o parser.o
  gcc -c -Wall -Wextra -Werror -std=c99 conjunto.c

intervalo.o: intervalo.c intervalo.h parser.o
  gcc -c -Wall -Wextra -Werror -std=c99 intervalo.c
  
clean:
	rm -f *.o main main.exe
