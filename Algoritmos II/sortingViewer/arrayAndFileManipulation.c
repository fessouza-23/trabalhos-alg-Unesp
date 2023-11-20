#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "arrayAndFileManipulation.h"

#ifdef _WIN32
    #include <windows.h>
#endif

FILE *open_file(const char *nomeArquivo, const char *modo) {
    FILE *arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        exit(-1);
    }
    return arquivo;
}

int* write_file_in_array(int vet[]) {
    FILE *file;

    int i = 0;

    file = open_file("random_values.txt", "r");

    while (fscanf(file, "%d, ", &vet[i]) == 1) {
        i++;
    }

    return vet;
}

int get_array_size(int *n) {
    CLR_SCREEN;
    int i, integer_chars, length;
    char input_buffer[BUFFER_SIZE], integer_buffer[BUFFER_SIZE];
    bool loopAgain = false;

    do {
        fflush(stdin);
        integer_chars = 0;
        *n = 0;
        length = 0;
        i = 0;

        printf("Digite o tamanho do vetor a ser ordenado (MIN 1 & MAX 100000)\n");

        if (strlen(fgets(input_buffer, BUFFER_SIZE, stdin)) <= BUFFER_SIZE) {
            length = strlen(input_buffer);
        } else {
            printf("Entrada fora do intervalo!\n");
            getchar();
            loopAgain = true;
            fflush(stdin);
            CLR_SCREEN;
            continue;
        }

        while (isspace(input_buffer[i])) i++;

        if (length == i) {
            printf("Entrada invalida!\n");
            getchar();
            CLR_SCREEN;
            loopAgain = true;
            continue;
        }

        if (input_buffer[i] == '-') {
            printf("Entrada invalida!\n");
            getchar();
            CLR_SCREEN;
            loopAgain = true;
            continue;
        }

        while (i < length && !isspace(input_buffer[i])) {
            if (!isdigit(input_buffer[i])) {
                printf("Entrada invalida!\n");
                getchar();
                CLR_SCREEN;
                loopAgain = true;
                break;
            }

            loopAgain = false;
            integer_buffer[integer_chars] = input_buffer[i];
            integer_chars++;
            i++;
        }

        if (loopAgain) continue;

        integer_buffer[integer_chars] = '\0';

        while(isspace(input_buffer[i])) i++;

        if (input_buffer[i] != '\0') {
            printf("Entrada invalida!\n");
            getchar();
            CLR_SCREEN;
            loopAgain = true;
            continue;
        }

        if (atoi(integer_buffer) > 100000 || atoi(integer_buffer) < 1) {
            printf("Entrada fora do intervalo!\n");
            getchar();
            CLR_SCREEN;
            loopAgain = true;
            continue;
        } else {
            *n = atoi(integer_buffer);
            loopAgain = false;
            break;
        }

    } while (loopAgain);

    CLR_SCREEN;

    return *n;
}

int* restart(int *retry) {
    int ch;

    bool loopAgain = false;

    do {
        printf("Testar para novos valores (1 - SIM; 0 - NAO)?\n");
        *retry = fgetc(stdin);
        if (*retry != '1' && *retry != '0') {
            printf("Entrada invalida!\n");
            while ((ch = getchar()) != '\n');
            loopAgain = true;
            continue;
        } else {
            break; 
        }
    } while (loopAgain);

    while ((ch = getchar()) != '\n');

    return retry;
}

int exit_program() {
    CLR_SCREEN;
    exit(0);
    return 0;
}

int shuffle_array(int vet[], int n) {
    int i, j, temp, count = 0;

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

int shuffle_array_fixed_factor(int vet[], int n) {
    int i, j, temp, count = 0;
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

int shuffle_array_random_factor(int vet[], int n) {
    int i, j, temp, count = 0;
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