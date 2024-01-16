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

void shellsort(Item a[], int tamanho, int *comparacoes, int *atribui)
{
    int h = 1;
    while (h < tamanho / 3)
    {
        h = 3 * h + 1;
    }

    while (h >= 1)
    {
        for (int i = h; i < tamanho; i++)
        {
            int j = i;
            Item temp = a[i];
            (*atribui)++;

            while (j >= h && temp.chave < a[j - h].chave)
            {
                (*comparacoes)++;
                a[j] = a[j - h];
                (*atribui)++;
                j -= h;
            }

            a[j] = temp;
            (*atribui)++;
        }

        h /= 3;
    }
}

void shellsortGrande(Itemgrande a[], int tamanho, int *comparacoes, int *atribui)
{
    int h = 1;
    while (h < tamanho / 3)
    {
        h = 3 * h + 1;
    }

    while (h >= 1)
    {
        for (int i = h; i < tamanho; i++)
        {
            int j = i;
            Itemgrande temp = a[i];
            (*atribui)++;

            while (j >= h && temp.campo < a[j - h].campo)
            {
                (*comparacoes)++;
                a[j] = a[j - h];
                (*atribui)++;
                j -= h;
            }

            a[j] = temp;
            (*atribui)++;
        }

        h /= 3;
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

        preencherVetordecrescente(vetor, tamanho);

        printf("Vetor não ordenado:\n");

        imprimirVetor(vetor, tamanho);

        clock_t inicio = clock();
        shellsort(vetor, tamanho, &comparacoes, &atribuicoes);
        clock_t fim = clock();

        printf("Vetor ordenado:\n");

        imprimirVetor(vetor, tamanho);

        printf("\n");
        printf("Número de comparações: %d\n", comparacoes);
        printf("Número de atribuições: %d\n", atribuicoes);
        printf("Tempo de execução: %.10f segundos\n", calcularTempo(inicio, fim));

        free(vetor);

        return 0;
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
        shellsortGrande(vetorgrande, tamanho, &comparacoes, &atribuicoes);
        clock_t fim = clock();

        printf("Vetor ordenado:\n");

        imprimirVetorgrande(vetorgrande, tamanho);

        printf("\n");
        printf("Número de comparações: %d\n", comparacoes);
        printf("Número de atribuições: %d\n", atribuicoes);
        printf("Tempo de execução: %.10f segundos\n", calcularTempo(inicio, fim));

        free(vetorgrande);
        break;
    }
    }
}

