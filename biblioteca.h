#define BIBLIOTECA_H

#include <stdio.h>

void gerarNumerosAleatorios(const char *nomeArquivo, int quantidade);
int buscaLinear(const int *numeros, int tamanho, int alvo, double *duracao);
int buscaSentinela(int *numeros, int tamanho, int alvo, double *duracao);
int buscaBinaria(const int *numeros, int tamanho, int alvo, double *duracao);
int compare(const void *a, const void *b);
void executarAlgoritmoBusca(int opcao, int *numeros, int quantidade);