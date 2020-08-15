#ifndef INTERVALO_H_INCLUDED
#define INTERVALO_H_INCLUDED

typedef struct _Intervalo {
  long long inicio;
  long long ultimo;
  int esVacio;
  long long cardinalidad;
} Intervalo;

Intervalo* extraer_ini_y_fin(char* operacion);

#endif // INTERVALO_H_INCLUDED
