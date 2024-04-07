#ifndef _FUNCIONES_6_H_
#define _FUNCIONES_6_H_

typedef struct {
    char creator[50];
    int comment_count;
} CommentCounter;

void contarComentariosPorUsuario(const char *filename);

#endif /* CONTADOR_COMENTARIOS_H */

