#include <stdio.h>
#include "sorting.h"
#include "arrayAndFileManipulation.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

/*
* FAZER: 
* Alterar os tipos "comps" e "swaps" para long long int, e todas as outras
* funções envolvidas com elas;
* Criar menu para que seja possível escolher vetores em ordem completamente aleatória, em ordem
* crescente, em ordem decrescente e quase ordenado.
*/

/* 
* Sorting Benchmark Viewer - Visualizador de performance para algoritmos de ordenação  
* Este programa realiza um teste de perfomance para 7 tipos diferentes de algoritmos
* de ordenação, sendo eles: bubble sort, insertion sort, selection sort, shell sort, 
* bead sort, quick sort e merge sort. A performance é avaliada a partir de três critérios:
* número de comparações realizadas, quantidade de trocas realizadas e tempo de execução.
* O programa aceita vetores de tamanho 1 até 100000, incluso.
*/                                     

int main(int argc, char *argv[]) {
    CLR_SCREEN;

    int array_to_be_sorted[MAX_ARRAY_SIZE], array_size, retry;

    // Vetor do tipo "SortFunction". Este vetor possui os ponteiros para as funções de ordenação
    SortFunction bufferAlgos[] = {bubble_sort, insertion_sort, selection_sort, shell_sort, bead_sort, quick_sort, merge_sort};

    // Vetor com os nomes das funções
    const char *sortName[] = {"BUBBLE SORT", "INSERTION SORT", "SELECTION SORT", "SHELL SORT", "BEAD SORT", "QUICK SORT", "MERGE SORT"}; 
    
    #ifdef __GNUC__
        printf ("COMPILED ON GCC VERSION %d.%d\n\n", __GNUC__, __GNUC_MINOR__);
    #endif

    printf("------------------------------------------------------------\n");
    printf("| Visualizador de performance para algoritmos de ordenacao |\n");
    printf("------------------------------------------------------------\n\n");
    printf("Este programa realiza um teste de perfomance para 7 tipos diferentes de algoritmos\n");
    printf("de ordenacao, sendo eles: bubble sort, insertion sort, selection sort, shell sort,\n");
    printf("bead sort, quick sort e merge sort. A performance e avaliada a partir de tres criterios:\n");
    printf("numero de comparacoes realizadas, quantidade de trocas realizadas e tempo de execucao.\n");
    printf("O programa aceita vetores de tamanho 1 ate 100000, incluso.\n\n\n");


    printf("Pressione qualquer tecla para continuar... ");
    getchar();

    write_file_in_array(array_to_be_sorted);

    do {

        get_array_size(&array_size);

        print_array_data(bufferAlgos, array_to_be_sorted, array_size, sortName);

        restart(&retry);

    } while (retry == '1');

    exit_program();

    return 0;
}