#ifndef _FUNCIONES_3_H_
#define _FUNCIONES_3_H_
#include "structures.h"

//FUNCIONES PARA CREAR UNA NUEVA DISCUSIÓN

void crearDiscusion(Usuario *user);
void agregarNuevaDiscusion(Usuario *user, Discusion *disc);
char* eliminarSalto(char* frase);
void insertarDiscusion(Discusion *disc);
int discusionExiste(char* nombre);

#endif //_FUNCIONES_1_H_