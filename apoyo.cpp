#include "apoyo.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* strreplace(char *o) {
    int posicionarroba = -1;
    int posicionespacio = -1;
    int i = 0;
    while(o[i] != '\0') {
        if(o[i] == '@') {
            posicionarroba = i;
        }
        i++;
    }
    i = posicionarroba;
    while(o[i] != '\0') {
        if(o[i] == ' ') {
            posicionespacio = i;
            break;
        }
        i++;
    }
    if(posicionespacio == -1) {
        posicionespacio = i;    
    }
    int e;
    for (int e = 0; o[e] != '\0'; e++) {
        if (e >= posicionarroba && e < posicionespacio && posicionarroba != -1) {
            printf("\x1b[34m%c\x1b[0m", o[e]); // Impresión en azul (código ANSI)
        } else {
            printf("%c", o[e]); // Impresión en blanco
        }
    }
    printf("\n");
    return o;
}
// eliminarSalto(char* frase): función para eliminar el '\n' de los campos y poder imprimir por pantalla los campos correctamente.
// Se llama desde agregarNuevaDiscusion(Usuario *user, Discusion *disc).
char* eliminarSalto( const char* frase) {
    int i = 0;
    while(frase[i] != '\n' && frase[i] != '\0') {
        i++;
    }
    if (frase[i] == '\n') { 
        char* copia = (char*)malloc(sizeof(char) * (i + 1)); 
        int e;
        for (e = 0; e < i; e++) {
            copia[e] = frase[e];
        }
        copia[i] = '\0'; 
        return copia; 
    } else { 
        char* copia = (char*)malloc(sizeof(char) * (i + 1)); 
        int e;
        for (e = 0; e < i; e++) {
            copia[e] = frase[e];
        }
        return copia; 
    }
}
//funcion para leer un archivo adminConfig.txt y obtener los datos de configuracion del administrador (nombre, contraseña y base de datos) 
char* obtenerLineaPorNumero(int numeroLinea) {
    FILE* archivo = fopen("adminConfig.txt", "r");
    char* linea = NULL;
    size_t longitud = 0;
    ssize_t leidos;
    int contador = 0;

    // Leer el archivo línea por línea
    while ((leidos = getline(&linea, &longitud, archivo)) != -1) {
        contador++;
        if (contador == numeroLinea) {
            // Hemos encontrado la línea que buscamos
            // Eliminar el carácter de nueva línea, si existe
            if (linea[leidos - 1] == '\n')
                linea[leidos - 1] = '\0';
            fclose(archivo);
            return linea;
        }
    }

    fclose(archivo);
}

// clearIfNeeded(char *str, int max_line): finción utilizada en inicioSesion(Usuario *user) y en registro(Usuario *user) para
// limpiar los campos introducidos por el usuario mediante el teclado.
void clearIfNeeded(char *str, int max_line) {
	// Limpia los caracteres de más introducidos
	if ((strlen(str) == max_line-1) && (str[max_line-2] != '\n'))
		while (getchar() != '\n');
}