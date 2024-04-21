#include "cargarDiscusion.h"
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include"structures.h"

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
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
    const char *sql = "SELECT ID, Nombre, FechaCreacion, Creador FROM Discusiones WHERE ID = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    rc = sqlite3_bind_text(stmt, 1, id, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
        
    Discusion *disc = malloc(sizeof(Discusion)); 
    disc->id = sqlite3_column_int(stmt, 0);
    disc->nombre = strdup((char *)sqlite3_column_text(stmt, 1));
    disc->fechaCreacion = strdup((char *)sqlite3_column_text(stmt, 2));
    disc->creador = leerUsuario(strdup((char *)sqlite3_column_text(stmt, 3)));

    sqlite3_finalize(stmt);
    sqlite3_close(db);

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
    
    Comentario *com = malloc(sizeof(Comentario));
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
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
    const char *sql = "SELECT ID, Nombre, Creador, FechaCreacion FROM Discusiones"; 
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    Discusion *discusiones = NULL;
    int num_discusiones = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nombre = sqlite3_column_text(stmt, 1);
        const unsigned char* nombreCreador = sqlite3_column_text(stmt, 2);
        Usuario *creator = leerUsuario(nombreCreador);        

        const unsigned char* fecha_creacion = sqlite3_column_text(stmt, 3);
        Discusion d;
        creator = leerUsuario((char *)nombreCreador);
        d.creador = creator;
        d.id = id;
        d.nombre = strdup((char *)nombre); 

        d.fechaCreacion = strdup((char *)fecha_creacion); 

        num_discusiones++;
        discusiones = realloc(discusiones, num_discusiones * sizeof(Discusion));
        discusiones[num_discusiones - 1] = d;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return discusiones;
}
// imprimirComentarios(char* IDConversacion): función que recive un char* lo convierte a int y imprime por pantalla todos los
// comentarios de la conversación con dicho ID.
void imprimirComentarios(char* IDConversacion) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int id_conversacion = atoi(IDConversacion);
    rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
    if (rc != SQLITE_OK) {          // por si no se encuentra la base
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    const char *sql = "SELECT ID, Comentario, IDUser, FechaCreacion FROM Comentarios WHERE IDDiscusion = ?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id_conversacion);
    while (sqlite3_step(stmt) == SQLITE_ROW) {      // itera por cada uno de los comentarios y los va imprimirndo uno a uno
        int id = sqlite3_column_int(stmt, 0);  
        char* comentario = (char*)sqlite3_column_text(stmt, 1);
        char* id_user = (char*)sqlite3_column_text(stmt, 2);
        char* fecha_creacion = (char*)sqlite3_column_text(stmt, 3);
        Comentario com;
        com.texto = eliminarSalto(comentario);
        com.fechaCreacion = fecha_creacion;
        com.id = maxComentID();
        Usuario *u = leerUsuario(id_user);
        com.creador = u;
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("%s\n%s: ", com.fechaCreacion, com.creador->nombre);
        strreplace(com.texto);
    }
    printf("-----------------------------------------------------------------------------------------------------\n");

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

