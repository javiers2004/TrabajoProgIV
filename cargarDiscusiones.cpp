#include "inicioSesion.h"
#include "structures.h"
#include "sqlite3.h"
#include "apoyo.h"
#include "menuPrincipal.h"
#include "publicarComentario.h"
#include "cargarDiscusiones.h"
#include "crearDiscusiones.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
Discusion* cargarDiscusion(char* id) {
char sendBuff[512], recvBuff[512];
    sprintf(sendBuff, "CARGARDISCUSION:%s", id);

    send(comm_socket, sendBuff, strlen(sendBuff), 0);
    int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
    recvBuff[bytes] = '\0';

    if (strcmp(recvBuff, "NULL") == 0) {
        return NULL;
    }

    // Discusion *disc = (Discusion*) malloc(sizeof(Discusion));
    // char *token = strtok(recvBuff, ":");
    // disc->id = atoi(token);
    // token = strtok(NULL, ":");
    // strcpy(disc->nombre, token);
    // token = strtok(NULL, ":");
    // strcpy(disc->creador->nombre, token);
    // token = strtok(NULL, ":");
    // strcpy(disc->fechaCreacion, token);

    // Parsear la respuesta y crear la estructura de Discusion
    Discusion *disc = (Discusion*) malloc(sizeof(Discusion));
    disc->creador = (Usuario*) malloc(sizeof(Usuario));

    char *token = recvBuff;
    char temp[512];
    int i = 0;

    // Parsear el ID de la discusión
    while (*token != ':' && *token != '\0') {
        temp[i++] = *token++;
    }
    temp[i] = '\0';
    disc->id = atoi(temp);

    if (*token == ':') token++;  // Saltar el delimitador ':'

    // Parsear el nombre de la discusión
    i = 0;
    while (*token != ':' && *token != '\0') {
        if (i < sizeof(disc->nombre) - 1) {
            disc->nombre[i++] = *token++;
        } else {
            token++;  // Saltar el caracter actual si excede el tamaño del buffer
        }
    }
    disc->nombre[i] = '\0';

    if (*token == ':') token++;  // Saltar el delimitador ':'

    // Parsear el nombre del creador
    i = 0;
    while (*token != ':' && *token != '\0') {
        if (i < sizeof(disc->creador->nombre) - 1) {
            disc->creador->nombre[i++] = *token++;
        } else {
            token++;  // Saltar el caracter actual si excede el tamaño del buffer
        }
    }
    disc->creador->nombre[i] = '\0';

    if (*token == ':') token++;  // Saltar el delimitador ':'

    // Parsear la fecha de creación
    i = 0;
    while (*token != '\0') {
        if (i < sizeof(disc->fechaCreacion) - 1) {
            disc->fechaCreacion[i++] = *token++;
        } else {
            token++;  // Saltar el caracter actual si excede el tamaño del buffer
        }
    }
    disc->fechaCreacion[i] = '\0';

    return disc;

        
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

