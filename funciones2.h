#ifndef _FUNCIONES_2_H_
#define _FUNCIONES_2_H_
#include "structures.h"

//FUNCIONES PARA VER TODAS LAS DISCUSIONES Y AÑADIR COMENTARIOS

Comentario comentar(Usuario *user, Discusion *disc, Comentario *respuesta);
void AgregarNuevoComentario(Comentario *coment);
Discusion* leerDiscusiones();
void desplegarDiscusiones(Usuario *user);
#endif //_FUNCIONES_2_H_