#include "structures.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funciones1.h"
//FUNCIONES

void showMainMenu(Usuario *user) {
    if((*user).nombre == NULL | (*user).id < 0) {
        printf("BIENVENIDO A --------\n");   
        printf(" 1.Iniciar sesion/Registrarse \n 2.Buscar una discusion \n 3.Crear nueva discusion \n 4.Mostrar estadisticas \n");
        char linea[10];
	    fgets(linea, 10, stdin);
        printf("%s", linea);
        switch (*linea) {
            case '1':
                inicioSesionoRegistro(user);
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            default:
                break;
        }
    }    
    else {
        printf("Hola, %s  \n", (*user).nombre, (*user).contrasena); 
        printf(" 1.Cerrar sesion \n 2.Buscar una discusion \n 3.Crear nueva discusion \n 4.Mostrar estadisticas \n");
        char linea[10];
	    fgets(linea, 10, stdin);
        printf("%s", linea);
        switch (*linea) {
            case '1':
                cerrarSesion(user);
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            default:
                break;
        }
    }
}

