#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int i, j, temp, count = 0;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (i = 0; i < 8; i++) {
        printf("%d", arr[i]);
    }

    srand(time(NULL));

    for (i = n - 1; i > 0; i--) {
        if (rand() % 2) {
            j = rand() % (i + 1);
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp; 
            count++;
        }
    }

    printf("\n\n");

    for (i = 0; i < n; i++) {
        printf("%d", arr[i]);
    }

    float perc = (float)count / n;

    printf("\nNumero de trocas: %d", count);
    printf("\nGrau de ordenacao (0 - Totalmente ordenado; 1 - Totalmente desordenado)\n%.3f", perc);

    printf("\n\n");

}