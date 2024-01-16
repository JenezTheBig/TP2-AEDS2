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

void merge(Item a[], int inicio, int meio, int fim, Item aux[], long int *comparacoes, long int *atribuicoes)
{
    int i = inicio;
    int j = meio + 1;
    int k = 0;

    while (i <= meio && j <= fim)
    {
        (*comparacoes)++;
        if (a[i].chave <= a[j].chave)
        {
            aux[k++] = a[i++];
            (*atribuicoes)++;
        }
        else
        {
            aux[k++] = a[j++];
            (*atribuicoes)++;
        }
    }

    while (i <= meio)
    {
        aux[k++] = a[i++];
        (*atribuicoes)++;
    }

    while (j <= fim)
    {
        aux[k++] = a[j++];
        (*atribuicoes)++;
    }

    for (i = inicio, k = 0; i <= fim; i++, k++)
    {
        a[i] = aux[k];
        (*atribuicoes)++;
    }
}

void mergesort(Item a[], int inicio, int fim, Item aux[], long int *comparacoes, long int *atribuicoes)
{
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;

        mergesort(a, inicio, meio, aux, comparacoes, atribuicoes);
        mergesort(a, meio + 1, fim, aux, comparacoes, atribuicoes);

        merge(a, inicio, meio, fim, aux, comparacoes, atribuicoes);
    }
}

void mergeGrande(Itemgrande a[], int inicio, int meio, int fim, Itemgrande aux[], long int *comparacoes, long int *atribuicoes)
{
    int i = inicio;
    int j = meio + 1;
    int k = 0;

    while (i <= meio && j <= fim)
    {
        (*comparacoes)++;
        if (a[i].campo <= a[j].campo)
        {
            aux[k++] = a[i++];
            (*atribuicoes)++;
        }
        else
        {
            aux[k++] = a[j++];
            (*atribuicoes)++;
        }
    }

    while (i <= meio)
    {
        aux[k++] = a[i++];
        (*atribuicoes)++;
    }

    while (j <= fim)
    {
        aux[k++] = a[j++];
        (*atribuicoes)++;
    }

    for (i = inicio, k = 0; i <= fim; i++, k++)
    {
        a[i] = aux[k];
    }
}

void mergesortGrande(Itemgrande a[], int inicio, int fim, Itemgrande aux[], long int *comparacoes, long int *atribuicoes)
{
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;

        mergesortGrande(a, inicio, meio, aux, comparacoes, atribuicoes);
        mergesortGrande(a, meio + 1, fim, aux, comparacoes, atribuicoes);

        mergeGrande(a, inicio, meio, fim, aux, comparacoes, atribuicoes);
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

    printf("Selecione qual tipo de registro:\n");
    printf("~1~ Registro pequeno (tipo int)\n");
    printf("~2~ Registro grande (tipo char)\n");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
    {
        printf("Digite o tamanho do vetor: ");
        scanf("%d", &tamanho);

        Item *vetor = malloc(tamanho * sizeof(Item));
        Item *auxiliar = malloc(tamanho * sizeof(Item));

        long int comparacoes = 0;
        long int atribuicoes = 0;

        preencherVetorcrescente(vetor, tamanho);

        printf("Vetor não ordenado:\n");
        imprimirVetor(vetor, tamanho);

        clock_t inicio = clock();
        mergesort(vetor, 0, tamanho - 1, auxiliar, &comparacoes, &atribuicoes);
        clock_t fim = clock();

        printf("Vetor ordenado:\n");
        imprimirVetor(vetor, tamanho);

        printf("Número de comparações: %ld\n", comparacoes);
        printf("Número de atribuições: %ld\n", atribuicoes);
        printf("Tempo de execução: %.10lf segundos\n", calcularTempo(inicio, fim));
        free(vetor);
        break;
    }
    case 2:
    {
        printf("Digite o tamanho do vetor: ");
        scanf("%d", &tamanho);

        Itemgrande *vetorgrande = malloc(tamanho * sizeof(Itemgrande));
        Itemgrande *auxiliar = malloc(tamanho * sizeof(Itemgrande));
        long int comparacoes = 0;
        long int atribuicoes = 0;

        preencherVetorgrande(vetorgrande, tamanho);

        printf("Vetor não ordenado:\n");
        imprimirVetorgrande(vetorgrande, tamanho);

        clock_t inicio = clock();
        mergesortGrande(vetorgrande, 0, tamanho - 1, auxiliar, &comparacoes, &atribuicoes);
        clock_t fim = clock();

        printf("Vetor ordenado:\n");
        imprimirVetorgrande(vetorgrande, tamanho);

        printf("Número de comparações: %ld\n", comparacoes);
        printf("Número de atribuições: %ld\n", atribuicoes);
        printf("Tempo de execução: %.10lf segundos\n", calcularTempo(inicio, fim));

        free(vetorgrande);
    }
    }
}

