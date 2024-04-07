
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
}