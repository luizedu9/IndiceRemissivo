/*
    * Luiz Eduardo Pereira
    * 0021619
    * 14/12/2016 
*/

#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

struct lista {
    int tamanho;
    struct nodo *inicio;
};
typedef struct nodo *Nodo;

struct nodo {
    int valor;
    struct nodo *proximo;
};

Lista cria_lista(void) {
    Lista P;
    P = (Lista) malloc(sizeof(struct lista));
    P->inicio = NULL;
    P->tamanho = 0;
    return(P);
}

void destroi_lista(Lista P) {
    Nodo aux1, aux2;
    aux1 = P->inicio;
    while(aux1 != NULL) {
        aux2 = aux1->proximo;
        free(aux1);
        aux1 = aux2;
    }
    free(P);
    P = NULL;
    return;		
}

boolean vazia_lista(Lista P) {
    if (P->tamanho == 0) {
        return(TRUE);
    }
    return(FALSE);
}

void insere_lista(Lista P, int valor) {
    Nodo nodo, aux;
    P->tamanho++;
    nodo = (Nodo) malloc(sizeof(struct nodo));
    nodo->valor = valor;
    nodo->proximo = NULL;
    /* Caso Inicial, nodo inexistente; */
    if (P->inicio == NULL) {
        P->inicio = nodo;
        return;
    }
    /* Outros; */
    aux = P->inicio;
    while (aux->proximo != NULL) {
        aux = aux->proximo;
    }
    aux->proximo = nodo;
    return;
}

int busca_lista(Lista P, int pos) { /* pos é indexado de 0; */
    Nodo aux;
    int i;
    if (pos == P->tamanho) { /* Se pos = tamanho, então passou da ultima posição; */
        return(0);
    }
    /* Caso inicial, posição 0; */
    aux = P->inicio;
    if (pos == 0) {
        return(aux->valor);
    }
    /* Outros; */
    aux = aux->proximo;
    i = 1;
    while (aux != NULL) {
        if (pos == i) {
            return(aux->valor);
        }
        aux = aux->proximo;
    }
    return(0);
}

void escreve_arquivo_lista(Lista P, char *diretorio, char *palavra) {
    Nodo aux;
    FILE *arquivo;
    int i;
    arquivo = fopen(diretorio, "a");
    fprintf(arquivo, "%s", palavra);
    aux = P->inicio;
    i = 1;
    while (aux != NULL) {
        fprintf(arquivo, " - %d", aux->valor);
	aux = aux->proximo;
        i++;
    }
    fprintf(arquivo, "\n");
    fclose(arquivo);
    return;
}