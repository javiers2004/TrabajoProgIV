#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
//ESTRUCTURAS
typedef struct{
    int id;
    char* nombre;
    struct Usuario* creador;

}Discusion;

typedef struct{
    int id;
    char* nombre;
    char* contrasena;
    char* fechaCreacion;
}Usuario;

typedef struct{
    int id;
    char* texto;
    Usuario creador;
    char* fechaCreacion;
    struct Comentario* respuestaA;
}Comentario;


//FUNCIONES
void showMainMenu(char** nombreusuario);
void inicioSesionoRegistro(char** nombreusuario);
void inicioSesion(char** nombreusuario);




#endif // _STRUCTURES_H_