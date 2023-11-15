#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "biblioteca.h"

int main() {
    const char *nomeArquivo = "numeros_aleatorios.txt";
    int quantidade;

   do {
        printf("Informe a quantidade de números a serem gerados (positivos): ");
        scanf("%d", &quantidade);

        if (quantidade < 0) {
            printf("A quantidade de números deve ser positiva. Tente novamente.\n");
        }

    } while (quantidade < 0);

    gerarNumerosAleatorios(nomeArquivo, quantidade);

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    int *numeros = malloc(quantidade * sizeof(int));
    for (int i = 0; i < quantidade; ++i) {
        fscanf(arquivo, "%d", &numeros[i]);
    }
    fclose(arquivo);
int opcao;

    do {
        printf("Escolha o tipo de busca:\n");
        printf("1. Busca Linear\n");
        printf("2. Busca Sentinela\n");
        printf("3. Busca Binária\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);

        if (opcao == 0) {
            break; // Sai do loop se o usuário escolher sair
        }

        executarAlgoritmoBusca(opcao, numeros, quantidade);

    } while (1); // Loop infinito até que o usuário escolha sair

        free(numeros);

        return EXIT_SUCCESS;
}

void executarAlgoritmoBusca(int opcao, int *numeros, int quantidade) {
    int alvo;
    int posicao;
    double duracao;

     switch (opcao) {
        case 1:
            printf("Informe o número a ser buscado: ");
            scanf("%d", &alvo);
            posicao = buscaLinear(numeros, quantidade, alvo, &duracao);
            if (posicao != -1) {
                printf("Número encontrado na posição %d (busca linear). Tempo = %lf segundos\n", posicao, duracao);
            } else {
                printf("Número não encontrado (busca linear). Tempo = %lf segundos\n", duracao);
            }
            break;
        case 2:
            printf("Informe o número a ser buscado: ");
            scanf("%d", &alvo);
            posicao = buscaSentinela(numeros, quantidade, alvo, &duracao);
            if (posicao != -1) {
                printf("Número encontrado na posição %d (busca sentinela). Tempo = %lf segundos\n", posicao, duracao);
            } else {
                printf("Número não encontrado (busca sentinela). Tempo = %lf segundos\n", duracao);
            }
            break;
        case 3:
            printf("Informe o número a ser buscado: ");
            scanf("%d", &alvo);
            int *numerosOrdenados = malloc(quantidade * sizeof(int));
            for (int i = 0; i < quantidade; ++i) {
                numerosOrdenados[i] = numeros[i];
            }
            qsort(numerosOrdenados, quantidade, sizeof(int), compare);
            posicao = buscaBinaria(numerosOrdenados, quantidade, alvo, &duracao);
            if (posicao != -1) {
                printf("Número encontrado na posição %d (busca binária). Tempo = %lf segundos\n", posicao, duracao);
            } else {
                printf("Número não encontrado (busca binária). Tempo = %lf segundos\n", duracao);
            }
            free(numerosOrdenados);
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
}
