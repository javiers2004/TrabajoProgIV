#include "anadirEstadisticas.h"
#include "structures.h"

// contarComentariosPorUsuario(Usuario user, const char *archivo): función que a partir de un fichero de tipo .txt en donde están todos  
// los comentarios de los usuarios, imprime las estadísticas de la base de datos(comentarios totales, media de caracteres por comentario
// y total de menciones) e imprime todo por pantalla. También llama a anadirEst(Usuario user);
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
    int total_caracteres = 0;
    int total_comentarios = 0;
    int total_menciones = 0;

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, "|");
        char creator[50] = "";
        char *texto = NULL;
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
            } else if (strstr(token, "Texto:") != NULL) {
                texto = token;
                // Contar menciones en el texto
                char *mention = strchr(texto, '@');
                while (mention != NULL) {
                    total_menciones++;
                    mention = strchr(mention + 1, '@');
                }
            }
            token = strtok(NULL, "|");
        }
        if (texto != NULL) {
            total_caracteres += (strlen(texto)-9);
            total_comentarios++;
        }
    }
    printf("Conteo de comentarios por usuario:\n\n");               // imprime los comentarios por usuario
    for (int i = 0; i < num_counters; i++) {
        printf("    %s: %d comentarios\n", counters[i].creator, counters[i].comment_count);
    }
    if (total_comentarios > 0) {
        float media_caracteres = (float)total_caracteres / total_comentarios;  // Total de caracteres entre número de comentarios
        printf("\n\nMedia de caracteres por comentario: %.2f\n", media_caracteres);
    } else {
        printf("No se encontraron comentarios en el archivo.\n");       // en el caso de que total_comentarios sea 0, es decir no haya comentarios
    }
    printf("\n\nTotal de menciones(@) en los comentarios: %d\n", total_menciones);  // total menciones
    fclose(file);
    anadirEst(user);
    printf(" \n\nPulsa ENTER para continuar.");
    char linea[10];
    fgets(linea, 10, stdin);
    system("cls || clear");
    showMainMenu(&user);
}


// anadirEst(Usuario user): función que añade las solicitudes por parte de los usuarios de las estadísticas, incluyendo en la base de 
// datos la hora y quién fue el usuario que lo solicitó
void anadirEst(Usuario user) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
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