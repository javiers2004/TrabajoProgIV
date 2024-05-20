#include "structures.h"
#include "menuPrincipal.h"

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

SOCKET s;


int main(int argc, char *argv[]) {

    WSADATA wsaData;
	struct sockaddr_in server;

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

	// SEND and RECEIVE data


	// CLOSING the socket and cleaning Winsock...
	


    //CODIGO PARA EMPEZAR EL PROGRAMA
    Usuario *user1 = new Usuario();
    user1->nombre = NULL;  
    system("cls || clear");
    showMainMenu(user1);
    

    closesocket(s);
	WSACleanup();
    // crearBaseDeDatosUsuarios();
    // crearBaseDeDatosDiscusiones();
    // crearBaseDeDatosComentarios();
    // crearBaseDeDatosEstadisticas();
    return 0;
}