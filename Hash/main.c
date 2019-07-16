/*
    * Luiz Eduardo Pereira
    * 0021619
    * 14/12/2016 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "hash.h"

int tamanho_hash(char *diretorio) {
    FILE *arquivo;
    int tamanho = 0;
    char palavra[33];
    arquivo = fopen(diretorio, "r");
    while (fscanf(arquivo, "%s", palavra) != EOF) { /* Palavras-Chaves = Número de linhas; */
        tamanho++;
    }	
    fclose(arquivo);
    return(tamanho);
}

char **insere_palavrachave_hash(Hash hash, char *diretorio, int tamanho) { /* Retorna um vetor com as palavras chaves; */
    FILE *arquivo;
    char palavra[33];
    char **palavras;
    int i, posicao = 0;
    palavras = (char**) malloc(tamanho * sizeof(char*)); /* Guarda as palavras em um vetor; */
    arquivo = fopen(diretorio, "r");
    while (fscanf(arquivo, "%s", palavra) != EOF) {
	for (i = 0; i < strlen(palavra); i++) {
            palavra[i] = tolower(palavra[i]); /* Deixa tudo minusculo; */
	}
        insere_palavra_hash(hash, palavra, tamanho);
        palavras[posicao] = (char*) malloc(strlen(palavra) * sizeof(char));
	strcpy(palavras[posicao], palavra);
	posicao++;
    } 
    fclose(arquivo);
    return(palavras);
}

void insere_pagina_lista(Hash hash, char *diretorio, int tamanho) {
    FILE *arquivo;
    Nodo nodo = NULL;
    char palavra[33];
    char letra;
    int pagina = 1, posicao = 0;
    arquivo = fopen(diretorio, "r");
    while (fscanf(arquivo, "%c", &letra) != EOF) {
    	if (isalpha(letra)) { /* Verifica se é uma letra; */ 
            letra = tolower(letra);
            palavra[posicao] = letra;
            posicao++;
	}
        else if (posicao > 3) { /* Se palavra for maior que 3, então é uma palavra valida; */
            palavra[posicao] = '\0';
            posicao = 0;
            nodo = busca_palavra_hash(hash, palavra, tamanho); /* Verifica se existe palavra-chave correspondente; */
            if (nodo != NULL){
		insere_pagina(hash, palavra, pagina, tamanho); /* Se sim, insere o indice na lista da palavra; */
            }
	}
	if (letra == ' ') { /* Reinicia busca;*/
            posicao = 0;
	}
	if (letra == '\n') { /* Reinicia busca e pula para proxima pagina; */
            pagina++;
            posicao = 0;
	}
    }
    fclose(arquivo);
    return;
}

void escreve_palavra_pagina(Hash hash, char *diretorio_entrada, char *diretorio_saida, char **palavras, int tamanho){
    int i;
    for (i = 0; i < tamanho; i++) {
        escreve_arquivo(hash, palavras[i], tamanho, diretorio_saida);
        free(palavras[i]);
    }
    free(palavras);	
    return;
}

/* Código retirado do site stackoverflow.com; */
int64_t calcula_tempo(struct timespec *timeA_p, struct timespec *timeB_p) {
    return (((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) - ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec));
}

int main(int argc, char *argv[]) {
    Hash hash; 
    struct timespec inicio, final; /* Tempo; */
    int tamanho;
    char *palavra_chave = argv[1];
    char *texto = argv[2];
    char *saida = argv[3];    
    char **palavras;
    
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    
    tamanho = tamanho_hash(palavra_chave); /* Pega a quantidade de palavras chaves; */
    hash = cria_hash(tamanho); 
    palavras = insere_palavrachave_hash(hash, palavra_chave, tamanho); /* Insere as palavras chaves na hash; */
    insere_pagina_lista(hash, texto, tamanho); /* Preenche o indice de paginas de cada palavra chave; */
    escreve_palavra_pagina(hash, palavra_chave, saida, palavras, tamanho); /* Escreve saída; */
    destroi_hash(hash, tamanho);
    
    clock_gettime(CLOCK_MONOTONIC, &final);
    
    printf("Tempo: %ld\n", (calcula_tempo(&final, &inicio) / 1000000)); /* dividido por 1.000.000 para sair resultado em milissegundos; */
    return(0);
}