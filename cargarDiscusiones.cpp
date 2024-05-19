#include "inicioSesion.h"
#include "structures.h"
#include "sqlite3.h"
#include "apoyo.h"
#include "menuPrincipal.h"
#include "publicarComentario.h"
#include "cargarDiscusiones.h"
#include "crearDiscusiones.h"
#include <winsock2.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

extern SOCKET s;

// desplegarDiscusiones(): despliega todas las discusiones cuando es llamada desde showMainMenu(Usuario *user)(opción 2) y para ello usa la 
// función leerDiscusiones() de donde las recibirá.
void desplegarDiscusiones(Usuario *user) {
    system("cls || clear");
    printf("Recopilando discusiones.");
    sleep(1);
    system("cls || clear");
    printf("Recopilando discusiones..");
    sleep(1);
    system("cls || clear");
    printf("Recopilando discusiones...");
    sleep(1);
    Discusion *discusiones = leerDiscusiones();
    system("cls || clear");
    if (discusiones == NULL) {          // por si acaso no hubiera ninguna discusión
        printf("No hay discusiones para desplegar.\n");
        return;
    }

    printf("SELECCIONA LA DISCUSION A LA QUE DESEAS ACCEDER:\n");       //aquí te printea todas las referencias posibles
    for (int i = 0; i<obtenerIdMaximoDiscusiones(); i++) {
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("%i . %s\n        creada por %s el %s\n",discusiones[i].id, discusiones[i].nombre, discusiones[i].creador->nombre, discusiones[i].fechaCreacion);
    }

    printf("-----------------------------------------------------------------------------------------------------\n \n\n");
    printf("Pulsa ENTER para volver al menu principal\n");
    char linea[10];             // para leer la selección
	fgets(linea, 10, stdin);
    if(linea[0] == '\n') {
        system("cls || clear");
        showMainMenu(user);
        
    }else {	
    cargarSeleccion(linea, user);
   }
}
// cargarDiscusion(char* id): función que recibe un id de una conversacion y devuelve un puntero a la discusión
Discusion* cargarDiscusion(const char* id) {
    char sendBuff[512], recvBuff[512];
    char code[] = "CARGARDISCUSION:";

	strcpy(sendBuff, strcat(code, id));
    send(s, sendBuff, strlen(sendBuff), 0);
	recv(s, recvBuff, sizeof(recvBuff), 0);

    Discusion *d = new Discusion();

    char idConversacion[256];
    char nombre[256];
    char nombreCreador[256];
    char fecha[256];
    int i = 0;
    while(recvBuff[i] != ';') {
        idConversacion[i] = recvBuff[i];
        i++;
    }
    idConversacion[i] = '\0';
    i++;
    int e = 0;
    while(recvBuff[i] != '\n') {
        nombre[e] = recvBuff[i];
        i++;
        e++;
    }
    nombre[e] = '\0';
    i++;
    i++;
    e = 0;
    while(recvBuff[i] != ';') {
        nombreCreador[e] = recvBuff[i];
        i++;
        e++;
    }
    i++;
    e = 0;
    while(recvBuff[i] != ';') {
        fecha[e] = recvBuff[i];
        i++;
        e++;
    }
    d->id = idConversacion[3] - '0';
    d->nombre = nombre;
    //d->creador->nombre = nombreCreador;
    d->fechaCreacion = fecha;

    return d;
        
}
// cargarSeleccion(char* linea, Usuario *user): función que recibiendo un char* imprime los datos de la discusión con ese id y 
// todos sus comentarios
void cargarSeleccion(char* linea, Usuario *user) {
     Discusion *disc_num = cargarDiscusion(linea);

    system("cls || clear");
    printf("Discusion seleccionada: %s\n", disc_num->nombre);
    printf("Creada por: %s\n", disc_num->creador->nombre);
    printf("Fecha de creacion: %s\n", disc_num->fechaCreacion);
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("COMENTARIOS:\n");

    imprimirComentarios(linea);

    printf("\n \n \n");
    char str[500];
    printf("¿Algo interesante que comentar? Escribe tu mensaje o pulsa solo ENTER para volver al menu: \n");
	fflush(stdout);
	fgets(str, sizeof(str), stdin);
    
    Comentario *com = new Comentario();
    if(strcmp(str, "\n") == 1) {
        com->creador = user;
        com->disc = disc_num;
        com->texto = str;
        time_t tiempo;
        struct tm *info_tm;
        char buffer[26]; 
        time(&tiempo);
        info_tm = localtime(&tiempo);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", info_tm);
        com->fechaCreacion = buffer;
        AgregarNuevoComentario(com);
        free(com);
        cargarSeleccion(linea, user);
    }
    else {
        system("cls || clear");
        showMainMenu(user);
    }

}
// leerDiscusiones(): lee las discusiones de la base de datos y las devuelve mediante un Puntero Discusion*. Esta función es llamada 
// desde el método desplegarDiscusiones().
Discusion* leerDiscusiones() {
    
    
}
// imprimirComentarios(char* IDConversacion): función que recive un char* lo convierte a int y imprime por pantalla todos los
// comentarios de la conversación con dicho ID.
void imprimirComentarios(char* IDConversacion) {
    
}

