#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
#include <time.h>

//ESTRUCTURAS NECESARIAS   -> Usuario, Discusión, Comentario
typedef struct{
    int id;
    char* nombre;
    char* contrasena;
    char* fechaCreacion;
    char* telefono;
    char* email;
}Usuario;

typedef struct{
    int id;
    char* nombre;
    Usuario *creador;
    char* fechaCreacion;
}Discusion;

typedef struct{
    int id;
    char* texto;
    Usuario *creador;
    Discusion *disc;
    char* fechaCreacion;
   // Comentario *respuestaA;
}Comentario;


//FUNCIONES
void showMainMenu(Usuario *user);
void crearBaseDeDatosUsuarios();
void crearBaseDeDatosDiscusiones();
void crearBaseDeDatosComentarios();
void crearBaseDeDatosEstadisticas();

void eliminar(int id, int n);
char* obtenerLineaPorNumero(int numeroLinea);
#endif // _STRUCTURES_H_