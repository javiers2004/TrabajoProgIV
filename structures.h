#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
#include <time.h>
//ESTRUCTURAS

typedef struct{
    int id;
    char* nombre;
    char* contrasena;
    time_t fechaCreacion;
    char* telefono;
    char* email;
}Usuario;

typedef struct{
    int id;
    char* nombre;
    Usuario *creador;
    time_t fechaCreacion;
}Discusion;

typedef struct{
    int id;
    char* texto;
    Usuario creador;
    char* fechaCreacion;
    struct Comentario* respuestaA;
}Comentario;


//FUNCIONES
void showMainMenu(Usuario *user);

#endif // _STRUCTURES_H_