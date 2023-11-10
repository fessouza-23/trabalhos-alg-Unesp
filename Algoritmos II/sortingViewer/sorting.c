#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

#include "sorting.h"

FILE *manipularArquivo(const char *nomeArquivo, const char *modo) {
    FILE *arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }
    return arquivo;
}

int shuffleArray(int vet[], int n) {
    int i, j, temp, count = 0;
    int size = sizeof(*vet) / sizeof(vet[0]);
    double nextDouble;

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

int shuffleArrayFixedFactor(int vet[], int n) {
    int i, j, temp, count = 0;
    int size = sizeof(*vet) / sizeof(vet[0]);
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

int shuffleArrayRandomFactor(int vet[], int n) {
    int i, j, temp, count = 0;
    int size = sizeof(*vet) / sizeof(vet[0]);
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

void troca(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void getSortData(int* (*f)(int*, int), int *vet, int n) {
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

    shuffleArray(vet, n);
}

int* bubble_sort(int vet[], int n) {
    int i, j, houve_troca = 1, comps = 0, trocas = 0;
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
    int i, j, aux, comps = 0, trocas = 0;
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
    int i, j, min_ind, comps = 0, trocas = 0;
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
    int i, j, k, aux, comps = 0, trocas = 0;
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

int partition(int v[], int left, int right) {
    int pivot = v[left];
    int i = left;
    int j;

    for (j = left + 1; j <= right; j++) {
        //comps++;
        if (v[j] <= pivot) {
            i+=1;
            //trocas++;
            troca(&v[i], &v[j]);
        }
    }
    //trocas++;
    troca(&v[left], &v[i]); //função auxilar
    
    return i; 
}

void quick_sort(int v[], int left, int right) {
	if (left < right) {
        int med = (left+right)/2;
        if (v[left] <= v[med] && v[left] >= v[right]){
            //comps += 2;
        }
        else if (v[left] >= v[med] && v[left] <= v[right]){
            //comps += 4;
        }
        else if (v[med] <= v[left] && v[med] >= v[right]){
            //comps += 6;
            //trocas++;
            troca(&v[left], &v[med]);
        }
        else if (v[med] >= v[left] && v[med] <= v[right]){
            //comps += 8;
            //trocas++;
            troca(&v[left], &v[med]);
        } 
        else {
            //comps += 8;
            //trocas++;
            troca(&v[left], &v[right]);
        }
		int index_pivot = partition(v, left, right);
		quick_sort(v, left, index_pivot - 1);
		quick_sort(v, index_pivot + 1, right);	
	}
}

void merge(int v[], int inicio, int meio, int fim) {
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;
    temp = (int*) malloc (tamanho * sizeof(int));
    if (temp != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (!fim1 && !fim2) {
                if (v[p1] < v[p2])
                    temp[i] = v[p1++];
                else
                    temp[i] = v[p2++];
                if (p1 > meio) fim1 = 1;
                if (p2 > meio) fim2 = 1;
            } else {
                if (!fim1)
                    temp[i] = v[p1++];
                else
                    temp[i] = v[p2++];
            }
        }
        for (j = 0, k = inicio; j < tamanho; j++, k++)
            v[k] = temp[j];
    }
    free(temp);
}

void merge_sort(int v[], int inicio, int fim) {   
    int meio;
    if (inicio < fim) {
        meio = floor((inicio + fim) / 2);
        merge_sort(v, inicio, meio);
        merge_sort(v, meio + 1, fim);
        merge(v, inicio, meio, fim);
    }
}

//Dropsort original
int dropSort(int *arr, int size, int *sortedArr) {
    int newSize = 1, i, comps = 0, trocas = 0, arraySize = 0;

    shuffleArray(arr, size);

    sortedArr[0] = arr[0];
    for (i = 1; i < size; ++i) {
        if (arr[i] >= sortedArr[newSize-1]) {
            comps++;
            trocas++;
            ++newSize;
            sortedArr[newSize-1] = arr[i];
        } else {
            comps++;
        }
    }

    for (i = 0; i < newSize; i++) {
        //printf("%d ", sortedArr[i]);
        arraySize++;
    }

    return arraySize;
}

//Recent Memory
int dropSortRecMem(int *arr, int size, int *sortedArr) {
    int newSize = 1, i, count = 0, j, temp = 0, comps = 0, trocas = 0, arraySize = 0;

    shuffleArray(arr, size);

    //printf("\n");

    sortedArr[0] = arr[0];
    arraySize++;
    for (i = 1; i < size; i++) {
        if (arr[i] >= sortedArr[newSize-1]) {
            ++newSize;
            sortedArr[newSize - 1] = arr[i];
            comps++;
            trocas++;
            arraySize++;
        } else {
            count++;
            if (count >= 4) {
                count = 0;
                --newSize;
                sortedArr[newSize] = arr[i];
                comps++;
                trocas++;
                arraySize--;
            }
        }
    }

    /*for (i = 0; i < newSize; i++) {
        //printf("%d ", sortedArr[i]);
        arraySize++;
    }*/

    return arraySize;
}

//Double Comparison
int dropSortDoubleComparison(int *arr, int size, int *sortedArr) {
    int newSize = 1, i, comps = 0, trocas = 0, arraySize = 0;

    shuffleArray(arr, size);

    //printf("\n");

    sortedArr[0] = arr[0];
    for (i = 1; i < size; ++i) {
        if (arr[i] >= sortedArr[newSize-1] && arr[i] < arr[i + 1]) {
            comps++;
            trocas++;
            ++newSize;
            sortedArr[newSize-1] = arr[i];
        } else {
            comps++;
        }
    }

    for (i = 0; i < newSize; i++) {
        //printf("%d ", sortedArr[i]);
        arraySize++;
    }

    return arraySize;
}

//Recent Memory and Double Comparison
int dropSortRecMemAndDoubleComparison(int *arr, int size, int *sortedArr) {
    int newSize = 1, i, count = 0, j, temp = 0, comps = 0, trocas = 0, arraySize = 0;

    shuffleArray(arr, size);

    //printf("\n");

    sortedArr[0] = arr[0];
    ++arraySize;
    for (i = 1; i < size; ++i) {
        if (arr[i] >= sortedArr[newSize-1]) {
            ++newSize;
            sortedArr[newSize - 1] = arr[i];
            comps++;
            trocas++;
            ++arraySize;
        } else {
            count++;
            if (count >= 4) {
                count = 0;
                --newSize;
                sortedArr[newSize] = arr[i];
                comps++;
                trocas++;
                arraySize--;
            }
        }
    }

    return arraySize;
}