#ifndef _CARGARDISCUINES_H_
#define _CARGARDISCUINES_H_
#include "structures.h"
void desplegarDiscusiones(Usuario *user);
Discusion* cargarDiscusion(const char* id);
void cargarSeleccion(char* linea, Usuario *user);
Discusion* leerDiscusiones();
void imprimirComentarios(char* IDConversacion);
#endif