#include "structures.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funciones1.h"
#include <unistd.h>
#include "sqlite3.h"


// inicioSesionoRegistro(Usuario *user): función llamada desde la funcion showMainMenu(Usuario *user)(con la opción 1), se encarga de
// preguntar al usuario por la opción que desea: 1.Iniciar sesión o 2.Registrarse, lee la entrada por teclado y llama a la función que 
//corresponda.
void inicioSesionoRegistro(Usuario *user) {
    system("cls || clear");
    printf(" 1.Iniciar sesion \n 2.Registrarse \n");
    char numero[10];
    fgets(numero, sizeof(numero), stdin);
    if(numero[0] == '1') {
        system("cls || clear");
        printf("---------- INICIAR SESION ----------");
        inicioSesion(user);
    }
    else if(numero[0] == '2') {
        system("cls || clear");
        printf("---------- REGISTRARSE ----------");
        registro(user);
    }
    else {
        // Manejar otra entrada si es necesario
    }
}


// inicioSesion(Usuario *user): función llamada por inicioSesionoRegistro(Usuario *user)(opción 1), se encarga de pedir el nombre y la
// contraseña para el correcto inicio de sesión. Cuando introduces el nombre comprueba que está en la base de datos (si no está 
// te manda atrás) y cuando introduces la contraseña comprueba un usuario cuyos campos coincidan (si no te manda de vuelta al menú 
// principal). Si todo está correcto te manda al menú principal pero con la sesión iniciada.
void inicioSesion(Usuario *user) {
    system("cls || clear");
    char str[20];
	char nombre[20]; // Almacena el nombre de usuario
	char contrasena[20]; // Almacena la contraseña
	printf("INGRESE EL NOMBRE: \n");
	fflush(stdout);
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%s", nombre); // Escanea una cadena (%s) para el nombre
	clearIfNeeded(str, sizeof(str));
    if(nombreExiste(nombre) == 1) {
        system("cls || clear");
	    printf("INGRESE LA CONTRASENA: \n");
	    fflush(stdout);
	    fgets(str, sizeof(str), stdin);
	    sscanf(str, "%s", contrasena); // Escanea una cadena (%s) para la contraseña
	    clearIfNeeded(str, sizeof(str));
        if(verificarCredenciales(nombre, contrasena) == 1) {
            (*user).nombre = strdup(nombre); // Asigna memoria y copia el nombre
            (*user).contrasena = strdup(contrasena); // Asigna memoria y copia la contraseña

            (*user).id = 1;
            system("cls || clear");
            printf("Iniciando sesion de %s...", (*user).nombre);
            sleep(4);
            system("cls || clear");
            printf("Sesion iniciada con exito\n");
            sleep(2);
            system("cls || clear");
            showMainMenu(user);
        }
        else {
            system("cls || clear");
            printf("Contrasena incorrecta");
            sleep(4);
            showMainMenu(user);
        }
    }
    else {
        system("cls || clear");
        printf("No hay ningun usuario con este nombre");
        sleep(4);
        system("cls || clear");
        printf("Si es tu primera vez aqui selecciona la opcion de Registrarse\n");
        sleep(4);
        system("cls || clear");
        showMainMenu(user);
    }



}


// clearIfNeeded(char *str, int max_line): finción utilizada en inicioSesion(Usuario *user) y en registro(Usuario *user) para
// limpiar los campos introducidos por el usuario mediante el teclado.
void clearIfNeeded(char *str, int max_line) {
	// Limpia los caracteres de más introducidos
	if ((strlen(str) == max_line-1) && (str[max_line-2] != '\n'))
		while (getchar() != '\n');
}


// cerrarSesion(Usuario *user): función que simplemente cierra la sesión actual y te devuelve al menú principal.
void cerrarSesion(Usuario *user) {
    system("cls || clear");

    (*user).id = -1;
    printf("Cerrando sesion de %s...", (*user).nombre);
    sleep(4);
    system("cls || clear");
    (*user).nombre = NULL;
    (*user).contrasena = NULL;
    (*user).email = NULL;
    (*user).telefono = NULL;
    printf("Sesion cerrada con exito\n");
    sleep(2);
    system("cls || clear");
    showMainMenu(user);
}


// registro(Usuario *user): función para registrarse por primera vez, es llamada desde inicioSesionoRegistro(Usuario *user)(opción 2)
// y te pregunta sobre los diferentes campos del Usuario: nombre, contraseña, email y telefono (comprobando que no esté ese nombre 
// usado de antes). Si todo funciona correctamente, te devuelve al menú principal además con la sesión iniciada y también
// llama a insertarUsuario(Usuario *user) para que se incluya en la base de datos.
void registro(Usuario *user) {
    system("cls || clear");
    char str[20];
	char nombre[20]; // Almacena el nombre de usuario
	char contrasena[20]; // Almacena la contraseña
    char email[30];
    char telefono[12];
	printf("INGRESE EL NOMBRE: \n");
	fflush(stdout);
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%s", nombre); // Escanea una cadena (%s) para el nombre
	clearIfNeeded(str, sizeof(str));
    if(nombreExiste(nombre) == 1) {                     //NOMBRE YA ESTÁ EN USO
        system("cls || clear");
        printf("Este nombre ya esta en uso. Prueba con otro");
        sleep(4);
        system("cls || clear");
        showMainMenu(user);
    }
    else {                                              //NOMBRE DISPONIBLE
        system("cls || clear");
	    printf("INGRESE LA CONTRASENA: \n");
	    fflush(stdout);
	    fgets(str, sizeof(str), stdin);
	    sscanf(str, "%s", contrasena); 
	    clearIfNeeded(str, sizeof(str));
        system("cls || clear");
        printf("INGRESE EL EMAIL: \n");
	    fflush(stdout);
	    fgets(str, sizeof(str), stdin);
	    sscanf(str, "%s", email); 
    	clearIfNeeded(str, sizeof(str));
        system("cls || clear");
        printf("INGRESE EL TELEFONO: \n");
	    fflush(stdout);
	    fgets(str, sizeof(str), stdin);
	    sscanf(str, "%s", telefono); 
	    clearIfNeeded(str, sizeof(str));
        system("cls || clear");

	    (*user).nombre = strdup(nombre); 
        (*user).contrasena = strdup(contrasena); 
        (*user).email = email;
        (*user).telefono = telefono;
        time_t tiempo_actual;
        time(&tiempo_actual);
        (*user).fechaCreacion = tiempo_actual;
    
        insertarUsuario(user);

        (*user).id = 1;
        system("cls || clear");
        printf("Registro con exito de %s\n", (*user).nombre);
        sleep(2);
        system("cls || clear");
        showMainMenu(user);
    }
}


// insertarUsuario(Usuario *user): se encarga de establecer conexión con la base de datos y añadir al usuario que se le pasa por
// argumentos en la tabla Usuario, el Id se asigna automaticamente de manera ascendente.
void insertarUsuario(Usuario *user) {
    sqlite3 *db;
    char *err_msg = 0;
    char sql[500];

    int rc = sqlite3_open("base.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    sprintf(sql, "INSERT INTO Usuarios (Nombre, Contrasena, Telefono, Email) VALUES ('%s', '%s', '%s', '%s');",
            user->nombre, user->contrasena, user->telefono, user->email);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error SQL al insertar usuario: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
    }

    printf("Usuario insertado correctamente.\n");
    sqlite3_close(db);
}


// nombreExiste(const char *nombre): función que se encarga de decir si el nombre introducido ya ha sido usado por otra persona
// si es así devuelve 1, si no 0. Estafunción es usada en registro(Usuario *user) y en inicioSesion(Usuario *user) para comprobar 
// la posibilidad de usar el nombre/existencia del nombre introducido.
int nombreExiste(const char *nombre) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open("base.db", &db);

    const char *sql = "SELECT COUNT(*) FROM Usuarios WHERE Nombre = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    rc = sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);  
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return (count > 0); 
}


// verificarCredenciales(const char *nombre, const char *contrasena): función que se encarga de decir si existe un usuario con el 
// nombre y contraseña introducidos y en el caso de haberlo devuelve 1, sino 0. Esta función es llamada en inicioSesion(Usuario *user)
int verificarCredenciales(const char *nombre, const char *contrasena) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open("base.db", &db);

    const char *sql = "SELECT COUNT(*) FROM Usuarios WHERE Nombre = ? AND Contrasena = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    rc = sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    rc = sqlite3_bind_text(stmt, 2, contrasena, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return (count > 0);
}