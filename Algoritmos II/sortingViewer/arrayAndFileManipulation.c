#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

#include "arrayAndFileManipulation.h"

int* insertArraySize(int* n) {
    system("cls");
    do {
        printf("Digite o tamanho do vetor (MIN 1 & MAX 100000)\n");
        scanf("%d", n);
    } while (*n < MIN_ARRAY_SIZE || *n > MAX_ARRAY_SIZE);

    system("cls");

    return n;
}

int* runAgain(int *retry) {
    do {
        printf("Testar para novos valores (1 - SIM; 0 - NAO)?\n");
        scanf("%d", retry);
    } while (*retry != 1 && *retry != 0);

    return retry;
}

int exitProgram() {
    system("cls");

    return 0;
}

FILE *manipularArquivo(const char *nomeArquivo, const char *modo) {
    FILE *arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }
    return arquivo;
}

int* writeFileInArray(int vet[]) {
    FILE *file;

    int i = 0;

    file = manipularArquivo("random_values.txt", "r");

    while (fscanf(file, "%d, ", &vet[i]) == 1) {
        i++;
    }

    return vet;
}

int shuffleArray(int vet[], int n) {
    int i, j, temp, count = 0;
    int size = sizeof(*vet) / sizeof(vet[0]);
    double nextDouble;

    srand(time(NULL));

    for (i = 0; i < n; i++) {
        if(vet[i] <= vet[i+1]) {
            count++;
        } 
    }

    count = 0;

    for (i = n - 1; i > 0; i--) {
        j = rand() % n;
        temp = vet[i];
        vet[i] = vet[j];
        vet[j] = temp;
        count++;
    }

    return *vet;
}

int shuffleArrayFixedFactor(int vet[], int n) {
    int i, j, temp, count = 0;
    int size = sizeof(*vet) / sizeof(vet[0]);
    double randomizationFactor; //Grau de ordenacao
    double nextDouble;

    srand(time(NULL));

    for (i = 0; i < n; i++) {
        if(vet[i] <= vet[i+1]) {
            count++;
        } 
    }

    count = 0;

    do {
        printf("Randomization Factor (MIN = 0 & MAX = 1");
        scanf("%lf", &randomizationFactor);
    } while (randomizationFactor < 0 || randomizationFactor > 1);

    for (i = n - 1; i > 0; i--) {
        nextDouble = (double)rand() / (double)RAND_MAX;
        if (nextDouble < randomizationFactor) {
            j = rand() % n;
            temp = vet[i];
            vet[i] = vet[j];
            vet[j] = temp;
            count++;
        }
    }

    return *vet;
}

int shuffleArrayRandomFactor(int vet[], int n) {
    int i, j, temp, count = 0;
    int size = sizeof(*vet) / sizeof(vet[0]);
    float randomizationFactor; //Grau de ordenacao
    double nextDouble;

    srand(time(NULL));

    for (i = 0; i < n; i++) {
        if(vet[i] <= vet[i+1]) {
            count++;
        } 
    }

    count = 0;

    for (i = n - 1; i > 0; i--) {
        randomizationFactor = (double)rand() / (double)RAND_MAX;
        nextDouble = (double)rand() / (double)RAND_MAX;
        if (nextDouble < randomizationFactor) {
            j = rand() % n;
            temp = vet[i];
            vet[i] = vet[j];
            vet[j] = temp;
            count++;
        }
    }

    return *vet;
}