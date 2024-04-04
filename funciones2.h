#ifndef _FUNCIONES_2_H_
#define _FUNCIONES_2_H_
#include "structures.h"

//FUNCIONES PARA VER TODAS LAS DISCUSIONES Y AÑADIR COMENTARIOS

void AgregarNuevoComentario(Comentario *coment);
Discusion* leerDiscusiones();
void desplegarDiscusiones(Usuario *user);
void agregarstadistica(Comentario *com);
Discusion* cargarDiscusion(char* id);
int obtenerIdMaximoDiscusiones();
void cargarSeleccion(char* linea, Usuario *user);
void imprimirComentarios(char* IDConversacion);
int maxComentID();

#endif //_FUNCIONES_2_H_