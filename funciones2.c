#include "funciones2.h"
#include "structures.h"
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <unistd.h>

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
    time_t tiempo_actual;
    time(&tiempo_actual);
    c1.fechaCreacion = tiempo_actual;

}


void AgregarNuevoComentario(Comentario *coment) {

    //AGREGAR EL COMENTARIO A LA BASE DE DATOS

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

        int fecha_creacion = sqlite3_column_int(stmt, 3);

        Discusion d;
        d.id = id;
        d.nombre = strdup((char *)nombre); 

        d.fechaCreacion = fecha_creacion;

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
void desplegarDiscusiones() {
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
        printf("%i . %s\n  creada por %s\n",discusiones[i].id, discusiones[i].nombre, discusiones[i].fechaCreacion);
    }
}
