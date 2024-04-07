#include "structures.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funciones1.h"
#include "funciones3.h"
#include "sqlite3.h"
#include "funciones2.h"
#include "funciones5.h"
#include <unistd.h>
#include "funciones6.h"
#include "funciones6.h"
//FUNCIONES


// showMainMenu(Usuario *user): despliega el menú principal, que en función de si ya está dentro de un usuario, se encarga de 
// mostrar unas opciones u otras. Y además lee la entrada por teclado y en función de la opción seleccionada, se encarga de
// llamar a la función correspondiente
void showMainMenu(Usuario *user) {                      
    if((*user).nombre == NULL | (*user).id < 0) {
        fflush(stdout);
        printf("BIENVENIDO A THREADSPHERE\n");   
        printf(" 1.Iniciar sesion/Registrarse \n 2.Buscar una discusion \n");
        char linea[10];
	    fgets(linea, 10, stdin);
        switch (*linea) {
            case '1':
                inicioSesionoRegistro(user);
                break;
            case '2':
                desplegarDiscusiones(user);
                break;
            default:
                break;
        }
    }    
    else {
        int n;
        char id[100];
        printf("Hola, %s\n", (*user).nombre); 
        printf(" 1.Cerrar sesion \n 2.Buscar una discusion \n 3.Crear nueva discusion \n 4.Mostrar estadisticas \n 5.Mostrar informacion de usuario \n");
        if(strcmp(user->nombre, "admin") == 0) {
            printf(" \n-OPCIONES DE ADMINISTRADOR-\n 6.Borrar usuario\n 7.Borrar discusion\n 8.Borrar comentario\n");
        }
        char linea[10];
	    fgets(linea, 10, stdin);
        switch (*linea) {
            case '1':
                cerrarSesion(user);
                break;
            case '2':
                desplegarDiscusiones(user);
                break;
            case '3':
                crearDiscusion(user);
                break;
            case '4':
                contarComentariosPorUsuario("estadisticas.txt");
                break;
            case '5':
                imprimirInfoUsuario(user);
                break;
            case '6':
                system("cls || clear");
                printf("ID del usuario:\n");
	            fgets(id, 100, stdin);
                n = atoi(id);
                eliminar(n, 6);
                system("cls || clear");
                showMainMenu(user);
                break;
            case '7':
                system("cls || clear");
                printf("ID de la discusion\n");
	            fgets(id, 100, stdin);
                n = atoi(id);
                eliminar(n, 7);
                system("cls || clear");
                showMainMenu(user);
                break;
            case '8':
                system("cls || clear");
                printf("ID del comentario\n");
	            fgets(id, 100, stdin);
                n = atoi(id);
                eliminar(n, 8);
                system("cls || clear");
                showMainMenu(user);
                break;
            default:
                break;
        }
    }
}



//crearBaseDeDatosUsuarios(): función para llamar solo la primera vez o si se quiere reiniciar la actual base (habría primero que 
// eliminarla y llamar a esta función). Crea una tabla Usuario con sus campos: id, nombre, contraseña, fecha creación, email 
// y telefono.
void crearBaseDeDatosUsuarios() {
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("base.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db); // Cerrar la conexión antes de salir
        return;
    }
    const char *sql = "CREATE TABLE IF NOT EXISTS Usuarios ("
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "Nombre TEXT UNIQUE NOT NULL,"
                      "Contrasena TEXT NOT NULL,"
                      "FechaCreacion TEXT,"
                      "Telefono TEXT,"
                      "Email TEXT"
                      ");";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Tabla creada correctamente.\n");
    }
    sqlite3_close(db);
}

//crearBaseDeDatosDiscusiones(): función para llamar solo la primera vez o si se quiere reiniciar la actual base (habría primero que 
// eliminarla y llamar a esta función). Crea una tabla Discusiones con sus campos: id, nombre, contraseña, fecha creación y creacion.
void crearBaseDeDatosDiscusiones() {
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("base.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db); // Cerrar la conexión antes de salir
        return;
    }
    const char *sql = "CREATE TABLE IF NOT EXISTS Discusiones ("
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "Nombre TEXT UNIQUE NOT NULL,"
                      "Creador INT NOT NULL,"
                      "FechaCreacion TEXT"
                      ");";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Tabla creada correctamente.\n");
    }
    sqlite3_close(db);
}

void crearBaseDeDatosComentarios() {
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("base.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db); // Cerrar la conexión antes de salir
        return;
    }
    const char *sql = "CREATE TABLE IF NOT EXISTS Comentarios ("
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "Comentario TEXT ,"
                      "IDUser TEXT NOT NULL,"
                      "IDDiscusion INT NOT NULL,"
                      "FechaCreacion TEXT"
                      ");";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Tabla creada correctamente.\n");
    }
    sqlite3_close(db);
}


void eliminar(int id, int n) {
    if(n == 6) {
        printf("Borrando...");
        sleep(2);
        sqlite3 *db;
        char *err_msg = 0;
        int rc = sqlite3_open("base.db", &db);

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
        int rc = sqlite3_open("base.db", &db);

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
        int rc = sqlite3_open("base.db", &db);
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

//funcion para leer un archivo adminConfig.txt y obtener los datos de configuracion del administrador (nombre, contraseña y base de datos) 
void leerConfigAdmin(char *nombre, char *contrasena, char *base) {
    FILE *fichero;
    char clave[100], valor[100];
    
    fichero = fopen("adminConfig.txt", "r");
    if (fichero == NULL) {
        printf("Error al abrir el fichero\n");
        return;
    }
    
    while (fscanf(fichero, "%s = %s", clave, valor) == 2) {
        if (strcmp(clave, "admin") == 0) {
            strcpy(nombreAdmin, valor);
        } else if (strcmp(clave, "contrasena") == 0) {
            strcpy(contrasenaAdmin, valor);
        } else if (strcmp(clave, "db") == 0) {
            strcpy(baseDatos, valor);
        }
    }

    fclose(fichero);
}

