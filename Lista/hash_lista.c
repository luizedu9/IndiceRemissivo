/*
    * Luiz Eduardo Pereira
    * 0021619
    * 14/12/2016 
*/

#include <stdlib.h>
#include <string.h>
#include "hash_lista.h"

struct hash_lista {
    int tamanho;
    struct nodo *inicio;
};

struct nodo {
    char palavra[33]; /* 32 caracteres + "\0"; */
    Lista lista;
    struct nodo *proximo;
};
typedef struct nodo *Nodo;

LHash cria_hash_lista(void) {
    LHash P;
    P = (LHash) malloc(sizeof(struct hash_lista));
    P->inicio = NULL;
    return(P);
}

void destroi_hash_lista(LHash P) {
    Nodo aux1, aux2;
    aux1 = P->inicio;
    while (aux1 != NULL) {
	if (aux1->lista != NULL && !vazia_lista(aux1->lista))
            destroi_lista(aux1->lista);
            aux2 = aux1->proximo;
            free(aux1);
            aux1 = aux2;
	}
    free(P);
    P = NULL;
    return;
}

void insere_hash_lista(LHash P, char *palavra) {
    Nodo nodo, aux;
    nodo = (Nodo) malloc(sizeof(struct nodo));
    nodo->lista = cria_lista();
    strcpy(nodo->palavra, palavra);
    nodo->proximo = NULL;
    /* Caso inicial; */
    if (P->inicio == NULL) {
    	P->inicio = nodo;
	return;
    }
    aux = P->inicio;
    while (aux->proximo != NULL) {
        aux = aux->proximo;
    }
    aux->proximo = nodo;
    return;
}

Nodo busca_hash_lista(LHash P, char *palavra) {
    Nodo aux;
    aux = P->inicio;
    while (aux != NULL) {
	if (strcmp(palavra, aux->palavra) == 0) {
            return(aux);
	}
	aux = aux->proximo;
    }
    return(NULL);
}

/* Retorna a lista que contém o indice remissivo de uma palavra; */
Lista lista_indice(Nodo nodo) {
    return(nodo->lista);
}