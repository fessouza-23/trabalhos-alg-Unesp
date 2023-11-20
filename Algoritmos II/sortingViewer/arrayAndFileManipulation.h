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

// Função utilizada para abrir um arquivo
FILE *open_file(const char *nomeArquivo, const char *modo);

// Recebe o tamanho do vetor
int get_array_size(int *n);

// Verifica se o programa deve reiniciar
int* restart(int *retry);

// Fecha o programa
int exit_program();

// Escreve o arquivo que contém os valores para serem ordenados em um vetor
int* write_file_in_array(int vet[]);

// Embaralha um vetor
int shuffle_array(int vet[], int n);

// Embaralha um vetor com um grau de aleatorização fixo
int shuffle_array_fixed_factor(int vet[], int n);

// Embaralha um vetor com um grau de aleatorização aleatório
int shuffle_array_random_factor(int vet[], int n);

#endif