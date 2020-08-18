#ifndef INTERVALO_H_INCLUDED
#define INTERVALO_H_INCLUDED

#include "parser.h"
#define LIMITE 300

typedef struct _Intervalo {
  long long inicio;
  long long ultimo;
  int esVacio;
  long long cardinalidad;
} Intervalo;

/**
* Extraemos los intervalos inf y sup de la def. por comprension
*/
Intervalo* extraer_ini_y_fin(char* operacion);

#endif // INTERVALO_H_INCLUDED
