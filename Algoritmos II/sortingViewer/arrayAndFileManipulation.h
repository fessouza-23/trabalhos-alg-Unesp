#ifndef ARRAYANDFILEMANIPULATION_H
#define ARRAYANDFILEMANIPULATION_H

#define MAX_ARRAY_SIZE         100000
#define BUFFER_SIZE            10
#define MIN_ARRAY_SIZE         1
#define MAX_ARGS               3
#define SORT_FUNCTIONS         7
#define RETRY_INPUT_SIZE       2

#ifdef _WIN32
    #define CLR_SCREEN system("cls");
#else
    #include <stdlib.h>
    #define CLR_SCREEN system("clear");
#endif

FILE *manipularArquivo(const char *nomeArquivo, const char *modo);

int insertArraySize(int *n);

int* runAgain(int *retry);

int exitProgram();

int* writeFileInArray(int vet[]);

int shuffleArray(int vet[], int n);

int shuffleArrayFixedFactor(int vet[], int n);

int shuffleArrayRandomFactor(int vet[], int n);

#endif