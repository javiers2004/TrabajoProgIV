#ifndef _CREARDISCUSIONES_H_
#define _CREARDISCUSIONES_H__H_
#include "structures.h"
#include <winsock2.h>

void crearDiscusion(Usuario *user, char* nombreCreador);
void agregarNuevaDiscusion(Usuario *user, Discusion *disc, char* nombreCreador);
void insertarDiscusion(char* nombreDiscusion, char* nombreCreador);
int discusionExiste(const char* nombre);
int obtenerIdMaximoDiscusiones();

#endif //_CREARDISCUSIONES_H_