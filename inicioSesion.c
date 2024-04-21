#include "inicioSesion.h"
#include "structures.h"

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
        contrasenaRecursiva(user, 3, nombre);
    }
    else {
        system("cls || clear");
        printf("No hay ningun usuario con este nombre");
        sleep(4);
        system("cls || clear");
        printf("Si es tu primera vez aqui selecciona la opcion de Registrarse\n");
        sleep(4);
        system("cls || clear");
        inicioSesionoRegistro(user);
    }
}

// cerrarSesion(Usuario *user): función que simplemente cierra la sesión actual y te devuelve al menú principal.
void cerrarSesion(Usuario *user) {
    system("cls || clear");
    (*user).id = -1;
    printf("Cerrando sesion de %s.", (*user).nombre);
    sleep(1);
    system("cls || clear");
    printf("Cerrando sesion de %s..", (*user).nombre);
    sleep(1);
    system("cls || clear");
    printf("Cerrando sesion de %s...", (*user).nombre);
    sleep(1);
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

//leerUsuario(const char* nombre): función que a partir de un char* nombre busca en la base de datos un usuario con ese nombre y en el 
// caso de encontrarlo te devuelve un puntero a un usuario con todos los datos que le corresponden. Se usa cuando en leerDiscusiones();
Usuario* leerUsuario(const char* nombre) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
    const char *sql = "SELECT ID, Nombre, Contrasena, FechaCreacion, Telefono, Email FROM Usuarios WHERE Nombre = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    rc = sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
        
    Usuario *user = malloc(sizeof(Usuario)); 
    user->id = sqlite3_column_int(stmt, 0);
    user->nombre = strdup((char *)sqlite3_column_text(stmt, 1));
    user->contrasena = strdup((char *)sqlite3_column_text(stmt, 2));
    user->fechaCreacion = strdup((char *)sqlite3_column_text(stmt, 3));
    user->telefono = strdup((char *)sqlite3_column_text(stmt, 4));
    user->email = strdup((char *)sqlite3_column_text(stmt, 5));
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return user; 
}

// nombreExiste(const char *nombre): función que se encarga de decir si el nombre introducido ya ha sido usado por otra persona
// si es así devuelve 1, si no 0. Estafunción es usada en registro(Usuario *user) y en inicioSesion(Usuario *user) para comprobar 
// la posibilidad de usar el nombre/existencia del nombre introducido.
int nombreExiste(const char *nombre) {               // He usado const porque *nombre no se va a tocar
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
    const char *sql = "SELECT COUNT(*) FROM Usuarios WHERE Nombre = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    rc = sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);  
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return (count > 0); // Al ser count > 0 devuelve 1 y se daría en el caso de que ya haya sido usado ese nombre
}

// verificarCredenciales(const char *nombre, const char *base.dbcontrasena): función que se encarga de decir si existe un usuario con el 
// nombre y contraseña introducidos y en el caso de haberlo devuelve 1, sino 0. Esta función es llamada en inicioSesion(Usuario *user)
int verificarCredenciales(const char *nombre, const char *contrasena) {         // He usado const porque ni nombre ni contraseña se tocan
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    rc = sqlite3_open(obtenerLineaPorNumero(6), &db);
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

// contrasenaRecursiva(Usuario *user, int intentos, char* nombre): función recursiva para manejar los intentos de contraseñas
// introducidas.
void contrasenaRecursiva(Usuario *user, int intentos, char* nombre) {
    char contrasena[20]; // Almacena la contraseña
    char str[20];
	printf("INGRESE LA CONTRASENA: \n");
	fflush(stdout);
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%s", contrasena); // Escanea una cadena (%s) para la contraseña
	clearIfNeeded(str, sizeof(str));
    if(verificarCredenciales(nombre, contrasena) == 1) { // CASO DE QUE LA CONTRASEÑA INTRODUCIDA SEA CORRECTA
        user = leerUsuario(nombre);
        system("cls || clear");
        printf("Iniciando sesion de %s.", (*user).nombre);
        sleep(1);
        system("cls || clear");
        printf("Iniciando sesion de %s..", (*user).nombre);
        sleep(1);
        system("cls || clear");
        printf("Iniciando sesion de %s...", (*user).nombre);
        sleep(1);
        system("cls || clear");
        printf("Sesion iniciada con exito\n");
        sleep(2);
        system("cls || clear");
        showMainMenu(user);
    }
    else if(intentos > 0) {  // CASO DE QUE LA CONTRASEÑA INTRODUCIDA SEA INCORRECTA PERO QUEDEN INTENTOS
        system("cls || clear");
        printf("Contrasena incorrecta");
        sleep(4);
        system("cls || clear");
        printf("Intentos: %i \n", intentos);
        contrasenaRecursiva(user, intentos -1, nombre);
    }   
    else {  // CASO DE QUE LA CONTRASEÑA INTRODUCIDA SEA INCORRECTA Y NO QUEDEN INTENTOS
        system("cls || clear");
        printf("Has introducido demasiadas veces una contrasena incorrecta");
        sleep(4);
        system("cls || clear");
        printf("Volveras al menu principal en 3");
        sleep(1);
        system("cls || clear");
        printf("Volveras al menu principal en 2");
        sleep(1);
        system("cls || clear");
        printf("Volveras al menu principal en 1");
        sleep(1);
        system("cls || clear");
        inicioSesionoRegistro(user);
    }
}






