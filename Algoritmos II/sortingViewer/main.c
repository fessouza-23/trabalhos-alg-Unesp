#include <stdio.h>
#include "sorting.h"
#include "arrayAndFileManipulation.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

// Sorting Viewer - Visualizador de dados para algoritmos de ordenação                                       

int main(int argc, char *argv[]) {
    CLR_SCREEN;

    int vet[MAX_ARRAY_SIZE], n = 0, retry, comps, trocas, arrayCompsAndTrocas[MAX_ARGS];

    SortFunction bufferAlgos[] = {bubble_sort, insertion_sort, selection_sort, shell_sort, bead_sort};

    SortFunctionSpecial bufferAlgosSpecial[] = {quick_sort, merge_sort}; 

    const char *sortName[] = {"BUBBLE SORT", "INSERTION SORT", "SELECTION SORT", "SHELL SORT", "QUICK SORT", "MERGE SORT", "BEAD SORT"}; 

    printf("------------------------------------------------------------\n");
    printf("| Visualizador de performance para algoritmos de ordenacao |\n");
    printf("------------------------------------------------------------\n\n");

    #ifdef __GNUC__
        printf ("COMPILED ON GCC VERSION %d.%d\n\n", __GNUC__, __GNUC_MINOR__);
    #endif

    printf("Pressione qualquer tecla para continuar... ");
    getchar();

    writeFileInArray(vet);

    do {

        insertArraySize(&n);

        printArrayData(bufferAlgos, bufferAlgosSpecial, vet, n, &comps, &trocas, arrayCompsAndTrocas, sortName);

        runAgain(&retry);

    } while (retry == '1');

    exitProgram();

    return 0;
}