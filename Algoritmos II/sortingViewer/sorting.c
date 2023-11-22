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

#define BEAD(i, j) beads[i * max + j]

// Escreve os dados de performance na tela
void print_array_data(SortFunction bufferAlgos[], int array_to_be_sorted[], int array_size, const char* sortName[]) {
    // Declara as comparações, trocas e o vetor que irá armazenar esses dados
    int i;
    long long int comps, swaps, arrayCompsAndSwaps[MAX_ARGS];

    printf("-------- TAMANHO %d --------\n", array_size);

    for (i = 0; i < SORT_FUNCTIONS; i++) { 
        comps = 0; swaps = 0;
        // Escreve o nome do algoritmo na tela
        printf("--- %s ---\n", sortName[i]);
        // Escreve os dados do teste de perfomance na tela
        get_sort_data(bufferAlgos[i], array_to_be_sorted, 0, array_size-1, &comps, &swaps, arrayCompsAndSwaps);
    }


    printf("\n\n");
}

// Calcula os dados de performance das funções de ordenação
void get_sort_data(long long int* (*f)(int*, int, int, long long int*, long long int*, long long int*), 
int *array_to_be_sorted, int left, int array_size, long long int *comps, long long int *swaps, long long int* arrayCT) {
    #ifdef _WIN32
        // Declara as variáveis que serão utilizadas pelas funções de medição de tempo de execução (QueryPerformance)
        LARGE_INTEGER frequency;
        LARGE_INTEGER start;
        LARGE_INTEGER end;
        double elapsed_time;

        // Limpa o vetor
        for (int i = 0; i < MAX_ARGS; i++) {
            arrayCT[i] = 0;
        }

        // Inicia o "cronômetro" para medir o tempo de execução da função de ordenação 
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        // Declara um vetor int* que recebe o vetor "arrayCT" das funções de ordenação
        // "ArrayCT" possui como indíces o número de comparações e trocas, respectivamente
        long long int *dataSort = f(array_to_be_sorted, left, array_size, comps, swaps, arrayCT);

        // Para o cronômetro
        QueryPerformanceCounter(&end);
        // Calcula o tempo de execução, em segundos
        elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

        // Escreve na tela o número de comparações, trocas e o tempo de execução da função de ordenação
        printf("Comparacoes = %12lld; Trocas = %12lld; Tempo = %12lf segundos\n", dataSort[0], dataSort[1], elapsed_time);
    #else
        // Limpa o vetor
        for (int i = 0; i < MAX_ARGS; i++) {
            arrayCT[i] = 0;
        }

        // Inicia o "cronômetro" para medir o tempo de execução da função de ordenação 
        clock_t begin = clock();
        clock_gettime(begin, CLOCK_REALTIME);

        // Declara um vetor int* que recebe o vetor "arrayCT" das funções de ordenação
        // "ArrayCT" possui como indíces o número de comparações e trocas, respectivamente
        int *dataSort = f(vet, left, right, comps, swaps, arrayCT);

        // Para o cronômetro
        clock_t end = clock();
        // Calcula o tempo de execução, em segundos
        double elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;

        // Escreve na tela o número de comparações, trocas e o tempo de execução da função de ordenação
        printf("Comparacoes = %12d; Trocas = %12d; Tempo = %12lf\n", dataSort[0], dataSort[1], elapsed_time);
    #endif

    /*
    * Após o vetor ter sido ordenado, embaralha novamente para que assim a próxima
    * função de ordenação receba um vetor desordenado
    */

    shuffle_array(array_to_be_sorted, array_size);
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

long long int* bubble_sort(int vet[], int m, int n, long long int *comps, long long int *swaps, long long int *arrayCT) {
    int i, j, swap_occured = 1;

    n++;
    
    for(i = 0; i < n-1 && swap_occured; i++){
        swap_occured = 0;
        for(j = 0; j < n-i-1; j++){
          (*comps) += 1;
          if (vet[j] > vet[j+1]){
              (*swaps) += 1;
              swap(&vet[j], &vet[j+1]);
              swap_occured = 1;
          }
        }
    }

    arrayCT[0] = *comps;
    arrayCT[1] = *swaps;

    return arrayCT;
}

long long int* insertion_sort(int vet[], int m, int n, long long int *comps, long long int *swaps, long long int *arrayCT) {
    int i, j, aux;

    n++;

    for(i = 1; i < n; i++){
        aux = vet[i]; 
        for(j = i-1; j >= 0 && aux < vet[j]; j--) {
            (*comps)++; 
            (*swaps)++;
            vet[j+1] = vet[j];
        }
        if (j >= 0)
            (*comps)++;
        vet[j+1] = aux;
    }

    arrayCT[0] = *comps;
    arrayCT[1] = *swaps;

    return arrayCT;
}

long long int* selection_sort(int vet[], int m, int n, long long int *comps, long long int *swaps, long long int *arrayCT) {
    int i, j, min_ind;

    n++;

    for(i = 0; i < n-1; i++){
        min_ind = i;
        for(j = i+1; j < n; j++) {
            (*comps)++;
            if (vet[j] < vet[min_ind])
                min_ind = j;
        }
        if (min_ind != i) {
            (*swaps)++;
            swap(&vet[min_ind], &vet[i]);
        }
    }

    arrayCT[0] = *comps;
    arrayCT[1] = *swaps;

    return arrayCT;
}

long long int* shell_sort(int vet[], int m, int n, long long int *comps, long long int *swaps, long long int *arrayCT) {
    int i, j, k, aux;

    n++;

    for(k = n/2; k > 0; k /= 2)
    {
        for(i = k; i < n; i++){
            aux = vet[i]; 
            for(j = i - k; j >= 0 && aux < vet[j]; j -= k) {
                (*comps)++;
                (*swaps)++;
                vet[j+k] = vet[j];
            }
            if (j >= 0)
                (*comps)++;
            vet[j+k] = aux;
        }
    }

    arrayCT[0] = *comps;
    arrayCT[1] = *swaps;

    return arrayCT;
}

long long int* quick_sort(int v[], int left, int right, long long int *comps, long long int *swaps, long long int *arrayCT) {
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
            (*swaps)++;
            swap(&v[left], &v[med]);
        }
        else if (v[med] >= v[left] && v[med] <= v[right]){
            (*comps) += 6;
            (*swaps)++;
            swap(&v[left], &v[med]);
        } 
        else {
            (*comps) += 8;
            (*swaps)++;
            swap(&v[left], &v[right]);
        }

        int index_pivot = partition(v, left, right, comps, swaps, arrayCT)[2];
        quick_sort(v, left, index_pivot - 1, comps, swaps, arrayCT);
        quick_sort(v, index_pivot + 1, right, comps, swaps, arrayCT);	
	}

    arrayCT[0] = *comps;
    arrayCT[1] = *swaps;

    return arrayCT;
}

long long int* partition(int v[], int left, int right, long long int *comps, long long int *swaps, long long int *arrayCT) {
    int pivot = v[left];
    int i = left;
    int j;

    for (j = left + 1; j <= right; j++) {
        (*comps)++;
        if (v[j] <= pivot) {
            (*swaps)++;
            i+=1;
            swap(&v[i], &v[j]);
        }
    }
    (*swaps)++;
    swap(&v[left], &v[i]);

    arrayCT[0] = *comps;
    arrayCT[1] = *swaps;
    arrayCT[2] = i;
    
    return arrayCT; 
}

long long int* merge_sort(int v[], int left, int right, long long int *comps, long long int *swaps, long long int *arrayCT) {   
    int mid;

    if (left < right) {
        mid = floor((left + right) / 2);
        merge_sort(v, left, mid, comps, swaps, arrayCT);
        merge_sort(v, mid + 1, right, comps, swaps, arrayCT);
        merge(v, left, mid, right, comps, swaps, arrayCT);
    }

    arrayCT[0] = *comps;
    arrayCT[1] = *swaps;

    return arrayCT;
}

long long int* merge(int v[], int left, int mid, int right, long long int *comps, long long int *swaps, long long int *arrayCT) {
    int *temp, p1, p2, size, i, j, k, fim1 = 0, fim2 = 0;
    size = right - left + 1;
    p1 = left;
    p2 = mid + 1;

    temp = (int*) malloc (size * sizeof(int));
    
    if (temp != NULL) {
        for (i = 0; i < size; i++) {

            if (!fim1 && !fim2) {
                (*comps)++;
                if (v[p1] < v[p2]) {
                    (*swaps)++;
                    temp[i] = v[p1++];
                    //printf("TESTE 1\n");
                }
                else {
                    (*swaps)++;
                    temp[i] = v[p2++];
                    //printf("TESTE 2\n");
                }

                if (p1 > mid) {
                    (*swaps)++;
                    fim1 = 1;
                    //printf("TESTE 3\n");
                }

                if (p2 > right) {
                    (*swaps)++;
                    fim2 = 1;
                    //printf("TESTE 4\n");
                }

            } else {
                (*comps)++;
                if (!fim1) {
                    (*swaps)++;
                    temp[i] = v[p1++];
                    //printf("TESTE 5\n");
                } else {
                    (*swaps)++;
                    temp[i] = v[p2++];
                    //printf("TESTE 6\n"); // Crasha o programa com n >= 90000
                }
            }
        }

        for (j = 0, k = left; j < size; j++, k++) {
            v[k] = temp[j];
            //printf("TESTE 7\n");
        }
    }

    free(temp);

    arrayCT[0] = *comps;
    arrayCT[1] = *swaps;

    return arrayCT;

}

long long int* bead_sort(int vet[], int m, int n, long long int *comps, long long int *swaps, long long int *arrayCT) {
    long long int sum, max, i, j;
    unsigned char *beads;

    n++;

    // Encontra o elemento máximo no array 
    for (i = 1, max = vet[0]; i < n; i++) {
        (*comps)++;
        if (vet[i] > max) {
            max = vet[i];
        }
    }

    // Aloca memória para o array de contas
    beads = calloc(1, max * n);

    // Marca as contas
    for (i = 0; i < n; i++) {
        (*swaps)++;
        for (j = 0; j < vet[i]; j++) {
            BEAD(i, j) = 1;
        }
    }

    // Conta o número de contas em cada poste
    for (j = 0; j < max; j++) {
        for (sum = i = 0; i < n; i++) {
            sum += BEAD(i, j);
            BEAD(i, j) = 0;
        }
        // Marca as contas na parte inferior
        for (i = n - sum; i < n; i++) {
            BEAD(i, j) = 1;
        }
    }

    // Atribui os valores ordenados de volta ao array
    for (i = 0; i < n; i++) {
        for (j = 0; j < max && BEAD(i, j); j++);
        vet[i] = j;
    }

    // Libera a memória alocada
    free(beads);

    arrayCT[0] = *comps;
    arrayCT[1] = *swaps;

    return arrayCT;

}