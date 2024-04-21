#ifndef APOYO_H_
#define APOYO_H_
#include "structures.h"

char* strreplace(char *o);
char* eliminarSalto(char* frase);
char* obtenerLineaPorNumero(int numeroLinea);
void clearIfNeeded(char *str, int max_line);
#endif