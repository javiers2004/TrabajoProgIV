#include "structures.h"
#include "sqlite3.h"
#include "apoyo.h"
#include "anadirEstadisticas.h"
#include "publicarComentario.h"

#include <stdio.h>

// comentar(Usuario *user, Discusion *disc, Comentario *respuesta): función que a partir de un Usuario *user, una Discusion *disc y
// un Comentario *respuesta se encarga de solicitar por teclado el texto que albergará el comentario. Con todo esos datos genera una 
// estructura Comentario para guardarlo más tarde en la base de datos.
void AgregarNuevoComentario(Comentario *coment) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
    char *sql = "INSERT INTO Comentarios (Comentario, IDUser, IDDiscusion, FechaCreacion) VALUES (?, ?, ?, ?)";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if(rc == SQLITE_OK){                //En el caso de que no haya error continuamos con el proceso
        sqlite3_bind_text(stmt, 1, coment->texto, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, coment->creador->nombre, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, coment->disc->id);
        sqlite3_bind_text(stmt, 4,coment->fechaCreacion,-1,SQLITE_TRANSIENT); 
        rc = sqlite3_step(stmt);
        if(rc != SQLITE_DONE){           // si hay error finalizamos el proceso
            printf("Error al insertar datos: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    }else{
        fprintf(stderr, "Error al preparar la inserción: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_close(db);
    agregarstadistica(coment);
}
// agregarstadistica(Comentario *com): función que reciviendo un puntero a un comentario lo añade al archivo de estadísticas
void agregarstadistica(Comentario *com) {
    FILE* fichero;
    fichero = fopen(obtenerLineaPorNumero(8), "a"); // a de "append" para añadir estadísticas al final

    if (fichero == NULL) {
        printf("Error al abrir el archivo de estadísticas.\n");
        return;
    }
    fprintf(fichero, "ID: %d | Texto: %s | Creador: %s | Discusión: %s | Fecha de creación: %s.\n",com->id, com->texto, com->creador->nombre, com->disc->nombre, com->fechaCreacion);
    fclose(fichero); 
}

// maxComentID(): función que devuelve el ultimo id asociado a un comentario de la base de datos + 1
int maxComentID() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int maxID = 0;
    rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
    const char *sql = "SELECT MAX(ID) FROM Comentarios";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    maxID = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return maxID + 1; 
}