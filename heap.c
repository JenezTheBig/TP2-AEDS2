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

void refazer(int esq, int dir, Item a[], int *comparacoes, int *atribuicoes)
{
    int i = esq;
    int j = i * 2;
    Item x = a[i];

    while (j <= dir)
    {
        (*comparacoes)++;

        if (j < dir && a[j].chave < a[j + 1].chave)
        {
            j++;
        }

        if (x.chave >= a[j].chave)
        {
            break;
        }

        a[i] = a[j];
        (*atribuicoes)++;
        i = j;
        j = i * 2;
    }

    a[i] = x;
    (*atribuicoes)++;
}

void construir(Item a[], int tamanho, int *comparacoes, int *atribuicoes)
{
    int esq = tamanho / 2;

    while (esq >= 0)
    {
        refazer(esq, tamanho - 1, a, comparacoes, atribuicoes);
        esq--;
    }
}

void heapsort(Item a[], int tamanho, int *comparacoes, int *atribuicoes)
{
    construir(a, tamanho, comparacoes, atribuicoes);

    int dir = tamanho - 1;

    while (dir > 0)
    {
        Item temp = a[0];
        a[0] = a[dir];
        a[dir] = temp;
        (*atribuicoes) += 3;

        dir--;
        refazer(0, dir, a, comparacoes, atribuicoes);
    }
}

void refazergrande(Itemgrande a[], int esq, int dir, int* comparacoes, int* atribuicoes) {
    int i = esq;
    int j = i * 2 + 1;
    Itemgrande x = a[i];

    while (j <= dir) {
        (*comparacoes)++;
        if (j < dir && a[j].campo < a[j + 1].campo) {
            j++;
        }

        (*comparacoes)++;
        if (x.campo >= a[j].campo) {
            break;
        }

        a[i] = a[j];
        (*atribuicoes)++;
        i = j;
        j = i * 2 + 1;
    }

    a[i] = x;
    (*atribuicoes)++;
}

void construirgrande(Itemgrande a[], int tamanho, int *comparacoes, int *atribuicoes)
{
    int esq = tamanho / 2;

    while (esq >= 0)
    {
        refazergrande(a, esq, tamanho - 1, comparacoes, atribuicoes);
        esq--;
    }
}

void heapsortgrande(Itemgrande a[], int tamanho, int *comparacoes, int *atribuicoes)
{
    construirgrande(a, tamanho, comparacoes, atribuicoes);

    int dir = tamanho - 1;

    while (dir > 0)
    {
        Itemgrande temp = a[0];
        a[0] = a[dir];
        a[dir] = temp;
        (*atribuicoes) += 3;

        dir--;
        refazergrande(a, 0, dir, comparacoes, atribuicoes);
    }
}

void preencherVetor(Item a[], int tamanho)
{
    srand(22);

    for (int i = 0; i < tamanho; i++)
    {
        a[i].chave = rand();
    }
}

void preencherVetorcrescente(Item a[], int tamanho)
{
    for(int i = 0; i < tamanho; i++)
    {
        a[i].chave = i + 1;
    }
}

void preencherVetordecrescente(Item a[], int tamanho)
{
    for(int i = 0; i < tamanho; i++)
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
        printf("%d ", a[i].chave);
    }
    printf("\n");
}

void imprimirVetorgrande(Itemgrande a[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("%c ", a[i].campo);
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
    
        int comparacoes = 0;
        int atribuicoes = 0;

        clock_t inicio = clock();

        heapsort(vetor, tamanho, &comparacoes, &atribuicoes);

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

        Itemgrande *vetor = malloc(tamanho * sizeof(Itemgrande));

        preencherVetorgrande(vetor, tamanho);

        printf("Vetor não ordenado:\n");
        imprimirVetorgrande(vetor, tamanho);

        int comparacoes = 0;
        int atribuicoes = 0;

        clock_t inicio = clock();

        heapsortgrande(vetor, tamanho, &comparacoes, &atribuicoes);

        clock_t fim = clock();

        printf("Vetor ordenado:\n");
        imprimirVetorgrande(vetor, tamanho);

        printf("\n");
        printf("Número de comparações: %d\n", comparacoes);
        printf("Número de atribuições: %d\n", atribuicoes);
        printf("Tempo de execução: %.10f segundos\n", calcularTempo(inicio, fim));

        free(vetor);

        return 0;
    }

    default:
        printf("Opção inválida\n");
        return 0;
    }
}
