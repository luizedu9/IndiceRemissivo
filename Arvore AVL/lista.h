/*
    * Luiz Eduardo Pereira
    * 0021619
    * 16/12/2016 
*/

#ifndef LISTA_H
#define LISTA_H

typedef enum {
    FALSE, TRUE
} boolean;

typedef struct lista *Lista;

Lista cria_lista(void);
void destroi_lista(Lista P);
boolean vazia_lista(Lista P);
void insere_lista(Lista P, int valor);
int busca_lista(Lista P, int pos);
void escreve_arquivo_lista(Lista P, char *diretorio, char *palavra);

#endif /* LISTA_H */