#ifndef SORTING_H
#define SORTING_H

/* 
*  Declara o tipo "SortFunction", que trata-se de uma função do tipo int* e possui
*  seis argumentos como parâmetros, sendo esses o vetor a ser ordenado, a parte "esquerda" do
*  vetor, utilizado pelas funções "quick_sort" e "merge_sort", o tamanho do vetor a ser
*  ordenado, o número de comparações e o número de trocas. É utilizada para passar a função de ordenação
*  como argumento para a função "get_sort_data" e assim escrever seus dados na tela
*/ 
typedef long long int* (*SortFunction)(int*, int, int, long long int*, long long int*, long long int*);

/* 
*  Função que escreve os dados de perfomance do algoritmo de ordenação na tela.
*  Recebe como parâmentro o vetor do tipo "SortFunction", o vetor a ser ordenado,
*  o tamanho do vetor e o nome do vetor.
*/
void print_array_data(SortFunction bufferAlgos[], int array_to_be_sorted[], int array_size, const char* sortName[]);

/* 
*  Função que escreve na tela os dados de performance do algoritmo de ordenação.
*  Recebe como parâmetro a função de ordenação, o vetor a ser ordenado, a parte "esquerda" do
*  vetor, utilizado pelas funções "quick_sort" e "merge_sort", o tamanho do vetor a ser
*  ordenado, o número de comparações, o número de trocas e o vetor que terá como índices
*  as comparações e trocas. É necessário utilizar um vetor para armazenar as comparações
*  e trocas pois o ponteiro "int* dataSort" recebe a função de ordenação que foi passada como parâmetro,
*  e as funções de ordenação retornam um ponteiro para o vetor "arrayCT", que tem como índices
*  as comparações e trocas realizadas pela função de ordenação.
*/
void get_sort_data(long long int* (*f)(int*, int, int, long long int*, long long int*, long long int*), 
int *array_to_be_sorted, int left, int array_size, long long int *comps, long long int *swaps, long long int* arrayCT);

void swap(int *x, int *y);

long long int* bubble_sort(int vet[], int m, int n, long long int *comps, long long int *swaps, long long int *arrayCT);

long long int* insertion_sort(int vet[], int m, int n, long long int *comps, long long int *swaps, long long int *arrayCT);

long long int* selection_sort(int vet[], int m, int n, long long int *comps, long long int *swaps, long long int *arrayCT);

long long int* shell_sort(int vet[], int m, int n, long long int *comps, long long int *swaps, long long int *arrayCT);

long long int* quick_sort(int v[], int left, int right, long long int *comps, long long int *swaps, long long int *arrayCT);

long long int* partition(int v[], int left, int right, long long int *comps, long long int *swaps, long long int *arrayCT);

long long int* merge_sort(int v[], int left, int right, long long int *comps, long long int *swaps, long long int *arrayCT);

long long int* merge(int v[], int left, int mid, int right, long long int *comps, long long int *swaps, long long int *arrayCT);

long long int* bead_sort(int vet[], int m, int n, long long int *comps, long long int *swaps, long long int *arrayCT);

#endif