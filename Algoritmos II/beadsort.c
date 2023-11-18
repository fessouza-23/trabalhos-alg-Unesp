#include <stdio.h>
#include <stdlib.h>

// Função para realizar a ordenação Bead Sort em um array
void bead_sort(int *a, int len) {
  int i, j, max, sum;
  unsigned char *beads;

  // Define uma macro para acessar elementos no array de contas (beads)
#define BEAD(i, j) beads[i * max + j]

  // Encontra o elemento máximo no array
  for (i = 1, max = a[0]; i < len; i++)
    if (a[i] > max)
      max = a[i];

  // Aloca memória para o array de contas (beads)
  beads = calloc(1, max * len);

  // Marca as contas (beads)
  for (i = 0; i < len; i++)
    for (j = 0; j < a[i]; j++)
      BEAD(i, j) = 1;

  // Conta o número de contas em cada poste
  for (j = 0; j < max; j++) {
    for (sum = i = 0; i < len; i++) {
      sum += BEAD(i, j);
      BEAD(i, j) = 0;
    }

    // Marca as contas na parte inferior
    for (i = len - sum; i < len; i++)
      BEAD(i, j) = 1;
  }

  // Atribui os valores ordenados de volta ao array
  for (i = 0; i < len; i++) {
    for (j = 0; j < max && BEAD(i, j); j++);
    a[i] = j;
  }

  // Libera a memória alocada
  free(beads);
}

// Função principal
int main() {
  int i, x[] = {5, 3, 1, 7, 4, 1, 1, 20};
  int len = sizeof(x) / sizeof(x[0]);

  // Exibe o array original
  printf("Array Original:\n");
  for (i = 0; i < len; i++)
    printf("%d%s", x[i], i == len - 1 ? "\n" : " ");

  // Ordena o array usando o Bead Sort
  bead_sort(x, len);

  // Exibe o array ordenado
  printf("\nArray Ordenado:\n");
  for (i = 0; i < len; i++)
    printf(" %d", x[i]);

  return 0;
}