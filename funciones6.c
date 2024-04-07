
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "funciones6.h"
#include "structures.h"
void contarComentariosPorUsuario(Usuario user, const char *archivo) {
    system("cls || clear");
    FILE *file = fopen(archivo, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo %s\n", archivo);
        return;
    }

    char line[256];
    CommentCounter counters[100];
    int num_counters = 0;

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, "|");
        char creator[50] = "";
        while (token != NULL) {
            if (strstr(token, "Creador:") != NULL) {
                sscanf(token, " Creador: %s", creator);
                int found = 0;
                for (int i = 0; i < num_counters; i++) {
                    if (strcmp(counters[i].creator, creator) == 0) {
                        counters[i].comment_count++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(counters[num_counters].creator, creator);
                    counters[num_counters].comment_count = 1;
                    num_counters++;
                }
            }
            token = strtok(NULL, "|");
        }
    }

    printf("Conteo de comentarios por creador:\n");
    for (int i = 0; i < num_counters; i++) {
        printf("%s: %d comentarios\n", counters[i].creator, counters[i].comment_count);
    }

    fclose(file);
    anadirEst(user);
    printf("Pulsa ENTER para continuar.");
    char linea[10];
    fgets(linea, 10, stdin);
    system("cls || clear");
    showMainMenu(&user);
}

void anadirEst(Usuario user) {
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("base.db", &db);

    char *sql = "INSERT INTO Estadisticas (Nombre, Fecha) VALUES (?, ?)";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    time_t tiempo;
    struct tm *info_tm;
    char buffer[26]; 
    time(&tiempo);
    info_tm = localtime(&tiempo);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", info_tm);
    sqlite3_bind_text(stmt, 1, user.nombre, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, buffer, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}