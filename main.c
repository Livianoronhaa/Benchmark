#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarNumerosAleatorios(const char *nomeArquivo, int quantidade) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        perror("Erro ao criar o arquivo");
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

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    const char *nomeArquivo = "numeros_aleatorios.txt";
    int quantidade;
    printf("Informe a quantidade de números a serem gerados: ");
    scanf("%d", &quantidade);

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

    int alvo;
    int posicao;
    double duracao;

    int opcao;
    printf("Escolha o tipo de busca:\n");
    printf("1. Busca Linear\n");
    printf("2. Busca Sentinela\n");
    printf("3. Busca Binária\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            // Teste de busca linear
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
            // Teste de busca sentinela
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
            // Teste de busca binária
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

    free(numeros);

    return EXIT_SUCCESS;
}
