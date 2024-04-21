#ifndef _INICIOSESION_H_
#define  _INICIOSESION_H_
#include "structures.h"

void inicioSesion(Usuario *user);
void cerrarSesion(Usuario *user);
Usuario* leerUsuario(const char* nombre);
int nombreExiste(const char *nombre);
int verificarCredenciales(const char *nombre, const char *contrasena);
void contrasenaRecursiva(Usuario *user, int intentos, char* nombre);

#endif // _INICIOSESION_H_