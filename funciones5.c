#include "funciones5.h"
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include <stdio.h>

void imprimirInfoUsuario(Usuario *user) {
    system("cls || clear");
    printf(" _________________________________\n");
    printf("|        Informacion Usuario      |\n");
    printf("|_________________________________|\n");
    printf("| Nombre:        %s\n", user->nombre);
    printf("| Email:         %s\n", user->email);
    printf("| Telefono:      %s\n", user->telefono);
    printf("| Fecha Creacion:%s\n", user->fechaCreacion);
    printf("|_________________________________|\n \n");

    printf("Pulsa ENTER para continuar.");
    char linea[10];
    fgets(linea, 10, stdin);
    system("cls || clear");
    showMainMenu(user);
}
