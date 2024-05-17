#include "structures.h"
#include "sqlite3.h"
#include "apoyo.h"
#include "anadirEstadisticas.h"
#include "publicarComentario.h"
#include "string.h"
#include <winsock2.h>
#include <string>
#include <stdio.h>

extern SOCKET s;

// comentar(Usuario *user, Discusion *disc, Comentario *respuesta): función que a partir de un Usuario *user, una Discusion *disc y
// un Comentario *respuesta se encarga de solicitar por teclado el texto que albergará el comentario. Con todo esos datos genera una 
// estructura Comentario para guardarlo más tarde en la base de datos.
void AgregarNuevoComentario(Comentario *coment) {
    char sendBuff[512], recvBuff[512];
    char code[] = "AGREGARNUEVOCOMENTARIO:";
	strcpy(sendBuff, strcat(code, coment->creador->nombre));
    strcat(sendBuff, ":");
    char str[20]; 
    snprintf(str, sizeof(str), "%d", coment->disc->id);
    strcat(sendBuff, str);
    strcat(sendBuff, ":");
    strcat(sendBuff, coment->texto);
	send(s, sendBuff, sizeof(sendBuff), 0);
}
// agregarstadistica(Comentario *com): función que reciviendo un puntero a un comentario lo añade al archivo de estadísticas
void agregarstadistica(Comentario *com) {
    FILE* fichero;
    fichero = fopen(obtenerLineaPorNumero(8), "a"); // a de "append" para añadir estadísticas al final

    if (fichero == NULL) {
        printf("Error al abrir el archivo de estadísticas.\n");
        return;
    }
    fprintf(fichero, "ID: %d | Texto: %s | Creador: %s | Discusión: %s | Fecha de creación: %s.\n",com->id, com->texto, com->creador->nombre, com->disc->nombre, com->fechaCreacion);
    fclose(fichero); 
}

// maxComentID(): función que devuelve el ultimo id asociado a un comentario de la base de datos + 1
int maxComentID() {
    char sendBuff[512], recvBuff[512];
    char code[] = "OBTENERIDMAXIMOCOM:";
	strcpy(sendBuff, strcat(code, " "));
	send(s, sendBuff, sizeof(sendBuff), 0);
	recv(s, recvBuff, sizeof(recvBuff), 0);
	return std::stoi(recvBuff);
}