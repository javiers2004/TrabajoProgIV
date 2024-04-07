#ifndef _FUNCIONES_6_H_
#define _FUNCIONES_6_H_
#include "structures.h"
typedef struct {
    char creator[50];
    int comment_count;
} CommentCounter;

void contarComentariosPorUsuario(Usuario user, const char *filename);
void anadirEst(Usuario user);
#endif /* CONTADOR_COMENTARIOS_H */

