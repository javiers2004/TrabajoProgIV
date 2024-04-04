#include "funciones2.h"
#include "structures.h"
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <unistd.h>
#include "funciones1.h"

// comentar(Usuario *user, Discusion *disc, Comentario *respuesta): función que a partir de un Usuario *user, una Discusion *disc y
// un Comentario *respuesta se encarga de solicitar por teclado el texto que albergará el comentario. Con todo esos datos genera una 
// estructura Comentario para guardarlo más tarde en la base de datos.
Comentario comentar(Usuario *user, Discusion *disc, Comentario *respuesta) {
    Comentario c1;
    c1.creador = user;
    c1.disc = disc;
    //c1.respuestaA = respuesta;
    char str[500];
    char texto[500]; // Almacena el contenido del comentario
    printf("Texto: \n");
	fflush(stdout);
	fgets(texto, sizeof(texto), stdin); // Escanea una cadena (%s) para el comentario

    c1.texto = strdup(texto);
    time_t tiempo;
    struct tm *info_tm;
    char buffer[26]; 
    time(&tiempo);
    info_tm = localtime(&tiempo);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", info_tm);
    c1.fechaCreacion = buffer;
    agregarstadistica(&c1);

}


void AgregarNuevoComentario(Comentario *coment) {

    //AGREGAR EL COMENTARIO A LA BASE DE DATOS
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("base.db", &db);
    if(rc != SQLITE_OK){
        fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    char *sql = "INSERT INTO Comentarios (Comentario, ID_User, ID_Discusion, FechaCreacion) VALUES (?, ?, ?, ?)";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if(rc == SQLITE_OK){
        sqlite3_bind_text(stmt, 1, coment->texto, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, coment->creador->id);
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
    for (int i = 0; discusiones[i].nombre != NULL; i++) {
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("%i . %s\n        creada por %s el %s\n",discusiones[i].id, discusiones[i].nombre, discusiones[i].creador->nombre, discusiones[i].fechaCreacion);
    }

    int disc_id;
    printf("-----------------------------------------------------------------------------------------------------\n");
    scanf("%i", &disc_id);

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    Discusion *disc_s = NULL;
    for(int i = 0; discusiones[i].nombre != NULL; i++) {
        if (discusiones[i].id == disc_id) {
            disc_s = &discusiones[i];
            printf("Discusion seleccionada: %s\n", disc_s->nombre);
            printf("Creada por: %s\n", disc_s->creador->nombre);
            printf("Fecha de creación: %s\n", disc_s->fechaCreacion);
            printf("-----------------------------------------------------------------------------------------------------\n");
            printf("COMENTARIOS:\n");
            // Leer comentarios
            
            break;
        }
    }
    if(disc_s !=NULL){
        printf("¿Deseas comentar en esta discusión? Presiona 1, cualquier otra tecla para salir.\n");
        int op;
        if(scanf("%d", &op) == 1 && op == 1){
            while((c = getchar()) != '\n' && c != EOF) { }
            Comentario c1 = comentar(user, disc_s, NULL);
            AgregarNuevoComentario(&c1);
        }
    }else{
        printf("Discusión no encontrada.\n");
    }
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

