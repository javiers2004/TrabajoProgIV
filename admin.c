#include "cargarDiscusiones.h"
#include "structures.h"
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <unistd.h>
#include "publicarComentario.h"
#include <stdbool.h>
#include"admin.h"
// eliminar(int id, int n): función que recive dos int, el primero indicando el int de lo que quiere eliminar y el segundo de que tabla 
// siendo n == 6 para usuarios, n == 7 para discusiones y n == 8 para comentarios
void eliminar(int id, int n) {
    if(n == 6) {
        printf("Borrando...");
        sleep(2);
        sqlite3 *db;
        char *err_msg = 0;
        int rc = sqlite3_open(obtenerLineaPorNumero(6), &db);

        char *sql = "DELETE FROM Usuarios WHERE ID = ?";
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, id);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Error al eliminar el comentario: %s\n", sqlite3_errmsg(db));
        } else {
            printf("Comentario eliminado exitosamente.\n");
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
    if(n == 7) {
        printf("Borrando...");
        sleep(2);
        sqlite3 *db;
        char *err_msg = 0;
        int rc = sqlite3_open(obtenerLineaPorNumero(6), &db);

        char *sql = "DELETE FROM Discusiones WHERE ID = ?";
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, id);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Error al eliminar el comentario: %s\n", sqlite3_errmsg(db));
        } else {
            printf("Comentario eliminado exitosamente.\n");
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
    if(n == 8) {
        printf("Borrando...");
        sleep(2);
        sqlite3 *db;
        char *err_msg = 0;
        int rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
        char *sql = "DELETE FROM Comentarios WHERE ID = ?";
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, id);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Error al eliminar el comentario: %s\n", sqlite3_errmsg(db));
        } else {
            printf("Comentario eliminado exitosamente.\n");
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
}