/*
    * Luiz Eduardo Pereira
    * 0021619
    * 14/12/2016 
*/

#ifndef HASH_H
#define HASH_H

#include "hash_lista.h"

typedef LHash *Hash;

Hash cria_hash(int tamanho);
void destroi_hash(Hash P, int tamanho);
int funcao_hash(int string_inteiro, int tamanho);
int converte_string_inteiro(char *palavra);
void insere_palavra_hash(Hash P, char *palavra, int tamanho);
Nodo busca_palavra_hash(Hash P,char *palavra, int tamanho);
void insere_pagina(Hash P, char *palavra, int pagina, int tamanho);
void escreve_arquivo(Hash P, char *palavra, int tamanho, char *diretorio);

#endif /* HASH_H */