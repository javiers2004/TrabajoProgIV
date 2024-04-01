#include "structures.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funciones1.h"
#include <unistd.h>

void inicioSesionoRegistro(Usuario *user) {
    system("cls || clear");
    printf(" 1.Iniciar sesion \n 2.Registrarse \n");
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
    else {
        // Manejar otra entrada si es necesario
    }
}

void inicioSesion(Usuario *user) {
    system("cls || clear");

    char str[20];
	char nombre[20]; // Almacena el nombre de usuario
	char contrasena[20]; // Almacena la contraseña
	printf("INGRESE EL NOMBRE: \n");
	fflush(stdout);
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%s", nombre); // Escanea una cadena (%s) para el nombre
	clearIfNeeded(str, sizeof(str));
    system("cls || clear");
	printf("INGRESE LA CONTRASENA: \n");
	fflush(stdout);
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%s", contrasena); // Escanea una cadena (%s) para la contraseña
	clearIfNeeded(str, sizeof(str));
	(*user).nombre = strdup(nombre); // Asigna memoria y copia el nombre
    (*user).contrasena = strdup(contrasena); // Asigna memoria y copia la contraseña


    //FALTA TODO EL SISTEMA DE BASES DE DATOS
    (*user).id = 1;
    system("cls || clear");
    printf("Iniciando sesion de %s...", (*user).nombre);
    sleep(4);
    system("cls || clear");
    printf("Sesion iniciada con exito\n");
    sleep(2);
    system("cls || clear");
    showMainMenu(user);
}


void clearIfNeeded(char *str, int max_line) {
	// Limpia los caracteres de más introducidos
	if ((strlen(str) == max_line-1) && (str[max_line-2] != '\n'))
		while (getchar() != '\n');
}

void cerrarSesion(Usuario *user) {
    system("cls || clear");

    (*user).id = -1;
    printf("Cerrando sesion de %s...", (*user).nombre);
    sleep(4);
    system("cls || clear");
    (*user).nombre = NULL;
    (*user).contrasena = NULL;
    (*user).email = NULL;
    (*user).telefono = NULL;
    printf("Sesion cerrada con exito\n");
    sleep(2);
    system("cls || clear");
    showMainMenu(user);
}

void registro(Usuario *user) {
    system("cls || clear");

    char str[20];
	char nombre[20]; // Almacena el nombre de usuario
	char contrasena[20]; // Almacena la contraseña
    char email[30];
    char telefono[12];
	printf("INGRESE EL NOMBRE: \n");
	fflush(stdout);
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%s", nombre); // Escanea una cadena (%s) para el nombre
	clearIfNeeded(str, sizeof(str));
    system("cls || clear");
	printf("INGRESE LA CONTRASENA: \n");
	fflush(stdout);
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%s", contrasena); // Escanea una cadena (%s) para la contraseña
	clearIfNeeded(str, sizeof(str));
    system("cls || clear");
    printf("INGRESE EL EMAIL: \n");
	fflush(stdout);
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%s", email); // Escanea una cadena (%s) para el email
	clearIfNeeded(str, sizeof(str));
    system("cls || clear");
    printf("INGRESE EL TELEFONO: \n");
	fflush(stdout);
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%s", telefono); // Escanea una cadena (%s) para el telefono
	clearIfNeeded(str, sizeof(str));
    system("cls || clear");

	(*user).nombre = strdup(nombre); // Asigna memoria y copia el nombre
    (*user).contrasena = strdup(contrasena); // Asigna memoria y copia la contraseña
    (*user).email = email;
    (*user).telefono = telefono;
    time_t tiempo_actual;
    time(&tiempo_actual);
    (*user).fechaCreacion = tiempo_actual;

    //FALTA TODO EL SISTEMA DE BASES DE DATOS
    (*user).id = 1;
    system("cls || clear");
    printf("Registro con exito de %s\n", (*user).nombre);
    sleep(2);
    system("cls || clear");
    showMainMenu(user);

}