#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../inc/arrayAndFileManipulation.h"

#ifdef _WIN32
    #include <windows.h>
#endif

void welcome_msg() {
    #ifdef __GNUC__
        printf ("COMPILED ON GCC VERSION %d.%d\n\n", __GNUC__, __GNUC_MINOR__);
    #endif

    printf("------------------------------------------------------------\n");
    printf("| Visualizador de performance para algoritmos de ordenacao |\n");
    printf("------------------------------------------------------------\n\n");
    printf("Este programa realiza um teste de perfomance para 7 tipos diferentes de algoritmos\n");
    printf("de ordenacao, sendo eles: bubble sort, insertion sort, selection sort, shell sort,\n");
    printf("bead sort, quick sort e merge sort. A performance e avaliada a partir de tres criterios:\n");
    printf("numero de comparacoes realizadas, quantidade de trocas realizadas e tempo de execucao.\n");
    printf("O programa aceita vetores de tamanho 1 ate 100000, incluso.\n\n\n");


    printf("Pressione qualquer tecla para continuar... ");
    getchar();
}

int* get_type_of_array(int *array_to_be_sorted) {
    char menu_option;

    printf("Escolha o tipo de vetor a ser ordenado:");
    printf("\n1 - Vetor nao ordenado\n2 - Vetor parcialmente ordenado\n3 - Vetor em ordem crescente\n4 - Vetor em ordem decrescente\n");

    do {
        menu_option = getchar();
        switch (menu_option) {
            case '1':
                write_file_in_array("res/unsorted_values.txt", array_to_be_sorted);
                break;
            case '2':
                write_file_in_array("res/partially_sorted_values.txt", array_to_be_sorted);
                break;
            case '3':
                write_file_in_array("res/ascending_sorted_values.txt", array_to_be_sorted);
                break;
            case '4':
                write_file_in_array("res/descending_sorted_values.txt", array_to_be_sorted);
                break;
            default:
                while ((menu_option = getchar()) != '\n');
                printf("Entrada invalida! Tente novamente\n");
                break;
        }
    } while (menu_option != '1' && menu_option != '2' && menu_option != '3' && menu_option != '4');

    while ((menu_option = getchar()) != '\n');

    return array_to_be_sorted;
}

FILE *open_file(const char *nomeArquivo, const char *modo) {
    FILE *arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        exit(-1);
    }
    return arquivo;
}

int* write_file_in_array(char* string, int vet[]) {
    FILE *file;
    char filename[100];

    int i = 0;

    snprintf(filename, sizeof(filename), string);

    file = open_file(string, "r");

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
            printf("Entrada fora do intervalo! Tente novamente\n");
            getchar();
            loopAgain = true;
            fflush(stdin);
            CLR_SCREEN;
            continue;
        }

        while (isspace(input_buffer[i])) i++;

        if (length == i) {
            printf("Entrada invalida! Tente novamente\n");
            getchar();
            CLR_SCREEN;
            loopAgain = true;
            continue;
        }

        if (input_buffer[i] == '-') {
            printf("Entrada invalida! Tente novamente\n");
            getchar();
            CLR_SCREEN;
            loopAgain = true;
            continue;
        }

        while (i < length && !isspace(input_buffer[i])) {
            if (!isdigit(input_buffer[i])) {
                printf("Entrada invalida! Tente novamente\n");
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
            printf("Entrada invalida! Tente novamente\n");
            getchar();
            CLR_SCREEN;
            loopAgain = true;
            continue;
        }

        if (atoi(integer_buffer) > 100000 || atoi(integer_buffer) < 1) {
            printf("Entrada fora do intervalo! Tente novamente\n");
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
            printf("Entrada invalida! Tente novamente\n");
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
    double nextDouble = 0.5;

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