/*
    * Luiz Eduardo Pereira
    * 0021619
    * 16/12/2016 (05:53)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "arvore.h"

/* O ARQUIVO DE SAÍDA ALTERA A ORDEM DAS PALAVRAS CHAVES, PORTANTO NÃO ESTARÁ NA MESMA 
 * ORDEM QUE A HASH E A ARVORE BINARIA DE BUSCA. MAS NÃO ALTERA O INDICE REMISSIVO. */

Raiz insere_palavrachave_arvore(Raiz raiz, char *diretorio) {
    FILE *arquivo;
    char palavra[33];
    int i;
    arquivo = fopen(diretorio, "r");
    while (fscanf(arquivo, "%s", palavra) != EOF) {
	for (i = 0; i < strlen(palavra); i++) {
            palavra[i] = tolower(palavra[i]);
	}
	raiz = insere_raiz(raiz, palavra);
    }
    fclose(arquivo);
    return(raiz);
}

void insere_pagina_lista(Raiz raiz, char *diretorio) {
    FILE *arquivo;
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
            insere_pagina(raiz, palavra, pagina);
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

/* Código retirado do site stackoverflow.com; */
int64_t calcula_tempo(struct timespec *timeA_p, struct timespec *timeB_p) {
    return (((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) - ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec));
}

int main(int argc, char *argv[]) {
    Raiz raiz = NULL;
    struct timespec inicio, final; /* Tempo; */
    char *palavra_chave = argv[1];
    char *texto = argv[2];
    char *saida = argv[3]; 
    
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    raiz = insere_palavrachave_arvore(raiz, palavra_chave);
    insere_pagina_lista(raiz, texto);
    escreve_arquivo(raiz, saida);
    destroi_arvore(raiz);
    
    clock_gettime(CLOCK_MONOTONIC, &final);
    
    printf("Tempo: %ld\n", (calcula_tempo(&final, &inicio) / 1000000)); /* dividido por 1.000.000 para sair resultado em milissegundos; */
    return(0);
}