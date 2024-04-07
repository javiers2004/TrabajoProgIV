#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones6.h"

void contarComentariosPorUsuario(const char *archivo) {
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
            total_caracteres += strlen(texto);
            total_comentarios++;
        }
    }

    printf("Conteo de comentarios por creador:\n");
    for (int i = 0; i < num_counters; i++) {
        printf("%s: %d comentarios\n", counters[i].creator, counters[i].comment_count);
    }

    if (total_comentarios > 0) {
        float media_caracteres = (float)total_caracteres / total_comentarios;
        printf("Media de caracteres por comentario: %.2f\n", media_caracteres);
    } else {
        printf("No se encontraron comentarios en el archivo.\n");
    }

    printf("Total de menciones en los comentarios: %d\n", total_menciones);

    fclose(file);
}
