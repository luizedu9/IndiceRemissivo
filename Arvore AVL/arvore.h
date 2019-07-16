/*
    * Luiz Eduardo Pereira
    * 0021619
    * 16/12/2016 
*/

#ifndef ARVORE_H
#define ARVORE_H

typedef struct raiz *Raiz;

Raiz cria_arvore(char *palavra);
void destroi_arvore(Raiz raiz);
Raiz insere_raiz(Raiz raiz, char *palavra);
void insere_pagina(Raiz raiz, char *palavra, int pagina);
void escreve_arquivo(Raiz raiz, char *diretorio);

#endif /* ARVORE_H */