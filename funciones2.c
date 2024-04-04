#include "funciones2.h"
#include "structures.h"
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <unistd.h>
#include "funciones1.h"
#include "funciones3.h"
#include <stdbool.h>


// comentar(Usuario *user, Discusion *disc, Comentario *respuesta): función que a partir de un Usuario *user, una Discusion *disc y
// un Comentario *respuesta se encarga de solicitar por teclado el texto que albergará el comentario. Con todo esos datos genera una 
// estructura Comentario para guardarlo más tarde en la base de datos.



void AgregarNuevoComentario(Comentario *coment) {

    //AGREGAR EL COMENTARIO A LA BASE DE DATOS
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("base.db", &db);

    char *sql = "INSERT INTO Comentarios (Comentario, IDUser, IDDiscusion, FechaCreacion) VALUES (?, ?, ?, ?)";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if(rc == SQLITE_OK){
        sqlite3_bind_text(stmt, 1, coment->texto, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, coment->creador->nombre, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, coment->disc->id);
        sqlite3_bind_text(stmt, 4,coment->fechaCreacion,-1,SQLITE_TRANSIENT); 

        rc = sqlite3_step(stmt);
        if(rc != SQLITE_DONE){
            printf("Error al insertar datos: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    }else{
        fprintf(stderr, "Error al preparar la inserción: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_close(db);
}


// leerDiscusiones(): lee las discusiones de la base de datos y las devuelve mediante un Puntero Discusion*. Esta función es llamada 
// desde el método desplegarDiscusiones().
Discusion* leerDiscusiones() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    rc = sqlite3_open("base.db", &db);

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


// desplegarDiscusiones(): despliega todas las discusiones cuando es llamada desde showMainMenu(Usuario *user)(opción 2) y para ello usa la 
// función leerDiscusiones() de donde las recibirá.
void desplegarDiscusiones(Usuario *user) {
    // Verificar si el array de discusiones es NULL
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
    if (discusiones == NULL) {
        printf("No hay discusiones para desplegar.\n");
        return;
    }

    printf("SELECCIONA LA DISCUSION A LA QUE DESEAS ACCEDER:\n");
    for (int i = 0; i<obtenerIdMaximoDiscusiones(); i++) {
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("%i . %s\n        creada por %s el %s\n",discusiones[i].id, discusiones[i].nombre, discusiones[i].creador->nombre, discusiones[i].fechaCreacion);
    }

    printf("-----------------------------------------------------------------------------------------------------\n");
    char linea[10];
	fgets(linea, 10, stdin);
    cargarSeleccion(linea, user);
   
}
void agregarstadistica(Comentario *com) {
    FILE* fichero;
    fichero = fopen("estadisticas", "a"); // a de "append" para añadir estadísticas al final

    if (fichero == NULL) {
        printf("Error al abrir el archivo de estadísticas.\n");
        return;
    }

    fprintf(fichero, "ID: %d | Texto: %s | Creador: %s | Discusión: %s | Fecha de creación: %s.\n",com->id, com->texto, com->creador->nombre, com->disc->nombre, com->fechaCreacion);

    fclose(fichero); 
}



Discusion* cargarDiscusion(char* id) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open("base.db", &db);
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
bool UsuarioExiste(char *nombreUsuario){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    bool existe = false;
    int rc = sqlite3_open("base.db", &db);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }
    const char *sql = "SELECT * FROM Usuarios WHERE Nombre = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if(rc == SQLITE_OK){
        sqlite3_bind_text(stmt, 1, nombreUsuario, -1, SQLITE_STATIC);
        rc = sqlite3_step(stmt);
        if(rc == SQLITE_ROW){
            existe = true;
        }
    sqlite3_finalize(stmt);

    }else{
        fprintf(stderr, "error al verificar el usuario: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_close(db);
    return existe;
}

void imprimirComentarios(char* IDConversacion) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Convertir el ID de conversación a entero
    int id_conversacion = atoi(IDConversacion);

    // Abrir la base de datos
    rc = sqlite3_open("base.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }


int obtenerIdMaximoDiscusiones() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int max_id = -1;

    rc = sqlite3_open("base.db", &db);


    const char *sql = "SELECT MAX(ID) FROM Discusiones;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        max_id = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return max_id;
}

void strreplace(char *o, const char *sub, const char *replacement){
    char *pos = strstr(o, sub);
    if(pos == NULL){
        return;
    }
    char temp[strlen(o) + strlen(replacement) - strlen(sub) + 1];
    size_t n = pos - o;
    strncpy(temp, o, n);
    strcpy(temp + n, replacement);
    strcpy(temp + n + strlen(replacement), pos + strlen(sub));
    strcpy(o, temp);

}

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
    printf("¿QUE QUIERES DECIR? Escribe tu mensaje o pulsa solo ENTER para volver al menu: \n");
	fflush(stdout);
	fgets(str, sizeof(str), stdin);
    if(strcmp(str, "\n")!= 0){
        char *posm = strchr(str, '@');
        if(posm !=NULL){
            char nUser[50];
            sscanf(posm, "@%49s", nUser);
            if(UsuarioExiste(nUser)){
                char mencionFormat[500];
                sprintf(mencionFormat, "\x1B[1m\x1B[32m@%s\x1B[0m", nUser);
                strreplace(str,nUser,mencionFormat);
            }
        }
    }
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
        //printf("introduciendo");
        AgregarNuevoComentario(com);
        free(com);
    cargarSeleccion(linea, user);
    }
    else {
        system("cls || clear");
        showMainMenu(user);
    }
    
}



    // Preparar la consulta SQL para obtener comentarios
    const char *sql = "SELECT ID, Comentario, IDUser, FechaCreacion FROM Comentarios WHERE IDDiscusion = ?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    sqlite3_bind_int(stmt, 1, id_conversacion);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        char* comentario = (char*)sqlite3_column_text(stmt, 1);
        char* id_user = (char*)sqlite3_column_text(stmt, 2);
        char* fecha_creacion = (char*)sqlite3_column_text(stmt, 3);
        Comentario com;
        com.texto = eliminarSalto(comentario);
        com.fechaCreacion = fecha_creacion;
        Usuario *u = leerUsuario(id_user);
        com.creador = u;
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("%s\n%s: %s  \n", com.fechaCreacion, com.creador->nombre, com.texto);
    }
    printf("-----------------------------------------------------------------------------------------------------\n");

    // Finalizar la consulta y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}