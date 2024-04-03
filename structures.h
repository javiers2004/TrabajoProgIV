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
<<<<<<< HEAD

=======
>>>>>>> 51c5e6da88e7552266423e2ec4b81f2b1154437d

#endif // _STRUCTURES_H_