#include "inicioSesion.h"
#include "structures.h"
#include "sqlite3.h"
#include "apoyo.h"
#include "menuPrincipal.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <winsock2.h>
#include <iostream>
#include <cstring>
extern SOCKET s;
extern char* nombreU;

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
    nombreU = NULL;
    printf("Sesion cerrada con exito\n");
    sleep(2);
    system("cls || clear");
    showMainMenu(user);
}

//leerUsuario(const char* nombre): función que a partir de un char* nombre busca en la base de datos un usuario con ese nombre y en el 
// caso de encontrarlo te devuelve un puntero a un usuario con todos los datos que le corresponden. Se usa cuando en leerDiscusiones();
Usuario* leerUsuario(const char* nombre) {
    char sendBuff[512], recvBuff[512];
    printf("%s", nombre);
    char code[] = "LEERUSUARIO:";

	strcpy(sendBuff, strcat(code, nombre));
    strcat(sendBuff, ";");
    send(s, sendBuff, strlen(sendBuff), 0);
	recv(s, recvBuff, sizeof(recvBuff), 0);

    Usuario *u = new Usuario();

    char id[256];
    char nombreUsuario[256];
    char contrasena[256];
    char email[256];
    char telefono[256];
    char fechaCreacion[256];
    int i = 0;
    while(recvBuff[i] != ';') {
        id[i] = recvBuff[i];
        i++;
    }
    id[i] = '\0';

    i++;
    int e = 0;
    while(recvBuff[i] != ';') {
        nombreUsuario[e] = recvBuff[i];
        i++;
        e++;
    }
    nombreUsuario[e] = '\0';
    i++;
    e = 0;
    while(recvBuff[i] != ';') {
        contrasena[e] = recvBuff[i];
        i++;
        e++;
    }
    contrasena[e] = '\0';
    i++;
    e = 0;
    while(recvBuff[i] != ';') {
        email[e] = recvBuff[i];
        i++;
        e++;
    }
    email[e] = '\0';
    i++;
    e = 0;
    while(recvBuff[i] != ';') {
        telefono[e] = recvBuff[i];
        i++;
        e++;
    }
    telefono[e] = '\0';
    i++;
    e = 0;
    while(recvBuff[i] != ';') {
        fechaCreacion[e] = recvBuff[i];
        i++;
        e++;
    }
    fechaCreacion[e] = '\0';

    u->id = id[0] - '0';

    nombreU = u->nombre;
    u->nombre = nombreUsuario;
    u->contrasena = contrasena;
    u->email = email;
    u->telefono = telefono;
    u->fechaCreacion = fechaCreacion;

    return u;
}

// nombreExiste(const char *nombre): función que se encarga de decir si el nombre introducido ya ha sido usado por otra persona
// si es así devuelve 1, si no 0. Estafunción es usada en registro(Usuario *user) y en inicioSesion(Usuario *user) para comprobar 
// la posibilidad de usar el nombre/existencia del nombre introducido.
int nombreExiste(const char *nombre) {               // He usado const porque *nombre no se va a tocar
    char code[] = "NOMBREEXISTE:";

    char sendBuff[512], recvBuff[512];

	strcpy(sendBuff, strcat(code, nombre));
    strcat(sendBuff, ";");
	send(s, sendBuff, sizeof(sendBuff), 0);
	recv(s, recvBuff, sizeof(recvBuff), 0);
	return std::stoi(recvBuff);
}

// verificarCredenciales(const char *nombre, const char *base.dbcontrasena): función que se encarga de decir si existe un usuario con el 
// nombre y contraseña introducidos y en el caso de haberlo devuelve 1, sino 0. Esta función es llamada en inicioSesion(Usuario *user)
int verificarCredenciales(const char *nombre, const char *contrasena) {         // He usado const porque ni nombre ni contraseña se tocan
    char code[] = "VERIFICARCREDENCIALES:";
    char sendBuff[512], recvBuff[512];

	strcpy(sendBuff, strcat(code, nombre));
    strcat(sendBuff, ":");
    strcat(sendBuff, contrasena);
    strcat(sendBuff, ":");
	send(s, sendBuff, sizeof(sendBuff), 0);
	recv(s, recvBuff, sizeof(recvBuff), 0);
	return std::stoi(recvBuff);
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
        printf("%s   %s   %s   %s", user->nombre, user->contrasena, user->email, user->telefono);
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






