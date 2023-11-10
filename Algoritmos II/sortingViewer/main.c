#include <stdio.h>
#include <windows.h>
#include <time.h>

#include "sorting.h"

int main() {
    int vet[100000], n, i = 0, retry;

    FILE *file;

    file = manipularArquivo("random_values.txt", "r");

    while (fscanf(file, "%d, ", &vet[i]) == 1) {
        i++;
    }

    do {
        system("cls");
        do {
            printf("Digite o tamanho do vetor (MIN 1 & MAX 100000): \n");
            scanf("%d", &n);
        } while (n < MIN_ARRAY_SIZE || n > MAX_ARRAY_SIZE);

        system("cls");

        printf("-------- TAMANHO %d --------\n", n);
        printf("BUBBLE SORT\n");
        setSortData(bubble_sort, vet, n);
        printf("INSERTION SORT\n");
        setSortData(insertion_sort, vet, n);
        printf("SELECTION SORT\n");
        setSortData(selection_sort, vet, n);
        printf("SHELL SORT\n");
        setSortData(shell_sort, vet, n);

        //Alterar getSortData para receber um numero nao fixo de argumentos,
        //Assim permitindo o uso do quick sort e merge sort
        /*printf("QUICK SORT\n");
        getSortData(quick_sort, vet, 0, n-1);
        printf("MERGE SORT\n");
        getSortData(merge_sort, vet, 0, n-1);*/

        n += 10;

        //PARA GERAR VETORES DE TAMANHO CONTINUO ATE UM LIMITE:
        /*

        printf("Digite o tamanho do vetor: \n");
        scanf("%d", &n);
        
        while (n <= 100000) {
            printf("-------- TAMANHO %d --------n\n", n);
            printf("BUBBLE SORT\n");
            getSortData(bubble_sort, vet, n, 0);
            printf("INSERTION SORT\n");
            getSortData(insertion_sort, vet, n, 0);
            printf("SELECTION SORT\n");
            getSortData(selection_sort, vet, n, 0);
            printf("SHELL SORT\n");
            getSortData(shell_sort, vet, n, 0);
            printf("QUICK SORT\n");
            getSortData(quick_sort, vet, 0, n-1);
            printf("MERGE SORT\n");
            getSortData(merge_sort, vet, 0, n-1);
            n += 10;
        }
        
        */

        printf("\n\n");

        do {
            printf("Testar para novos valores (1 - SIM; 0 - NAO)?\n");
            scanf("%d", &retry);
        } while (retry != 1 && retry != 0);

    } while (retry == 1);

    printf("pause");

    system("cls");

    return 0;
}

