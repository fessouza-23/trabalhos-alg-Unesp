#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int comps, trocas, arraySize;
LARGE_INTEGER frequency;
LARGE_INTEGER start;
LARGE_INTEGER end;
double elapsed_time;

//Funcao para embaralhar o vetor (adaptação do Fisher–Yates shuffle)
int shuffleArray(int vet[], int n) {
    int i, j, temp, count = 0;
    int size = sizeof(*vet) / sizeof(vet[0]);
    double randomizationFactor = 0.7; //Grau de randomizacao
    double nextDouble;

    srand(time(NULL));

    count = 0;

    for (i = n - 1; i > 0; i--) {
        //randomizationFactor = (double)rand() / (double)RAND_MAX;
        nextDouble = (double)rand() / (double)RAND_MAX;
        if (nextDouble < randomizationFactor) {
            j = rand() % n;
            temp = vet[i];
            vet[i] = vet[j];
            vet[j] = temp;
        }
    }

    return *vet;
}

//Dropsort original
int dropSort(int *arr, int size, int *sortedArr) {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    int newSize = 1, i;

    comps = trocas = arraySize = 0;

    //shuffleArray(arr, size);

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
        arraySize++;
    }

    QueryPerformanceCounter(&end);
    elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    return arraySize;
}

//Recent Memory
int dropSortRecMem(int *arr, int size, int *sortedArr) {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    int newSize = 1, i, count = 0, j, temp = 0;

    comps = trocas = arraySize = 0;

    //shuffleArray(arr, size);

    sortedArr[0] = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] >= sortedArr[newSize-1]) {
            ++newSize;
            sortedArr[newSize-1] = arr[i];
            comps++;
            trocas++;
        } else if (arr[i] < sortedArr[newSize-1]){
            count++;
            if (count >= 4) {
                count = 0;
                sortedArr[newSize - 1] = arr[i];
                comps++;
                trocas++;
            }
        }
    }

    for (i = 0; i < newSize; i++) {
        arraySize++;
    }

    QueryPerformanceCounter(&end);
    elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    return arraySize;
}

//Double Comparison
int dropSortDoubleComparison(int *arr, int size, int *sortedArr) {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    int newSize = 1, i;

    comps = trocas = arraySize = 0;

    //shuffleArray(arr, size);

    sortedArr[0] = arr[0];
    for (i = 1; i < size; ++i) {
        if (arr[i] >= sortedArr[newSize-1] && arr[i] <= arr[i + 1]) {
            comps++;
            trocas++;
            ++newSize;
            sortedArr[newSize-1] = arr[i];
        } else {
            comps++;
        }
    }

    for (i = 0; i < newSize; i++) {
        arraySize++;
    }

    QueryPerformanceCounter(&end);
    elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    return arraySize;
}

//Recent Memory
int dropSortRecMemAndDoubleComparison(int *arr, int size, int *sortedArr) {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    int newSize = 1, i, count = 0, j, temp = 0;

    comps = trocas = arraySize = 0;

    //shuffleArray(arr, size);

    sortedArr[0] = arr[0];
    for (i = 1; i < size; ++i) {
        if (arr[i] >= sortedArr[newSize-1] && arr[i] <= arr[i + 1]) {
            ++newSize;
            sortedArr[newSize-1] = arr[i];
            comps++;
            trocas++;
        } else {
            count++;
            if (count >= 4) {
                count = 0;
                sortedArr[newSize - 1] = arr[i];
                comps++;
                trocas++;
            }
        }
    }

    for (i = 0; i < newSize; i++) {
        arraySize++;
    }

    QueryPerformanceCounter(&end);
    elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    return arraySize;
}

int main()
{

    system("cls");

    int vet[] = {1, 10, 2, 3, 4, 5, 6, 7, 8, 9};

    int i, n1 = 10;

    int vetOrd1[10];

    FILE *file;

    printf("\n--------------------------------\n");

    printf("Vetor ordenado: \n");

    for (i = 0 ; i < n1; i++) {
        printf("%d ", vet[i]);
    }

    printf("\n--------------------------------\n");

    printf("Dropsort classico: \n");

    dropSort(vet, n1, vetOrd1);

    for (i = 0 ; i < arraySize; i++) {
        printf("%d ", vetOrd1[i]);
    }

    printf("\n--------------------------------\n");

    printf("Dropsort Recent Memory: \n");

    dropSortRecMem(vet, n1, vetOrd1);

    for (i = 0 ; i < arraySize; i++) {
        printf("%d ", vetOrd1[i]);
    }

    printf("\n--------------------------------\n");

    printf("Dropsort Double Comparison: \n");

    dropSortDoubleComparison(vet, n1, vetOrd1);

    for (i = 0 ; i < arraySize; i++) {
        printf("%d ", vetOrd1[i]);
    }

    printf("\n--------------------------------\n");

    printf("Dropsort Recent Memory and Double Comparison: \n");

    dropSortRecMemAndDoubleComparison(vet, n1, vetOrd1);

    for (i = 0 ; i < arraySize; i++) {
        printf("%d ", vetOrd1[i]);
    }

    getchar();
}