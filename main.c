#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerar_numeros_aleatorios(const char *nome_arquivo, int quantidade) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    clock_t tempo_inicial_geracao = clock();

    for (int i = 0; i < quantidade; ++i) {
        fprintf(arquivo, "%d ", rand() % 100 + 1);
    }

    clock_t tempo_final_geracao = clock();
    printf("Tempo de geração e salvamento: %f segundos\n", (double)(tempo_final_geracao - tempo_inicial_geracao) / CLOCKS_PER_SEC);

    fclose(arquivo);
}

void busca_linear(const int *numeros, int tamanho, int alvo) {
    clock_t tempo_inicial = clock();
    for (int i = 0; i < tamanho; ++i) {
        if (numeros[i] == alvo) {
            clock_t tempo_final = clock();
            printf("Busca Linear: Índice %d - Tempo decorrido: %f segundos\n", i, (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC);
            return;
        }
    }

    printf("Busca Linear: Elemento não encontrado\n");
}

void busca_sentinela(const int *numeros, int tamanho, int alvo) {
    int *temp_numeros = malloc((tamanho + 1) * sizeof(int));
    if (temp_numeros == NULL) {
        perror("Erro de alocação de memória");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < tamanho; ++i) {
        temp_numeros[i] = numeros[i];
    }
    temp_numeros[tamanho] = alvo;

    int i = 0;
    while (temp_numeros[i] != alvo) {
        ++i;
    }

    free(temp_numeros);

    if (i < tamanho) {
        printf("Busca Sentinela: Índice %d\n", i);
    } else {
        printf("Busca Sentinela: Elemento não encontrado\n");
    }
}

void busca_binaria(int *numeros, int tamanho, int alvo) {
    clock_t tempo_inicial = clock();

    // Ordena o array para busca binária
    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = 0; j < tamanho - i - 1; ++j) {
            if (numeros[j] > numeros[j + 1]) {
                // troca numeros[j] e numeros[j+1]
                int temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
            }
        }
    }

    int baixo = 0, alto = tamanho - 1;
    while (baixo <= alto) {
        int meio = (baixo + alto) / 2;
        if (numeros[meio] == alvo) {
            clock_t tempo_final = clock();
            printf("Busca Binária: Índice %d - Tempo decorrido: %f segundos\n", meio, (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC);
            return;
        } else if (numeros[meio] < alvo) {
            baixo = meio + 1;
        } else {
            alto = meio - 1;
        }
    }

    printf("Busca Binária: Elemento não encontrado\n");
}

void imprimir_array(const int *numeros, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        printf("%d ", numeros[i]);
    }
    printf("\n");
}

int main() {
    const char *nome_arquivo = "numeros_aleatorios.txt";
    int quantidade;

    printf("Digite a quantidade de números aleatórios a serem gerados: ");
    scanf("%d", &quantidade);

    gerar_numeros_aleatorios(nome_arquivo, quantidade);

    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int *numeros = malloc(quantidade * sizeof(int));
    if (numeros == NULL) {
        perror("Erro de alocação de memória");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < quantidade; ++i) {
        fscanf(arquivo, "%d", &numeros[i]);
    }

    fclose(arquivo);

    int escolha, alvo;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Busca Linear\n");
        printf("2. Busca Sentinela\n");
        printf("3. Busca Binária\n");
        printf("4. Sair\n");

        printf("Digite sua escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o número a ser buscado: ");
                scanf("%d", &alvo);
                busca_linear(numeros, quantidade, alvo);
                break;

            case 2:
                printf("Digite o número a ser buscado: ");
                scanf("%d", &alvo);
                busca_sentinela(numeros, quantidade, alvo);
                break;

            case 3:
                printf("Digite o número a ser buscado: ");
                scanf("%d", &alvo);
                busca_binaria(numeros, quantidade, alvo);
                break;

            case 4:
                free(numeros);
                return 0;

            default:
                printf("Escolha inválida. Por favor, tente novamente.\n");
        }
    }

    free(numeros);
    return 0;
}

