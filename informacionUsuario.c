#include "cargarDiscusion.h"
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include"structures.h"
#include"menuPrincipal.h"
#include "informacionUsuario.h"



void imprimirInfoUsuario(Usuario *user) {
    system("cls || clear");
    printf(" ______________________________________________________________\n");
    printf("|                     Informacion Usuario                      |\n");
    printf("|______________________________________________________________|\n");
    printf("| Nombre:        %s\n", user->nombre);
    printf("| Email:         %s\n", user->email);
    printf("| Telefono:      %s\n", user->telefono);
    printf("| Fecha Creacion:%s\n", user->fechaCreacion);
    printf("|______________________________________________________________|\n \n");

    printf("Pulsa ENTER para continuar.");
    char linea[10];
    fgets(linea, 10, stdin);
    system("cls || clear");
    showMainMenu(user);
}
