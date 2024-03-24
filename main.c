#include "stdio.h"
#include "structures.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int trueboolean = 1;
    char* nombreusuario = NULL;

        showMainMenu(nombreusuario);
        int seleccion;
        char numero[10];
        fgets(numero, 3, stdin);
        sscanf(numero," %c", &seleccion);
        if(seleccion = 1) {
            inicioSesionoRegistro();
        }



    




    //esto es una prueba
}