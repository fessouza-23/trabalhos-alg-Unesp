#ifndef SORTING_H
#define SORTING_H

#define MAX_ARRAY_SIZE 100000
#define MIN_ARRAY_SIZE 1

FILE *manipularArquivo(const char *nomeArquivo, const char *modo);

int shuffleArray(int vet[], int n);

int shuffleArrayFixedFactor(int vet[], int n);

int shuffleArrayRandomFactor(int vet[], int n);

void troca(int *x, int *y);

void getSortData(int* (*f)(int*, int), int *vet, int n);

int* bubble_sort(int vet[], int n);

int* insertion_sort(int vet[], int n);

int* selection_sort(int vet[], int n);

int* shell_sort(int vet[], int n);

void quick_sort(int v[], int left, int right);

int partition(int v[], int left, int right);

void merge(int v[], int inicio, int meio, int fim);

void merge_sort(int v[], int inicio, int fim);

int dropSort(int *arr, int size, int *sortedArr);

int dropSortRecMem(int *arr, int size, int *sortedArr);

int dropSortDoubleComparison(int *arr, int size, int *sortedArr);

int dropSortRecMemAndDoubleComparison(int *arr, int size, int *sortedArr);

#endif