#ifndef _CREARDISCUSIONES_H_
#define _CREARDISCUSIONES_H__H_
#include "structures.h"
#include <winsock2.h>

void crearDiscusion(Usuario *user);
void agregarNuevaDiscusion(Usuario *user, Discusion *disc);
void insertarDiscusion(Discusion *disc);
int discusionExiste(const char* nombre);
int obtenerIdMaximoDiscusiones();

#endif //_CREARDISCUSIONES_H_