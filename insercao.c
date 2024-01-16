#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int chave;
} Item;

typedef struct
{
    char campo;
} Itemgrande;

void insercao(Item a[], int tamanho, int *comparacoes, int *atribuicoes)
{
    for (int i = 1; i < tamanho; i++)
    {
        int j = i;
        Item temp = a[i];
        (*atribuicoes)++;

        while (j > 0 && temp.chave < a[j - 1].chave)
        {
            (*comparacoes)++;
            a[j] = a[j - 1];
            (*atribuicoes)++;
            j--;
        }

        a[j] = temp;
        (*atribuicoes)++;
    }
}

void insercaoGrande(Itemgrande a[], int tamanho, int *comparacoes, int *atribuicoes)
{
    for (int i = 1; i < tamanho; i++)
    {
        int j = i;
        Itemgrande temp = a[i];
        (*atribuicoes)++;

        while (j > 0 && temp.campo < a[j - 1].campo)
        {
            (*comparacoes)++;
            a[j] = a[j - 1];
            (*atribuicoes)++;
            j--;
        }

        a[j] = temp;
        (*atribuicoes)++;
    }
}

void preencherVetor(Item a[], int tamanho)
{
    srand(12);

    for (int i = 0; i < tamanho; i++)
    {
        a[i].chave = rand();
    }
}

void preencherVetorcrescente(Item a[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        a[i].chave = i + 1;
    }
}

void preencherVetordecrescente(Item a[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        a[i].chave = tamanho - i;
    }
}

void preencherVetorgrande(Itemgrande a[], int tamanho)
{
    srand(12);

    for (int i = 0; i < tamanho; i++)
    {
        a[i].campo = 'A' + rand() % 26;
    }
}

void imprimirVetor(Item a[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d \n", a[i].chave);
    }
    printf("\n");
}

void imprimirVetorgrande(Itemgrande a[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("%c \n", a[i].campo);
    }
    printf("\n");
}

double calcularTempo(clock_t inicio, clock_t fim)
{
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

int main()
{
    int tamanho;
    int opcao;
    int comparacoes = 0;
    int atribuicoes = 0;

    /*printf("Selecione qual tipo de registro:\n");
    printf("~1~ Registro pequeno (tipo int)\n");
    printf("~2~ Registro grande (tipo char)\n");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
    {*/
        printf("Digite o tamanho do vetor: ");
        scanf("%d", &tamanho);

        Item *vetor = malloc(tamanho * sizeof(Item));

        preencherVetordecrescente(vetor, tamanho);

        //printf("Vetor não ordenado:\n");

        //imprimirVetor(vetor, tamanho);

        clock_t inicio = clock();
        insercao(vetor, tamanho, &comparacoes, &atribuicoes);
        clock_t fim = clock();

       // printf("Vetor ordenado:\n");

        //imprimirVetor(vetor, tamanho);

        printf("\n");
        printf("Número de comparações: %d\n", comparacoes);
        printf("Número de atribuições: %d\n", atribuicoes);
        printf("Tempo de execução: %.10f segundos\n", calcularTempo(inicio, fim));

        free(vetor);

        return 0;
}
    /*
    }
    case 2:
    {
        printf("Digite o tamanho do vetor: ");
        scanf("%d", &tamanho);

        Itemgrande *vetorgrande = malloc(tamanho * sizeof(Itemgrande));

        preencherVetorgrande(vetorgrande, tamanho);

        printf("Vetor não ordenado:\n");
        imprimirVetorgrande(vetorgrande, tamanho);
        int comparacoes = 0;
        int atribuicoes = 0;

        clock_t inicio = clock();
        insercaoGrande(vetorgrande, tamanho, &comparacoes, &atribuicoes);
        clock_t fim = clock();

        printf("Vetor ordenado:\n");
        imprimirVetorgrande(vetorgrande, tamanho);

        printf("\n");
        printf("Número de comparações: %d\n", comparacoes);
        printf("Número de atribuições: %d\n", atribuicoes);
        printf("Tempo de execução: %.10f segundos\n", calcularTempo(inicio, fim));

        free(vetorgrande);

        return 0;

    }
    }
}*/
/*int main()
{
    int tamanho;
    int opcao;
    int comparacoes = 0;
    int atribuicoes = 0;

    while (1) {
        printf("Digite o tamanho do vetor: ");
        scanf("%d", &tamanho);

        Item *vetor = malloc(tamanho * sizeof(Item));

        preencherVetor(vetor, tamanho);

        for (int seed = 12; seed <= 21; seed++)
        {
            srand(seed);

            printf("=== Executando com srand(%d) ===\n", seed);

            //printf("Vetor não ordenado:\n");
            //imprimirVetor(vetor, tamanho);

            clock_t inicio = clock();
            insercao(vetor, tamanho, &comparacoes, &atribuicoes);
            clock_t fim = clock();

            //printf("Vetor ordenado:\n");
            //imprimirVetor(vetor, tamanho);

            printf("\n");
            printf("Número de comparações: %d\n", comparacoes);
            printf("Número de atribuições: %d\n", atribuicoes);
            printf("Tempo de execução: %.10f segundos\n", calcularTempo(inicio, fim));

            // Resetando o vetor para ser ordenado novamente
            preencherVetor(vetor, tamanho);
            comparacoes = 0;
            atribuicoes = 0;
        }

        free(vetor);

        printf("Deseja encerrar o programa? (S/N): ");
        char resposta;
        scanf(" %c", &resposta);
        if (resposta == 'S' || resposta == 's') {
            break;
        }
    }

    return 0;
}*/
