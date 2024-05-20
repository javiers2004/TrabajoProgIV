
#include "structures.h"
#include "sqlite3.h"
#include "menuPrincipal.h"
#include "crearDiscusiones.h"
#include "apoyo.h"
#include "inicioSesion.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <winsock2.h>
#include <string>

extern SOCKET s;
char sendBuff[512], recvBuff[512];

// crearDiscusion(Usuario *user): función que se encarga de crear una discusión permitiendo introducir el tema a tratar además 
// del usuario que recibe por argumentos.
void crearDiscusion(Usuario *user, char* nombreCreador) {
    system("cls || clear");
    Discusion *d1  = new Discusion();
    char str[100];
    char nombre[100]; // Almacena el nombre de la discusión
    printf("%s", nombreCreador);
    printf("NOMBRE: \n");
	fflush(stdout);
    printf("\n\n-------------------------------------------- \nPulse 'Enter' para volver al menu principal \n \n \n");
	fgets(nombre, sizeof(nombre), stdin); // Escanea una cadena (%s) para el nombre
    if(nombre[0] == '\n') {
        system("cls || clear");
        showMainMenu(user); 
    }else{
    if (discusionExiste(nombre) == 1) {
        system("cls || clear");
        printf("Esta discusion ya existe");
        sleep(3);
        system("cls || clear");
        printf("Encuentrala en 'buscar una discusion'");
        sleep(3);
        system("cls || clear");
        showMainMenu(user);
    }
    else {   
                  printf("%s", nombreCreador);
                sleep(5);
        d1->nombre = strdup(nombre);
        // time_t tiempo;
        // struct tm *info_tm;
        // char buffer[26]; 

        // time(&tiempo);
        // info_tm = localtime(&tiempo);
        // strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", info_tm);
        // d1->fechaCreacion = buffer;
        agregarNuevaDiscusion(user, d1, nombreCreador);

    }}
}

// agregarNuevaDiscusion(Usuario *user, Discusion *disc): función que se encarga de añadir la nueva discusión creada a la base de 
// datos. Se llama desde crearDiscusion(Usuario *user).
void agregarNuevaDiscusion(Usuario *user, Discusion *disc, char* nombreCreador) {
    system("cls || clear");
    printf("Creando la nueva discusion  '%s'  de  %s  el  %s... \n", eliminarSalto((*disc).nombre), nombreCreador, eliminarSalto((*disc).fechaCreacion));
    insertarDiscusion(disc, nombreCreador);
    sleep(4);
    system("cls || clear");
    printf("Discusion creada con exito");
    sleep(2);
    system("cls || clear");
    showMainMenu(user); 
}

// insertarDiscusion(Discusion *disc): función que se encarga de insertar la discusion que recibe como argumento dentro de la base
// de datos 'base.db'. Es llamada desde agregarNuevaDiscusion(Usuario *user, Discusion *disc).
void insertarDiscusion(Discusion *disc, char* nombreCreador) {
    char code[] = "INSERTARDISCUSION:";
	strcpy(sendBuff, code);
    strcat(sendBuff, disc->nombre);
    strcat(sendBuff, ":");
    strcat(sendBuff, nombreCreador);
	send(s, sendBuff, sizeof(sendBuff), 0);
}

// discusionExiste(char* nombre): función que se encarga de verificar si el string que se pasa como argumentos ya es el nombre de una
// discusion de la base de datos, es decir, si la discusión ya existe. Si existe, devuelve 1, si no devuelve 0.
int discusionExiste(const char* nombre) {

    char code[] = "DISCUSIONEXISTE:";

	strcpy(sendBuff, strcat(code, nombre));
	send(s, sendBuff, sizeof(sendBuff), 0);
	recv(s, recvBuff, sizeof(recvBuff), 0);
	return std::stoi(recvBuff);

}

// obtenerIdMaximoDiscusiones(): función que devuelve el int de la última discusión de la base de datos
int obtenerIdMaximoDiscusiones() {
    char code[] = "OBTENERIDMAXIMO:";
	strcpy(sendBuff, strcat(code, " "));
	send(s, sendBuff, sizeof(sendBuff), 0);
	recv(s, recvBuff, sizeof(recvBuff), 0);
    printf("%s", recvBuff);
	return std::stoi(recvBuff);
}

