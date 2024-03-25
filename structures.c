#include "structures.h"
#include "stdio.h"
#include <stdlib.h>
//FUNCIONES

void showMainMenu(char** nombreusuario) {
        if(nombreusuario != NULL) {
            printf("Hola, %s \n", nombreusuario);
        }
        printf(" 1.Iniciar sesion/Registrarse \n 2.Buscar una discusion \n 3.Crear nueva discusion \n 4.Mostrar estadisticas \n");
        int seleccion;
        char numero[10];
        fgets(numero, 3, stdin);
        sscanf(numero," %c", &seleccion);
        printf("%i",seleccion);
        if(seleccion == '1') {
            inicioSesionoRegistro(nombreusuario);
        }
        if(seleccion == '2') {
            inicioSesionoRegistro(nombreusuario);
        
    }
    else {
         printf(" 1.Cerrar sesion \n 2.Buscar una discusion \n 3.Crear nueva discusion \n 4.Mostrar estadisticas \n");
    }
}

void inicioSesionoRegistro(char** nombreusuario) {
    system("cls || clear");
    printf(" 1.Iniciar sesion \n 2.Registrarse");
        int seleccion;
        char numero[10];
        fgets(numero, 3, stdin);
        sscanf(numero," %c", &seleccion);
        if(seleccion = '1') {
            system("cls || clear");
            printf("---------- INICIAR SESION ----------");
            inicioSesion(nombreusuario);
        }
        else if(seleccion == 2) {
            system("cls || clear");
            printf("---------- REGISTRARSE ----------");
        }
        else {
        }
}

void inicioSesion(char** nombreusuario) {
    system("cls || clear");
    printf("Nombre de usuario: \n");
    char num[10];
    fgets(num, 3, stdin);
    sscanf(num," %c", *nombreusuario);
}



