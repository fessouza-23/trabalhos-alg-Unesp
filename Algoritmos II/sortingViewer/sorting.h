#ifndef SORTING_H
#define SORTING_H

typedef int* (*SortFunction)(int[], int);

typedef int* (*SortFunctionSpecial)(int*, int, int, int*, int*, int*);

void printSortName(char** sortName, int i);

void printArrayData(SortFunction bufferAlgos[], SortFunctionSpecial bufferAlgosSpecial[], 
int vet[], int n, int *comps, int *trocas, int arrayCT[], const char* sortName[]);

void troca(int *x, int *y);

void getSortData(int* (*f)(int*, int), int *vet, int n, const char* sortName[]);

void getSortDataSpecial(int* (*f)(int*, int, int, int*, int*, int*), 
int *vet, int left, int right, int *comps, int *trocas, int* arrayCT);

int* bubble_sort(int vet[], int n);

int* insertion_sort(int vet[], int n);

int* selection_sort(int vet[], int n);

int* shell_sort(int vet[], int n);

int* quick_sort(int v[], int left, int right, int *comps, int *trocas, int *arrayCT);

int* partition(int v[], int left, int right, int *comps, int *trocas, int *arrayCT);

int* merge_sort(int v[], int inicio, int fim, int *comps, int *trocas, int *arrayCT);

void merge(int v[], int inicio, int meio, int fim, int *comps, int *trocas, int *arrayCT);

int* bead_sort(int vet[], int n);

#endif