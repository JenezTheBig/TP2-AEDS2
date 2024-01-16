#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int chave;
} Item;

typedef struct {
    char campo;
} Itemgrande;

int comparacoes = 0;
int atribuicoes = 0;

void particionar(int esq, int dir, int* i, int* j, Item a[]) {
    Item x, w;
    *i = esq;
    *j = dir;
    x = a[(*i + *j) / 2];

    do {
        while (x.chave > a[*i].chave) {
            (*i)++;
            comparacoes++;
        }
        while (x.chave < a[*j].chave) {
            (*j)--;
            comparacoes++;
        }

        if (*i <= *j) {
            w = a[*i];
            a[*i] = a[*j];
            a[*j] = w;
            (*i)++;
            (*j)--;
            atribuicoes += 3;
        }
    } while (*i <= *j);
}

void ordenar(int esq, int dir, Item a[]) {
    int i, j;
    particionar(esq, dir, &i, &j, a);

    if (esq < j) {
        ordenar(esq, j, a);
    }
    if (i < dir) {
        ordenar(i, dir, a);
    }
}

void quicksort(Item a[], int tamanho) {
    comparacoes = 0;
    atribuicoes = 0;
    ordenar(0, tamanho - 1, a);
}

void particionarGrande(int esq, int dir, int* i, int* j, Itemgrande a[]) {
    Itemgrande x, w;
    *i = esq;
    *j = dir;
    x = a[(*i + *j) / 2];

    do {
        while (x.campo > a[*i].campo) {
            (*i)++;
            comparacoes++;
        }
        while (x.campo < a[*j].campo) {
            (*j)--;
            comparacoes++;
        }

        if (*i <= *j) {
            w = a[*i];
            a[*i] = a[*j];
            a[*j] = w;
            (*i)++;
            (*j)--;
            atribuicoes += 3;
        }
    } while (*i <= *j);
}

void ordenarGrande(int esq, int dir, Itemgrande a[]) {
    int i, j;
    particionarGrande(esq, dir, &i, &j, a);

    if (esq < j) {
        ordenarGrande(esq, j, a);
    }
    if (i < dir) {
        ordenarGrande(i, dir, a);
    }
}

void quicksortGrande(Itemgrande a[], int tamanho) {
    comparacoes = 0;
    atribuicoes = 0;
    ordenarGrande(0, tamanho - 1, a);
}

void preencherVetor(Item a[], int tamanho) {
    srand(12);

    for (int i = 0; i < tamanho; i++) {
        a[i].chave = rand();
    }
}

void preencherVetorcrescente(Item a [], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        a[i].chave = i + 1;
    }
}

void preencherVetordecrescente(Item a[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        a[i].chave = tamanho - i;
    }
}

void preencherVetorgrande(Itemgrande a[], int tamanho) {
    srand(12);

    for (int i = 0; i < tamanho; i++) {
        a[i].campo = 'A' + rand() % 26;
    }
}

void imprimirVetor(Item a[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d \n", a[i].chave);
    }
    printf("\n");
}

void imprimirVetorgrande(Itemgrande a[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%c \n", a[i].campo);
    }
    printf("\n");
}

double calcularTempo(clock_t inicio, clock_t fim) {
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

int main() {
    int tamanho;
    int opcao;

    printf("Selecione qual tipo de registro:\n");
    printf("~1~ Registro pequeno (tipo int)\n");
    printf("~2~ Registro grande (tipo char)\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            printf("Digite o tamanho do vetor: ");
            scanf("%d", &tamanho);

            Item* vetor = malloc(tamanho * sizeof(Item));

            preencherVetordecrescente(vetor, tamanho);

            printf("Vetor não ordenado:\n");

            imprimirVetor(vetor, tamanho);

            printf("\n");

            clock_t inicio = clock();
            quicksort(vetor, tamanho);
            clock_t fim = clock();

            printf("Vetor ordenado:\n");

            imprimirVetor(vetor, tamanho);

            printf("\n");
            printf("Tempo de execução: %.10f segundos\n", calcularTempo(inicio, fim));
            printf("Comparacoes: %d\n", comparacoes);
            printf("Atribuicoes: %d\n", atribuicoes);

            free(vetor);

            return 0;
        }
        case 2: {
            printf("Digite o tamanho do vetor: ");
            scanf("%d", &tamanho);

            Itemgrande* vetorgrande = malloc(tamanho * sizeof(Itemgrande));

            preencherVetorgrande(vetorgrande, tamanho);

            printf("Vetor não ordenado:\n");

            imprimirVetorgrande(vetorgrande, tamanho);

            printf("\n");

            clock_t inicio = clock();
            quicksortGrande(vetorgrande, tamanho);
            clock_t fim = clock();

            printf("Vetor ordenado:\n");

            imprimirVetorgrande(vetorgrande, tamanho);

            printf("\n");
            printf("Tempo de execução: %.10f segundos\n", calcularTempo(inicio, fim));
            printf("Comparacoes: %d\n", comparacoes);
            printf("Atribuicoes: %d\n", atribuicoes);

            free(vetorgrande);

            return 0;
       
        }
    }
}
