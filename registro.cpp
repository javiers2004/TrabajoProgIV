#include "structures.h"
#include "sqlite3.h"
#include "apoyo.h"
#include "menuPrincipal.h"
#include "registro.h"
#include "inicioSesion.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <winsock2.h>

extern SOCKET s;

// insertarUsuario(Usuario *user): se encarga de establecer conexión con la base de datos y añadir al usuario que se le pasa por
// argumentos en la tabla Usuario, el Id se asigna automaticamente de manera ascendente.
void insertarUsuario(Usuario *user) {
    char code[] = "INSERTARUSUARIO:";
    char sendBuff[512], recvBuff[512];

	strcpy(sendBuff, strcat(code, user->nombre));
    strcat(sendBuff, ":");
    strcat(sendBuff, user->contrasena);
    strcat(sendBuff, ":");
    strcat(sendBuff, user->telefono);
    strcat(sendBuff, ":");
    strcat(sendBuff, user->email);
    strcat(sendBuff, ":");
	send(s, sendBuff, sizeof(sendBuff), 0);
}

// registro(Usuario *user): función para registrarse por primera vez, es llamada desde inicioSesionoRegistro(Usuario *user)(opción 2)
// y te pregunta sobre los diferentes campos del Usuario: nombre, contraseña, email y telefono (comprobando que no esté ese nombre 
// usado de antes). Si todo funciona correctamente, te devuelve al menú principal además con la sesión iniciada y también
// llama a insertarUsuario(Usuario *user) para que se incluya en la base de datos.
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
    if(nombreExiste(nombre) == 1) {                     //NOMBRE YA ESTÁ EN USO
        system("cls || clear");
        printf("Este nombre ya esta en uso. Prueba con otro");
        sleep(4);
        system("cls || clear");
        registro(user);
    }
    else {                                              //NOMBRE DISPONIBLE
        system("cls || clear");
	    printf("INGRESE LA CONTRASENA: \n");
	    fflush(stdout);
	    fgets(str, sizeof(str), stdin);
	    sscanf(str, "%s", contrasena); 
	    clearIfNeeded(str, sizeof(str));
        system("cls || clear");
        printf("INGRESE EL EMAIL: \n");
	    fflush(stdout);
	    fgets(str, sizeof(str), stdin);
	    sscanf(str, "%s", email); 
    	clearIfNeeded(str, sizeof(str));
        system("cls || clear");
        printf("INGRESE EL TELEFONO: \n");
	    fflush(stdout);
	    fgets(str, sizeof(str), stdin);
	    sscanf(str, "%s", telefono); 
	    clearIfNeeded(str, sizeof(str));

        system("cls || clear");
        printf("Registrando usuario.");
	    (*user).nombre = strdup(nombre); 
        (*user).contrasena = strdup(contrasena); 
        (*user).email = email;
        (*user).telefono = telefono;

        time_t tiempo;
        struct tm *info_tm;
        char buffer[26]; 
        time(&tiempo);
        info_tm = localtime(&tiempo);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", info_tm);

        (*user).fechaCreacion = buffer;
        insertarUsuario(user);
        sleep(1);
        system("cls || clear");
        printf("Registrando usuario..");
        sleep(1);
        system("cls || clear");
        printf("Registrando usuario...");
        sleep(1);
        (*user).id = 1;
        system("cls || clear");
        printf("Registro con exito de %s\n", (*user).nombre);
        sleep(3);
        system("cls || clear");
        showMainMenu(user);
    }
}