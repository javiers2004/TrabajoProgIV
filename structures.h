#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
//ESTRUCTURAS
typedef struct{
    int id;
    char* nombre;
    Usuario creador;

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
    Comentario respuestaA;
}Comentario;


//FUNCIONES
void showMainMenu();
void inicioSesionoRegistro();





#endif // _STRUCTURES_H_