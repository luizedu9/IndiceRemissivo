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
    int altura;
    struct raiz *dir;
    struct raiz *esq;
    Lista indice; /* Lista com indice de palavras; */
};

/* Cria a raiz com uma palavra ja definida; */
Raiz cria_arvore(char *palavra) {
    Raiz raiz = (Raiz) malloc(sizeof(struct raiz));
    strcpy(raiz->palavra, palavra);
    raiz->altura = 1;
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

int altura_arvore(Raiz raiz) {
    if (raiz == NULL)
    	return(0);
    return(raiz->altura);
}

int maior_raiz(int raiz1, int raiz2) {
    if(raiz1 > raiz2)
	return raiz1;
    return raiz2;
}

Raiz direita_arvore(Raiz raiz) {
  Raiz raiz_e = raiz->esq;
  Raiz raiz_d = raiz_e->dir;
  raiz_e->dir = raiz;
  raiz->esq = raiz_d;
  raiz->altura = maior_raiz(altura_arvore(raiz->esq), altura_arvore(raiz->dir)) + 1;
  raiz_e->altura = maior_raiz(altura_arvore(raiz_e->esq), altura_arvore(raiz_e->dir)) + 1;
  return(raiz_e);
}

Raiz esquerda_arvore(Raiz raiz) {
  Raiz raiz_d = raiz->dir;
  Raiz raiz_e = raiz_d->esq;
  raiz_d->esq = raiz;
  raiz->dir = raiz_e;
  raiz->altura = maior_raiz(altura_arvore(raiz->esq), altura_arvore(raiz->dir)) + 1;
  raiz_d->altura = maior_raiz(altura_arvore(raiz_d->esq), altura_arvore(raiz_d->dir)) + 1;
  return(raiz_d);
}

int balanceada_arvore(Raiz raiz){
    if (raiz == NULL)
    	return(0);
    return(altura_arvore(raiz->esq) - altura_arvore(raiz->dir));
}

Raiz insere_raiz(Raiz raiz, char *palavra) {
    if (raiz == NULL){
    	raiz = cria_arvore(palavra);
	return(raiz);
    }
    if (strcmp(palavra, raiz->palavra) > 0) {
    	raiz->dir = insere_raiz(raiz->dir, palavra);
    }
    else {
	raiz->esq = insere_raiz(raiz->esq, palavra);
    }
    raiz->altura = 1 + maior_raiz(altura_arvore(raiz -> esq), altura_arvore(raiz -> dir));
    int balance = balanceada_arvore(raiz);
    /* LL; */
    if (balance > 1 && strcmp(palavra, raiz->esq->palavra) < 0)
	return(direita_arvore(raiz));
    /* RR; */
    if (balance < -1 && strcmp(palavra, raiz->dir->palavra) > 0)
	return(esquerda_arvore(raiz));
    /* LR; */
    if (balance > 1 && strcmp(palavra, raiz->esq->palavra) > 0) {
        raiz->esq = esquerda_arvore(raiz->esq);
        return(direita_arvore(raiz));
    }
    /* RL; */
    if (balance < -1 && strcmp(palavra, raiz->dir->palavra) < 0) {
	raiz -> dir = direita_arvore(raiz->dir);
        return(esquerda_arvore(raiz));
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