
#include "biblioteca.h"
#include <stdlib.h>
#include <time.h>


void gerarNumerosAleatorios(const char *nomeArquivo, int quantidade) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        fprintf(stderr, "Erro ao criar o arquivo %s\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < quantidade; ++i) {
        fprintf(arquivo, "%d ", rand() % 1000 + 1);
    }

    fclose(arquivo);
}

int buscaLinear(const int *numeros, int tamanho, int alvo, double *duracao) {
    clock_t inicio = clock();
    for (int i = 0; i < tamanho; ++i) {
        if (numeros[i] == alvo) {
            *duracao = ((double)(clock() - inicio)) / CLOCKS_PER_SEC;
            return i;
        }
    }
    *duracao = ((double)(clock() - inicio)) / CLOCKS_PER_SEC;
    return -1;
}

int buscaSentinela(int *numeros, int tamanho, int alvo, double *duracao) {
    clock_t inicio = clock();
    int ultimo = numeros[tamanho - 1];
    numeros[tamanho - 1] = alvo;

    int i = 0;
    while (numeros[i] != alvo) {
        ++i;
    }

    numeros[tamanho - 1] = ultimo;

    if (i < tamanho - 1 || numeros[tamanho - 1] == alvo) {
        *duracao = ((double)(clock() - inicio)) / CLOCKS_PER_SEC;
        return i;
    } else {
        *duracao = ((double)(clock() - inicio)) / CLOCKS_PER_SEC;
        return -1;
    }
}

int buscaBinaria(const int *numeros, int tamanho, int alvo, double *duracao) {
    clock_t inicio = clock();
    int baixo = 0, alto = tamanho - 1;

    while (baixo <= alto) {
        int meio = baixo + (alto - baixo) / 2;
        if (numeros[meio] == alvo) {
            *duracao = ((double)(clock() - inicio)) / CLOCKS_PER_SEC;
            return meio;
        } else if (numeros[meio] < alvo) {
            baixo = meio + 1;
        } else {
            alto = meio - 1;
        }
    }

    *duracao = ((double)(clock() - inicio)) / CLOCKS_PER_SEC;
    return -1;
}

 //Função usada como argumento para a função 'qsort'.
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}