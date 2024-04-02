#include "structures.h"
#include "funciones3.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sqlite3.h"


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
    if (discusionExiste(nombre) == 1) {
        system("cls || clear");
        printf("Esta discusion ya existe");
        sleep(3);
        system("cls || clear");
        printf("Encuentrala en 'buscar una discusion'");
        sleep(3);
        system("cls || clear");
        showMainMenu(user);

    }
    else {   
        d1.nombre = strdup(nombre);
        d1.creador = user;
        time_t tiempo_actual;
        time(&tiempo_actual);
        (*user).fechaCreacion = tiempo_actual;

        agregarNuevaDiscusion(user, &d1);
    }
}


// agregarNuevaDiscusion(Usuario *user, Discusion *disc): función que se encarga de añadir la nueva discusión creada a la base de 
// datos. Se llama desde crearDiscusion(Usuario *user).
void agregarNuevaDiscusion(Usuario *user, Discusion *disc) {
    system("cls || clear");
    char* time_str = ctime(&((*disc).fechaCreacion));
    printf("Creando la nueva discusion  '%s'  de  %s  a  %s... \n", eliminarSalto((*disc).nombre), eliminarSalto((*disc).creador->nombre), eliminarSalto(time_str));
    insertarDiscusion(disc);
    sleep(4);
    system("cls || clear");
    printf("Discusion creada con exito");
    sleep(2);
    system("cls || clear");
    showMainMenu(user);
    
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


// insertarDiscusion(Discusion *disc): función que se encarga de insertar la discusion que recibe como argumento dentro de la base
// de datos 'base.db'. Es llamada desde agregarNuevaDiscusion(Usuario *user, Discusion *disc).
void insertarDiscusion(Discusion *disc) {
    sqlite3 *db;
    char *err_msg = 0;
    char sql[500];

    int rc = sqlite3_open("base.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    sprintf(sql, "INSERT INTO Discusiones (Nombre, Creador, FechaCreacion) VALUES ('%s', '%s', '%s');",
            (*disc).nombre, (*disc).creador->nombre, (*disc).fechaCreacion);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error SQL al insertar usuario: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
    }
    sqlite3_close(db);
}


// discusionExiste(char* nombre): función que se encarga de verificar si el string que se pasa como argumentos ya es el nombre de una
// discusion de la base de datos, es decir, si la discusión ya existe. Si existe, devuelve 1, si no devuelve 0.
int discusionExiste(char* nombre) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open("base.db", &db);

    const char *sql = "SELECT COUNT(*) FROM Discusiones WHERE Nombre = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    rc = sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);  
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return (count > 0); 
}
