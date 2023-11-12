#include <stdio.h>
#include "sorting.h"
#include "arrayAndFileManipulation.h"
                                                                          
// Sorting Viewer - Visualizador de dados para algoritmos de ordenação                                       

int main() {
    int vet[100000], n, retry, comps = 0, trocas = 0, arrayCompsAndTrocas[3];

    SortFunction bufferAlgos[] = {bubble_sort, insertion_sort, selection_sort, shell_sort};

    SortFunctionSpecial bufferAlgosSpecial[] = {quick_sort, merge_sort}; 

    const char *sortName[] = {"BUBBLE SORT", "INSERTION SORT", "SELECTION SORT", "SHELL SORT", "QUICK SORT", "MERGE SORT"}; 

    writeFileInArray(vet);

    do {

        insertArraySize(&n);

        printArrayData(bufferAlgos, bufferAlgosSpecial, vet, n, &comps, &trocas, arrayCompsAndTrocas, sortName);

        runAgain(&retry);

    } while (retry == 1);

    exitProgram();

    return 0;
}