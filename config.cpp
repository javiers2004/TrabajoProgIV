#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_FILE "usuario.config"

// Función para guardar el nombre de usuario en el archivo de configuración
void guardarNombreUsuario(const char* nombreUsuario) {
    FILE* configFile = fopen(CONFIG_FILE, "w");
    if (configFile == NULL) {
        printf("Error al abrir el archivo de configuración para guardar el nombre de usuario.\n");
        return;
    }
    fprintf(configFile, "%s\n", nombreUsuario);
    fclose(configFile);
}

// Función para cargar el nombre de usuario desde el archivo de configuración
char* cargarNombreUsuario() {
    FILE* configFile = fopen(CONFIG_FILE, "r");
    if (configFile == NULL) {
        printf("Error al abrir el archivo de configuración para cargar el nombre de usuario.\n");
        return NULL;
    }
    static char nombreUsuario[512];
    if (fgets(nombreUsuario, sizeof(nombreUsuario), configFile) == NULL) {
        fclose(configFile);
        return NULL;
    }
    nombreUsuario[strcspn(nombreUsuario, "\n")] = 0;
    fclose(configFile);
    return nombreUsuario;
}
