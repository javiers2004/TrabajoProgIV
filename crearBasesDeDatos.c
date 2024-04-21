#include "crearBasesDeDatos.h"
#include "structures.h"

//crearBaseDeDatosUsuarios(): función para llamar solo la primera vez o si se quiere reiniciar la actual base (habría primero que 
// eliminarla y llamar a esta función). Crea una tabla Usuario con sus campos: id, nombre, contraseña, fecha creación, email 
// y telefono.
void crearBaseDeDatosUsuarios() {
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
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
// eliminarla y llamar a esta función). Crea una tabla Discusiones con sus campos: id, nombre, contraseña y fecha creación.
void crearBaseDeDatosDiscusiones() {
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
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



//crearBaseDeDatosComentarios(): función para llamar solo la primera vez o si se quiere reiniciar la actual base (habría primero que 
// eliminarla y llamar a esta función). Crea una tabla Comentarios con sus campos: id, comentario, IDUser, IDDiscusión y fecha creación.
void crearBaseDeDatosComentarios() {
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
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

void crearBaseDeDatosEstadisticas() {
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db); // Cerrar la conexión antes de salir
        return;
    }
    const char *sql = "CREATE TABLE IF NOT EXISTS Estadisticas ("
                      "FECHA TEXT PRIMARY KEY ,"
                      "Nombre TEXT"
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
