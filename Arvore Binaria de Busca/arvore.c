/*
    * Luiz Eduardo Pereira
    * 0021619
    * 16/12/2016 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"

struct raiz {
    char palavra[33];
    struct raiz *dir;
    struct raiz *esq;
    Lista indice; /* Lista com indice de palavras; */
};

/* Cria a raiz com uma palavra ja definida; */
Raiz cria_arvore(char *palavra) {
    Raiz raiz = (Raiz) malloc(sizeof(struct raiz));
    strcpy(raiz->palavra, palavra);
    raiz->dir = NULL;
    raiz->esq = NULL;
    raiz->indice = cria_lista();
    return(raiz);
}

void destroi_arvore(Raiz raiz){
    if (raiz == NULL) {
    	return;
    }
    destroi_arvore(raiz->esq);
    destroi_arvore(raiz->dir);
    free(raiz);
    raiz = NULL;
    return;
}

Raiz insere_raiz(Raiz raiz, char *palavra) {
    if (raiz == NULL){
	raiz = cria_arvore(palavra);
	return(raiz);
    }
    if (strcmp(raiz->palavra, palavra) < 0) { /* Se palavra é menor que raiz, vai para a esquerda; */
    	raiz->esq = insere_raiz(raiz->esq, palavra);
    }
    else {
        raiz->dir = insere_raiz(raiz->dir, palavra);
    }
    return(raiz);
}

void insere_pagina(Raiz raiz, char *palavra, int pagina){
    if (raiz == NULL) {
	return;
    }
    if (strcmp(palavra, raiz->palavra) == 0) { /* Busca palavra e insere indice na lista; */ 
    	insere_lista(raiz->indice, pagina);
    	return;
    }
    insere_pagina(raiz->esq, palavra, pagina);
    insere_pagina(raiz->dir, palavra, pagina);
}

void escreve_arquivo(Raiz raiz, char *diretorio) {
    if (raiz == NULL){
    	return;
    }
    escreve_arquivo(raiz->esq, diretorio);
    escreve_arquivo_lista(raiz->indice, diretorio, raiz->palavra);
    escreve_arquivo(raiz->dir, diretorio);
}