#include "inicioSesion.h"
#include "structures.h"
#include "admin.h"
#include "anadirEstadisticas.h"
#include "cargarDiscusiones.h"
#include "crearDiscusiones.h"
#include "informacionUsuario.h"
#include "menuPrincipal.h"
#include "apoyo.h"
#include "registro.h"
#include "publicarComentario.h"
#include "globals.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

//extern char* nombreU;

// showMainMenu(Usuario *user): despliega el menú principal, que en función de si ya está dentro de un usuario, se encarga de 
// mostrar unas opciones u otras. Y además lee la entrada por teclado y en función de la opción seleccionada, se encarga de
// llamar a la función correspondiente
void showMainMenu(Usuario *user) {  
    char* actual;                 
    if(strcmp(nombreU, "") == 0 | (*user).id < 0) {
        fflush(stdout);
        printf("BIENVENIDO A THREADSPHERE\n");   
        printf(" 1.Iniciar sesion/Registrarse \n 2.Buscar una discusion \n");
        char linea[10];
	    fgets(linea, 10, stdin);
        switch (*linea) {
            case '1':
                inicioSesionoRegistro(user);
                break;
            case '2':
                desplegarDiscusiones(user);
                break;
            default:
                break;
        }
    }    
    else {
        int n;
        char id[100];
        printf("Hola, %s\n", nombreU); 
        user = leerUsuario(nombreU);


        printf(" 1.Cerrar sesion \n 2.Buscar una discusion \n 3.Crear nueva discusion \n 4.Mostrar estadisticas \n 5.Mostrar informacion de usuario \n");
        if(strcmp(nombreU, "admin") == 0) {
            printf(" \n-OPCIONES DE ADMINISTRADOR-\n 6.Borrar usuario\n 7.Borrar discusion\n 8.Borrar comentario\n");
            printf("%s %s %s %s",(*user).nombre,(*user).contrasena,(*user).email,(*user).telefono);

        }
        char linea[10];
	    fgets(linea, 10, stdin);
        switch (*linea) {
            case '1':
                cerrarSesion(user);
                break;
            case '2':
                desplegarDiscusiones(user);
                break;
            case '3':
                crearDiscusion(user, user->nombre);
                break;
            case '4':
                contarComentariosPorUsuario(user, obtenerLineaPorNumero(8));
                break;
            case '5':
                imprimirInfoUsuario(user);
                break;
            case '6':
                if(strcmp(user->nombre, obtenerLineaPorNumero(2)) == 0) {
                    system("cls || clear");
                    printf("ID del usuario:\n");
	                fgets(id, 100, stdin);
                    n = atoi(id);
                    eliminar(n, 6);
                    system("cls || clear");
                    showMainMenu(user);
                }
                break;  
            case '7':
                if(strcmp(user->nombre, obtenerLineaPorNumero(2)) == 0) {
                    system("cls || clear");
                    printf("ID de la discusion\n");
	                fgets(id, 100, stdin);
                    n = atoi(id);
                    eliminar(n, 7);
                    system("cls || clear");
                    showMainMenu(user);
                }
                break;
            case '8':
                if(strcmp(user->nombre, obtenerLineaPorNumero(2)) == 0) {   
                    system("cls || clear");
                    printf("ID del comentario\n");
	                fgets(id, 100, stdin);
                    n = atoi(id);
                    eliminar(n, 8);
                    system("cls || clear");
                    showMainMenu(user);
                }
                break;
            default:
                break;
        }
    }
}
// inicioSesionoRegistro(Usuario *user): función llamada desde la funcion showMainMenu(Usuario *user)(con la opción 1), se encarga de
// preguntar al usuario por la opción que desea: 1.Iniciar sesión o 2.Registrarse, lee la entrada por teclado y llama a la función que 
//corresponda.
void inicioSesionoRegistro(Usuario *user) {
    system("cls || clear");
    printf(" 1.Iniciar sesion \n 2.Registrarse \n\n\nPulsa ENTER para volver atras\n");
    char numero[10];
    fgets(numero, sizeof(numero), stdin);
    if(numero[0] == '1') {
        system("cls || clear");
        printf("---------- INICIAR SESION ----------");
        inicioSesion(user);
    }
    else if(numero[0] == '2') {
        system("cls || clear");
        printf("---------- REGISTRARSE ----------");
        registro(user);
    }
    else if( numero[0] == '\n') {
        system("cls || clear");
        showMainMenu(user);   
    }
}