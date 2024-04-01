#include "funciones2.h"
#include "structures.h"
#include <stdio.h>
#include <string.h>


// comentar(Usuario *user, Discusion *disc, Comentario *respuesta): función que a partir de un Usuario *user, una Discusion *disc y
// un Comentario *respuesta se encarga de solicitar por teclado el texto que albergará el comentario. Con todo esos datos genera una 
// estructura Comentario para guardarlo más tarde en la base de datos.
Comentario comentar(Usuario *user, Discusion *disc, Comentario *respuesta) {
    Comentario c1;
    c1.creador = user;
    c1.disc = disc;
    //c1.respuestaA = respuesta;
    char str[500];
    char texto[500]; // Almacena el contenido del comentario
    printf("Texto: \n");
	fflush(stdout);
	fgets(texto, sizeof(texto), stdin); // Escanea una cadena (%s) para el comentario

    c1.texto = strdup(texto);
    time_t tiempo_actual;
    time(&tiempo_actual);
    c1.fechaCreacion = tiempo_actual;



}


void AgregarNuevoComentario(Comentario *coment) {

    //AGREGAR EL COMENTARIO A LA BASE DE DATOS

}

void desplegarConversaciones() {

    //CODIGO PARA LEER LAS CONVERSACIONES DE LA BASE DE DATOS Y MOSTRARLAS


}
