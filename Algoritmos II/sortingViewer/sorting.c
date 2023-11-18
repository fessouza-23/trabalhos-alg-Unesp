#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "sorting.h"
#include "arrayAndFileManipulation.h"

#ifdef _WIN32
    #include <windows.h>
#endif

#define CONTA(i, j) contas[i * max + j]

void printSortName(char** sortName, int i) {
    for (i = 0; i < 5; i++) {
        printf("%s", sortName[i]);
        printf("\n");
    }
}

void printArrayData(SortFunction bufferAlgos[], SortFunctionSpecial bufferAlgosSpecial[], 
int vet[], int n, int *comps, int *trocas, int arrayCT[], const char* sortName[]) {
    printf("-------- TAMANHO %d --------\n", n);

    int i, j;

    for (i = 0; i < SORT_FUNCTIONS; i++) {
        printf("--- %s ---\n", sortName[i]);
        getSortData(bufferAlgos[i], vet, n, sortName);
    }

    j = i;

    for (i = 0; i < SPECIAL_SORT_FUNCTIONS; i++) {
        printf("--- %s ---\n", sortName[j]);
        getSortDataSpecial(bufferAlgosSpecial[i], vet, 0, n-1, comps, trocas, arrayCT);
        j++;
    }


    printf("\n\n");
}


void troca(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void getSortData(int* (*f)(int*, int), int *vet, int n, const char* sortName[]) {
    #ifdef _WIN32
        LARGE_INTEGER frequency;
        LARGE_INTEGER start;
        LARGE_INTEGER end;
        double elapsed_time;

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        int *dataSort = f(vet, n);

        QueryPerformanceCounter(&end);
        elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

        printf("Comparacoes = %12d; Trocas = %12d; Tempo = %12lf\n", dataSort[0], dataSort[1], elapsed_time);
    #elif __linux__ 
        clock_t begin = clock();
        clock_gettime(begin, CLOCK_REALTIME);

        int *dataSort = f(vet, n);

        clock_t end = clock();
        double elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("Comparacoes = %12d; Trocas = %12d; Tempo = %12lf\n", dataSort[0], dataSort[1], elapsed_time);
    #endif

    shuffleArray(vet, n);
}

void getSortDataSpecial(int* (*f)(int*, int, int, int*, int*, int*), 
int *vet, int left, int right, int *comps, int *trocas, int* arrayCT) {
    #ifdef _WIN32
        LARGE_INTEGER frequency;
        LARGE_INTEGER start;
        LARGE_INTEGER end;
        double elapsed_time;

        int n = right;

        for (int i = 0; i < MAX_ARGS; i++) {
            arrayCT[i] = 0;
        }

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        int *dataSort = f(vet, left, right, comps, trocas, arrayCT);

        QueryPerformanceCounter(&end);
        elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

        printf("Comparacoes = %12d; Trocas = %12d; Tempo = %12lf\n", dataSort[1], dataSort[2], elapsed_time);
    #else
        int n = right;

        for (int i = 0; i < MAX_ARGS; i++) {
            arrayCT[i] = 0;
        }
        clock_t begin = clock();
        clock_gettime(begin, CLOCK_REALTIME);

        int *dataSort = f(vet, left, right, comps, trocas, arrayCT);

        clock_t end = clock();
        double elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("Comparacoes = %12d; Trocas = %12d; Tempo = %12lf\n", dataSort[1], dataSort[2], elapsed_time);
    #endif

    shuffleArray(vet, n);
}

int* bubble_sort(int vet[], int n) {
    int i, j, houve_troca = 1;
    int comps = 0, trocas = 0;
    static int arrayCompsAndTrocas[2];
    
    for(i = 0; i < n-1 && houve_troca; i++){
        houve_troca = 0;
        for(j = 0; j < n-i-1; j++){
          comps += 1;
          if (vet[j] > vet[j+1]){
              troca(&vet[j], &vet[j+1]);
              houve_troca = 1;
              trocas += 1;
          }
        }
    }

    arrayCompsAndTrocas[0] = comps;
    arrayCompsAndTrocas[1] = trocas;

    return arrayCompsAndTrocas;
}

int* insertion_sort(int vet[], int n) {
    int i, j, aux;
    int comps = 0, trocas = 0;
    static int arrayCompsAndTrocas[2];

    for(i = 1; i < n; i++){
        aux = vet[i]; 
        for(j = i-1; j >= 0 && aux < vet[j]; j--) {
            vet[j+1] = vet[j];
            comps++; 
            trocas++;
        }
        if (j >= 0)
            comps++;
        vet[j+1] = aux;
    }

    arrayCompsAndTrocas[0] = comps;
    arrayCompsAndTrocas[1] = trocas;

    return arrayCompsAndTrocas;
}

int* selection_sort(int vet[], int n) {
    int i, j, min_ind;
    int comps = 0, trocas = 0;
    static int arrayCompsAndTrocas[2];

    for(i = 0; i < n-1; i++){
        min_ind = i;
        for(j = i+1; j < n; j++) {
            comps++;
            if (vet[j] < vet[min_ind])
                min_ind = j;
        }
        if (min_ind != i) {
            troca(&vet[min_ind], &vet[i]);
            trocas++;
        }
    }

    arrayCompsAndTrocas[0] = comps;
    arrayCompsAndTrocas[1] = trocas;

    return arrayCompsAndTrocas;
}

int* shell_sort(int vet[], int n) {
    int i, j, k, aux;
    int comps = 0, trocas = 0;
    static int arrayCompsAndTrocas[2];

    for(k = n/2; k > 0; k /= 2)
    {
        for(i = k; i < n; i++){
            aux = vet[i]; 
            for(j = i - k; j >= 0 && aux < vet[j]; j -= k) {
                vet[j+k] = vet[j];
                comps++;
                trocas++;
            }
            if (j >= 0)
                comps++;
            vet[j+k] = aux;
        }
    }

    arrayCompsAndTrocas[0] = comps;
    arrayCompsAndTrocas[1] = trocas;

    return arrayCompsAndTrocas;
}

int* quick_sort(int v[], int left, int right, int *comps, int *trocas, int *arrayCT) {
	if (left < right) {
        int med = (left+right)/2;
        if (v[left] <= v[med] && v[left] >= v[right]){
            (*comps) += 2;
        }
        else if (v[left] >= v[med] && v[left] <= v[right]){
            (*comps) += 4;
        }
        else if (v[med] <= v[left] && v[med] >= v[right]){
            (*comps) += 6;
            (*trocas)++;
            troca(&v[left], &v[med]);
        }
        else if (v[med] >= v[left] && v[med] <= v[right]){
            (*comps) += 6;
            (*trocas)++;
            troca(&v[left], &v[med]);
        } 
        else {
            (*comps) += 8;
            (*trocas)++;
            troca(&v[left], &v[right]);
        }

        int index_pivot = partition(v, left, right, comps, trocas, arrayCT)[0];
        quick_sort(v, left, index_pivot - 1, comps, trocas, arrayCT);
        quick_sort(v, index_pivot + 1, right, comps, trocas, arrayCT);	
	}

    arrayCT[1] = *comps;
    arrayCT[2] = *trocas;

    return arrayCT;
}

int* partition(int v[], int left, int right, int *comps, int *trocas, int *arrayCT) {
    int pivot = v[left];
    int i = left;
    int j;

    for (j = left + 1; j <= right; j++) {
        (*comps)++;
        if (v[j] <= pivot) {
            i+=1;
            (*trocas)++;
            troca(&v[i], &v[j]);
        }
    }
    (*trocas)++;
    troca(&v[left], &v[i]); //função auxilar

    arrayCT[0] = i;
    arrayCT[1] = *comps;
    arrayCT[2] = *trocas;
    
    return arrayCT; 
}

int* merge_sort(int v[], int inicio, int fim, int *comps, int *trocas, int *arrayCT) {   
    int meio;

    if (inicio < fim) {
        meio = floor((inicio + fim) / 2);
        merge_sort(v, inicio, meio, comps, trocas, arrayCT);
        merge_sort(v, meio + 1, fim, comps, trocas, arrayCT);
        merge(v, inicio, meio, fim, comps, trocas, arrayCT);
    }

    arrayCT[1] = *comps;
    arrayCT[2] = *trocas;

    return arrayCT;
}

void merge(int v[], int inicio, int meio, int fim, int *comps, int *trocas, int *arrayCT) {
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;

    temp = (int*) malloc (tamanho * sizeof(int));
    
    if (temp != NULL) {
        for (i = 0; i < tamanho; i++) {

            if (!fim1 && !fim2) {
                (*comps)++;
                if (v[p1] < v[p2]) {
                    temp[i] = v[p1++];
                    (*trocas)++;
                }
                else {
                    temp[i] = v[p2++];
                    (*trocas)++;
                }

                if (p1 > meio) {
                    fim1 = 1;
                    (*trocas)++;
                }

                if (p2 > meio) {
                    fim2 = 1;
                    (*trocas)++;
                }

            } else {
                (*comps)++;
                if (!fim1) {
                    temp[i] = v[p1++];
                    (*trocas)++;
                } else {
                    temp[i] = v[p2++];
                    (*trocas)++;
                }
            }
        }

        for (j = 0, k = inicio; j < tamanho; j++, k++)
            v[k] = temp[j];
    }

    arrayCT[1] = *comps;
    arrayCT[2] = *trocas;

    free(temp);
}

int* bead_sort(int vet[], int n) {
    int i, j, max, soma, comps = 0, trocas = 0;
    unsigned char *contas;
    static int arrayCompsAndTrocas[2];

    // Encontra o elemento máximo no array 
    for (i = 1, max = vet[0]; i < n; i++) {
        comps++;
        if (vet[i] > max) {
            max = vet[i];
        }
    }

    // Aloca memória para o array de contas
    contas = calloc(1, max * n);

    // Marca as contas
    for (i = 0; i < n; i++) {
        for (j = 0; j < vet[i]; j++) {
            CONTA(i, j) = 1;
        }
    }

    // Conta o número de contas em cada poste
    for (j = 0; j < max; j++) {
        for (soma = i = 0; i < n; i++) {
            soma += CONTA(i, j);
            CONTA(i, j) = 0;
            trocas++;
        }
    }

    // Marca as contas na parte inferior
    for (i = n - soma; i < n; i++) {
        CONTA(i, j) = 1;
        trocas++;
    }

    // Atribui os valores ordenados de volta ao array
    for (i = 0; i < n; i++) {
        for (j = 0; j < max && CONTA(i, j); j++)
            vet[i] = j;
    }

    // Libera a memória alocada
    free(contas);

    arrayCompsAndTrocas[0] = comps;
    arrayCompsAndTrocas[1] = trocas;

    return arrayCompsAndTrocas;

}