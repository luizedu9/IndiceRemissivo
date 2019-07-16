/*
    * Luiz Eduardo Pereira
    * 0021619
    * 14/12/2016 
*/

#ifndef HASH_LISTA_H
#define HASH_LISTA_H

#include "lista.h"

typedef struct hash_lista *LHash;
typedef struct nodo *Nodo;

LHash cria_hash_lista(void);
void destroi_hash_lista(LHash P);
void insere_hash_lista(LHash P, char *palavra);
Nodo busca_hash_lista(LHash P, char *palavra);
Lista lista_indice(Nodo nodo);

#endif /* HASH_LISTA_H */