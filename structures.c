#include "structures.h"
#include "stdio.h"
#include <stdlib.h>
//FUNCIONES

void showMainMenu(char* nombreusuario) {
    if(nombreusuario == NULL) {
        printf("1. Iniciar sesion/Registrarse \n 2.Buscar una discusion \n 3.Crear nueva discusion \n 4.Mostrar estadisticas");

    }
    else {
         printf("1. Cerrar sesion \n 2.Buscar una discusion \n 3.Crear nueva discusion \n 4.Mostrar estadisticas");
    }
}

void inicioSesionoRegistro() {
    system("cls || clear");
    printf("1.Iniciar sesion \n 2.Registrarse");
        int seleccion;
        char numero[10];
        fgets(numero, 3, stdin);
        sscanf(numero," %c", &seleccion);
        if(seleccion == 1) {
            system("cls || clear");
            printf("---------- INICIAR SESION ----------");
        }
        else if(seleccion == 2) {
            system("cls || clear");
            printf("---------- REGISTRARSE ----------");
        }
        else {
        }
}



