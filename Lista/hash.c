/*
    * Luiz Eduardo Pereira
    * 0021619
    * 14/12/2016 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "hash_lista.h"

Hash cria_hash() {
    Hash P;
    P = (Hash) malloc(sizeof(LHash));
    P[0] = cria_hash_lista();
    return(P);
}

void destroi_hash(Hash P){
    destroi_hash_lista(P[0]);
    free(P);
    P = NULL;
    return;
}

void insere_palavra_hash (Hash P, char *palavra) {
    insere_hash_lista(P[0], palavra);
    return;
}

Nodo busca_palavra_hash(Hash P, char *palavra) {
    Nodo nodo;
    nodo = busca_hash_lista(P[0], palavra);
    return(nodo);
}

void insere_pagina(Hash P, char *palavra, int pagina){
    Lista L;
    Nodo nodo;
    nodo = busca_hash_lista(P[0], palavra);
    L = lista_indice(nodo);
    insere_lista(L, pagina);
    return;
}

void escreve_arquivo(Hash P, char *palavra, char *diretorio) {
    Nodo nodo;
    nodo = busca_hash_lista(P[0], palavra);
    escreve_arquivo_lista(lista_indice(nodo), diretorio, palavra);
}