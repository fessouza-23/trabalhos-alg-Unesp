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
    char menu_option;

    // Vetor do tipo "SortFunction". Este vetor possui os ponteiros para as funções de ordenação
    SortFunction bufferAlgos[] = {quick_sort, merge_sort, shell_sort, insertion_sort, selection_sort, bubble_sort, bead_sort};

    // Vetor com os nomes das funções
    const char *sortName[] = {"QUICK SORT", "MERGE SORT", "SHELL SORT", "INSERTION SORT", "SELECTION SORT", "BUBBLE SORT", "BEAD SORT"}; 

    welcome_msg();

    do {
        CLR_SCREEN

        printf("Escolha o tipo de vetor a ser ordenado:");
        printf("\n1 - Vetor nao ordenado\n2 - Vetor parcialmente ordenado\n3 - Vetor em ordem crescente\n4 - Vetor em ordem decrescente\n");

        do {
            menu_option = getchar();
            switch (menu_option) {
                case '1':
                    write_file_in_array(array_to_be_sorted);
                    break;
                case '2':
                    write_file_in_array(array_to_be_sorted);
                    break;
                case '3':
                    write_file_in_array(array_to_be_sorted);
                    break;
                case '4':
                    write_file_in_array(array_to_be_sorted);
                    break;
                default:
                    while ((menu_option = getchar()) != '\n');
                    printf("Entrada invalida! Tente novamente\n");
                    break;
            }
        } while (menu_option != '1' && menu_option != '2' && menu_option != '3' && menu_option != '4');

        while ((menu_option = getchar()) != '\n');

        get_array_size(&array_size);

        print_array_data(bufferAlgos, array_to_be_sorted, array_size, sortName);

        restart(&retry);

    } while (retry == '1');

    exit_program();

    return 0;
}