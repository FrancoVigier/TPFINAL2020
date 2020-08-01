#ifndef INTERVALO_H_INCLUDED
#define INTERVALO_H_INCLUDED

typedef struct _Intervalo {
  int inicio;
  int ultimo;
  int esVacio;
  int cardinalidad;
} Intervalo;

Intervalo* extraer_ini_y_fin(char* operacion);

#endif // INTERVALO_H_INCLUDED
