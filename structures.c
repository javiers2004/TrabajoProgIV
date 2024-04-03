#include "structures.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funciones1.h"
#include "funciones3.h"
#include "sqlite3.h"
#include "funciones2.h"
//FUNCIONES


// showMainMenu(Usuario *user): despliega el menú principal, que en función de si ya está dentro de un usuario, se encarga de 
// mostrar unas opciones u otras. Y además lee la entrada por teclado y en función de la opción seleccionada, se encarga de
// llamar a la función correspondiente
void showMainMenu(Usuario *user) {                      
    if((*user).nombre == NULL | (*user).id < 0) {
        printf("BIENVENIDO A --------\n");   
        printf(" 1.Iniciar sesion/Registrarse \n 2.Buscar una discusion \n");
        char linea[10];
	    fgets(linea, 10, stdin);
        switch (*linea) {
            case '1':
                inicioSesionoRegistro(user);
                break;
            case '2':
                desplegarDiscusiones();
                break;
            default:
                break;
        }
    }    
    else {
        printf("Hola, %s  \n", (*user).nombre, (*user).contrasena); 
        printf(" 1.Cerrar sesion \n 2.Buscar una discusion \n 3.Crear nueva discusion \n 4.Mostrar estadisticas \n");
        char linea[10];
	    fgets(linea, 10, stdin);
        switch (*linea) {
            case '1':
                cerrarSesion(user);
                break;
            case '2':
                desplegarDiscusiones();
                break;
            case '3':
                crearDiscusion(user);
                break;
            case '4':
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


