#include "sqlite3.h"
#include <stdio.h>
#include <unistd.h>
#include "apoyo.h"
#include "admin.h"
#include <winsock2.h>
#include "string.h"
#include <string.h>

extern SOCKET s;


// eliminar(int id, int n): función que recive dos int, el primero indicando el int de lo que quiere eliminar y el segundo de que tabla 
// siendo n == 6 para usuarios, n == 7 para discusiones y n == 8 para comentarios
void eliminar(int id, int n) {

    char sendBuff[512], recvBuff[512];

    char code[] = "ELIMINAR:";
    char cadena[20];
    char cadena2[20];
    sprintf(cadena, "%d", id);
    sprintf(cadena2, "%d", n);

    strcpy(sendBuff, code);
    strcat(sendBuff, cadena);
    strcat(sendBuff, ":");
    strcat(sendBuff, cadena2);    

	send(s, sendBuff, sizeof(sendBuff), 0);
}