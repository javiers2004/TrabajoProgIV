#include "structures.h"
#include "funciones3.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// crearDiscusion(Usuario *user): función que se encarga de crear una discusión permitiendo introducir el tema a tratar además 
// del usuario que recibe por argumentos.
void crearDiscusion(Usuario *user) {
    system("cls || clear");
    Discusion d1;

    char str[100];
    char nombre[100]; // Almacena el nombre de la discusión
    printf("NOMBRE: \n");
	fflush(stdout);
	fgets(nombre, sizeof(nombre), stdin); // Escanea una cadena (%s) para el nombre

    d1.nombre = strdup(nombre);
    d1.creador = user;
    time_t tiempo_actual;
    time(&tiempo_actual);
    (*user).fechaCreacion = tiempo_actual;

    //COMPROBAR QUE NO EXISTE Y ASIGNAR SU ID CORRESPONDIENTE (BASES DE DATOS)

    agregarNuevaDiscusion(user, &d1);

}


// agregarNuevaDiscusion(Usuario *user, Discusion *disc): función que se encarga de añadir la nueva discusión creada a la base de 
// datos. Se llama desde crearDiscusion(Usuario *user).
void agregarNuevaDiscusion(Usuario *user, Discusion *disc) {
    system("cls || clear");
    char* time_str = ctime(&((*disc).fechaCreacion));
    printf("Creando la nueva discusion  '%s'  de  %s  a  %s... \n", eliminarSalto((*disc).nombre), eliminarSalto((*disc).creador->nombre), eliminarSalto(time_str));
    sleep(4);
    system("cls || clear");
    printf("Discusion creada con exito");
    sleep(2);
    system("cls || clear");
    showMainMenu(user);
    //AÑADIR TODOS LOS CAMPOS DE LA DISCUSION A LA BASE DE DATOS
}


// eliminarSalto(char* frase): función para eliminar el '\n' de los campos y poder imprimir por pantalla los campos correctamente.
// Se llama desde agregarNuevaDiscusion(Usuario *user, Discusion *disc).
char* eliminarSalto(char* frase) {
    int i = 0;
    while(frase[i] != '\n' && frase[i] != '\0') {
        i++;
    }
    if (frase[i] == '\n') { 
        char* copia = (char*)malloc(sizeof(char) * (i + 1)); 
        if (copia == NULL) {
            return NULL; 
        }
        for (int e = 0; e < i; e++) {
            copia[e] = frase[e];
        }
        copia[i] = '\0'; 
        return copia; 
    } else { 
        return frase; 
    }
}
