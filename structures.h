#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
#include <time.h>

//ESTRUCTURAS NECESARIAS   -> Usuario, Discusión, Comentario
typedef struct{
    int id;
    const char* nombre;
    const char* contrasena;
    const char* fechaCreacion;
    const char* telefono;
    const char* email;
}Usuario;

typedef struct{
    int id;
    const char* nombre;
    Usuario *creador;
    char* fechaCreacion;
}Discusion;

typedef struct{
    int id;
    const char* texto;
    Usuario *creador;
    Discusion *disc;
    char* fechaCreacion;
   // Comentario *respuestaA;
}Comentario;

typedef struct {
    char creator[50];
    int comment_count;
} CommentCounter;

#endif // _STRUCTURES_H_