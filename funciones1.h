#ifndef _FUNCIONES_1_H_
#define _FUNCIONES_1_H_
#include "structures.h"

//FUNCIONES PARA INICIAR SESIÓN, REGISTRARSE Y CERRAR SESIÓN
void inicioSesionoRegistro(Usuario *user);
void inicioSesion(Usuario *user);
void clearIfNeeded(char *str, int max_line);
void cerrarSesion(Usuario *user);
void registro(Usuario *user);


#endif //_FUNCIONES_1_H_