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

/* Proporção da tabela = 50% (Dica de alunos) do quantidade original de palavras; */
#define PROPORCAO 2

/* tamanho = número de palavras; */
Hash cria_hash(int tamanho) {
    Hash P;
    int i;
    P = (Hash) malloc(((int)(tamanho / PROPORCAO)) * sizeof(LHash));
    for (i = 0; i < ((int)(tamanho / PROPORCAO)); i++) { 
        P[i] = cria_hash_lista();
    }
    return(P);
}

void destroi_hash(Hash P, int tamanho){
    int i;
    for (i = 0; i < ((int)(tamanho / PROPORCAO)); i++){
    	destroi_hash_lista(P[i]);
    }
    free(P);
    P = NULL;
    return;
}

int funcao_hash(int string_inteiro, int tamanho) {
    return(string_inteiro % ((int)(tamanho / PROPORCAO))); /* Utiliza um numero inteiro equivalente a string mod a proporção da hash; */
}

int converte_string_inteiro(char *palavra) { /* Transforma a string em um número inteiro (Dica de alunos); */
    int i, tamanho, string_inteiro = 0;
    tamanho = strlen(palavra);
    for (i = 0; i < tamanho; i++) {
        string_inteiro = (1.7 * string_inteiro) + ((int) palavra[i]);
    }
    return(string_inteiro);
}

void insere_palavra_hash (Hash P, char *palavra, int tamanho) {
    int i;
    i = funcao_hash(converte_string_inteiro(palavra), tamanho);
    insere_hash_lista(P[i], palavra);
    return;
}

Nodo busca_palavra_hash(Hash P, char *palavra, int tamanho) {
    Nodo nodo;
    int i;
    i = funcao_hash(converte_string_inteiro(palavra), tamanho); /* Encontra posição onde palavra está; */
    nodo = busca_hash_lista(P[i], palavra);
    return(nodo);
}

void insere_pagina(Hash P, char *palavra, int pagina, int tamanho){
    Lista L;
    Nodo nodo;
    int i;
    i = funcao_hash(converte_string_inteiro(palavra), tamanho);
    nodo = busca_hash_lista(P[i], palavra);
    L = lista_indice(nodo);
    insere_lista(L, pagina);
    return;
}

void escreve_arquivo(Hash P, char *palavra, int tamanho, char *diretorio) {
    Nodo nodo;
    int i;
    i = funcao_hash(converte_string_inteiro(palavra), tamanho);
    nodo = busca_hash_lista(P[i], palavra);
    escreve_arquivo_lista(lista_indice(nodo), diretorio, palavra);
}