#include <stdio.h>
#include <stdlib.h>

int comparacoes = 0;
int trocas = 0;

void ordenacao_por_contas(int *a, int len) {
  int i, j, max, soma;
  unsigned char *contas;

  // Define uma macro para acessar elementos no array de contas
#define CONTA(i, j) contas[i * max + j]

  // Encontra o elemento máximo no array
  for (i = 1, max = a[0]; i < len; i++) {
    comparacoes++;
    if (a[i] > max) {
      max = a[i];
    }
  }

  // Aloca memória para o array de contas
  contas = calloc(1, max * len);

  // Marca as contas
  for (i = 0; i < len; i++) {
    for (j = 0; j < a[i]; j++) {
      CONTA(i, j) = 1;
    }
  }

  // Conta o número de contas em cada poste
  for (j = 0; j < max; j++) {
    for (soma = i = 0; i < len; i++) {
      soma += CONTA(i, j);
      CONTA(i, j) = 0;
      trocas++;
    }

    // Marca as contas na parte inferior
    for (i = len - soma; i < len; i++) {
      CONTA(i, j) = 1;
      trocas++;
    }
  }

  // Atribui os valores ordenados de volta ao array
  for (i = 0; i < len; i++) {
    for (j = 0; j < max && CONTA(i, j); j++);
    a[i] = j;
  }

  // Libera a memória alocada
  free(contas);
}

int main() {
  int i, x[] = {5, 3, 1, 7, 4, 1, 1, 20};
  int len = sizeof(x) / sizeof(x[0]);

  printf("Array Original:\n");
  for (i = 0; i < len; i++)
    printf("%d%s", x[i], i == len - 1 ? "\n" : " ");

  ordenacao_por_contas(x, len);

  printf("\nArray Ordenado:\n");
  for (i = 0; i < len; i++)
    printf(" %d", x[i]);

  printf("\nComparacoes: %d", comparacoes);
  printf("\nTrocas: %d", trocas);

  return 0;
}