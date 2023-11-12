#ifndef ARRAYANDFILEMANIPULATION_H
#define ARRAYANDFILEMANIPULATION_H

#define MAX_ARRAY_SIZE 100000
#define MIN_ARRAY_SIZE 1

FILE *manipularArquivo(const char *nomeArquivo, const char *modo);

int* insertArraySize(int* n);

int* runAgain(int *retry);

int exitProgram();

int* writeFileInArray(int vet[]);

int shuffleArray(int vet[], int n);

int shuffleArrayFixedFactor(int vet[], int n);

int shuffleArrayRandomFactor(int vet[], int n);

#endif