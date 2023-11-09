#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

#define ESC 27
#define F1 59
#define F2 60

#define linhas 9

// Variáveis globais
int n; // tamanho do vetor

/*
    Como funciona a organização da matriz de vetores:
    Cada linha representa um vetor, estes vetores são iguais para cada linha,
    a fim de que cada algoritmo de ordenação trabalhe com a mesma aleatoriedade,
    fazendo com que as comparações sejam justas.

    Qual algoritmo ordena cada linha:
    0. SelectionSort
    1. BubbleSort
    2. InsertionSort
    3. ShellSort
    4. MergeSort
    5. QuickSort
    6. DropSort
    7. DropSort Recent Memory
    8. DropSort Double Comparisons
*/

FILE *abrirArquivo(const char *nomeArquivo, const char *modo) {
  FILE *arquivo = fopen(nomeArquivo, modo);
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
    exit(EXIT_FAILURE);
  }
  return arquivo;
}

void sobre() {
  system("cls");
  printf("================================  SOBRE O PROGRAMA  "
         "=======================================\n");
  printf("Programa desenvolvido por Eduardo Teixeira, Joao V. F. Souza,\n"
         "Gabriel Rasi e Guilherme S. para a disciplina de Algoritmos II do "
         "curso de BSI\n");
  printf("Criado em 2023\n");
  printf("Pressione qualquer tecla para voltar ao menu.\n");
  getch();
}

void troca(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void selectionSort(int vetoresAleatorios[linhas][n]) {
  int i, j, min_ind, comparacoes = 0, trocas = 0;

  for (i = 0; i < n - 1; i++) {
    min_ind = i;
    for (j = i + 1; j < n; j++) {
      comparacoes++;
      if (vetoresAleatorios[0][j] < vetoresAleatorios[0][min_ind]) {
        min_ind = j;
      }
    }
    if (min_ind != i) {
      troca(&vetoresAleatorios[0][min_ind], &vetoresAleatorios[0][i]);
      trocas++;
    }
  }

  printf("\n=============================  SELECTION SORT  "
         "====================================\n");

  printf("\ncomparacoes: %d\ntrocas: %d\n", comparacoes, trocas);
}

void bubbleSort(int vetoresAleatorios[linhas][n]) {
  int i, j, houve_troca = 1, comparacoes = 0, trocas = 0;

  for (i = 0; i < n - 1 && houve_troca; i++) {
    houve_troca = 0;
    for (j = 0; j < n - i - 1; j++) {
      comparacoes++;
      if (vetoresAleatorios[1][j] > vetoresAleatorios[1][j + 1]) {
        troca(&vetoresAleatorios[1][j], &vetoresAleatorios[1][j + 1]);
        houve_troca = 1;
        trocas++;
      }
    }
  }

  printf("\n=============================  BUBBLE SORT  "
         "====================================\n");

  printf("\ncomparacoes: %d\ntrocas: %d\n", comparacoes, trocas);
}

void insertionSort(int vetoresAleatorios[linhas][n]) {
  int i, j, aux, comparacoes = 0, trocas = 0;

  for (i = 1; i < n; i++) {
    aux = vetoresAleatorios[2][i];
    j = i - 1;

    comparacoes++;

    while (j >= 0 && aux < vetoresAleatorios[2][j]) {
      vetoresAleatorios[2][j + 1] = vetoresAleatorios[2][j];
      trocas++;
      j--;
    }

    vetoresAleatorios[2][j + 1] = aux;
    trocas++;
  }

  printf("\n=============================  INSERTION SORT  "
         "====================================\n");

  printf("\ncomparacoes: %d\ntrocas: %d\n", comparacoes, trocas);
}

void shellSort(int vetoresAleatorios[linhas][n]) {
  int i, j, k, aux, trocas = 0, comparacoes = 0;

  for (k = n / 2; k > 0; k /= 2) {
    for (i = k; i < n; i++) {
      aux = vetoresAleatorios[3][i];
      comparacoes++;

      for (j = i - k; j >= 0 && aux < vetoresAleatorios[3][j]; j -= k) {
        vetoresAleatorios[3][j + k] = vetoresAleatorios[3][j];
        trocas++;
      }

      vetoresAleatorios[3][j + k] = aux;
      trocas++;
    }
  }

  printf("\n=============================  SHELL SORT  "
         "====================================\n");

  printf("\ncomparacoes: %d\ntrocas: %d\n", comparacoes, trocas);
}

void merge(int arr[], int left, int mid, int right, int *comparacoes,
           int *trocas) {
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  int L[n1], R[n2];

  for (i = 0; i < n1; i++) {
    L[i] = arr[left + i];
  }
  for (j = 0; j < n2; j++) {
    R[j] = arr[mid + 1 + j];
  }

  i = 0;
  j = 0;
  k = left;
  while (i < n1 && j < n2) {
    (*comparacoes)++;
    if (L[i] <= R[j]) {
      (*trocas)++;
      arr[k] = L[i];
      i++;
    } else {
      (*trocas)++;
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    (*trocas)++;
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    (*trocas)++;
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int left, int right, int *comparacoes, int *trocas) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid, comparacoes, trocas);
    mergeSort(arr, mid + 1, right, comparacoes, trocas);

    merge(arr, left, mid, right, comparacoes, trocas);
  }
}

void callMergeSort(int vetoresAleatorios[linhas][n]) {
  int i, comparacoes = 0, trocas = 0;
  for (i = 0; i < n; i++) {
    mergeSort(vetoresAleatorios[4], 0, n - 1, &comparacoes, &trocas);
  }

  printf("\n=============================  MERGE SORT  "
         "====================================\n");

  printf("\ncomparacoes: %d\ntrocas: %d\n", comparacoes, trocas);
}

void quickSort(int arr[], int left, int right, int *comparacoes, int *trocas) {
  int i = left, j = right;
  int pivot = arr[(left + right) / 2];

  while (i <= j) {
    while (arr[i] < pivot) {
      (*comparacoes)++;
      i++;
    }
    while (arr[j] > pivot) {
      (*comparacoes)++;
      j--;
    }
    if (i <= j) {
      (*trocas)++;
      troca(&arr[i], &arr[j]);
      i++;
      j--;
    }
  }

  if (left < j) {
    quickSort(arr, left, j, comparacoes, trocas);
  }
  if (i < right) {
    quickSort(arr, i, right, comparacoes, trocas);
  }
}

void callQuickSort(int vetoresAleatorios[linhas][n]) {
  int i, comparacoes = 0, trocas = 0;
  for (i = 0; i < n; i++) {
    quickSort(vetoresAleatorios[5], 0, n - 1, &comparacoes, &trocas);
  }

  printf("\n=============================  QUICKSORT  "
         "====================================\n");

  printf("\ncomparacoes: %d\ntrocas: %d\n", comparacoes, trocas);
}

void dropSort(int vetoresAleatorios[linhas][n]) {
  int i, j = 1, previousInt = vetoresAleatorios[6][0];
  int trocas = 0, comparacoes = 0, retidos = 1;
  int *newVet = malloc(sizeof(int)); // Aloca memória para o vetor dinâmico
  int tam = 1;

  newVet[0] = vetoresAleatorios[6][0];

  if (newVet == NULL) {
    printf("Erro ao alocar memória para o vetor\n");
    return;
  }

  for (i = 1; i < n; i++) {
    comparacoes++;
    if (vetoresAleatorios[6][i] >= previousInt) {
      newVet[j] = vetoresAleatorios[6][i];
      previousInt = vetoresAleatorios[6][i];
      j++;

      // Aumenta o tamanho do vetor dinâmico usando realloc
      int *temp = realloc(newVet, (j + 1) * sizeof(int));
      retidos++;
      if (temp == NULL) {
        printf("Erro ao realocar memória para o vetor\n");
        free(newVet); // Libera a memória alocada anteriormente
        return;
      }
      newVet = temp;
    }
  }

  // Atualiza o tamanho do vetor após a ordenação
  tam = j;

  // Imprime o vetor após a ordenação
  printf("\n=============================  DROP SORT  "
         "====================================\n");
  for (i = 0; i < tam; i++) {
    printf("%d ", newVet[i]);
  }
  printf("\ncomparacoes: %d\ntrocas: %d\ntamanho: %d\n", comparacoes, trocas,
retidos);

  // Libera a memória alocada para o vetor dinâmico
  free(newVet);
}

/*
void dropSortRecentMemory(int vetoresAleatorios[linhas][n]) {
  int newSize = 1, i, count = 0, previousInt = vetoresAleatorios[7][0];
  int comps = 0, trocas = 0;

  for (i = 1; i < n; ++i) {
    comps++;
    if (arr[i] >= previousInt) {
      ++newSize;
      arr[newSize - 1] = arr[i];
      previousInt = arr[i];
      trocas++;
    } else {
      count++;
      if (count >= 4) {
        arr[newSize - 1] = arr[i];
        trocas++;
      }
    }
  }

  printf("\n=============================  DROP SORT RECENT MEMORY  "
         "====================================\n");

  printf("\ncomparacoes: %d\ntrocas: %d\n", comps, trocas);
}

void dropSortDoubleComparison(int *arr, int size) {
  int newSize = 1, i;
  int comps = 0, trocas = 0;

  for (i = 1; i < size; ++i) {
    comps++;
    if (arr[i] >= arr[newSize - 1] &&
        (i + 1 < size ? arr[i] <= arr[i + 1] : true)) {
      ++newSize;
      arr[newSize - 1] = arr[i];
      trocas++;
    } else {
      comps++;
    }
  }

  printf("\n=============================  DROP SORT DOUBLE COMPARISON "
         "====================================\n");

  printf("\ncomparacoes: %d\ntrocas: %d\n", comps, trocas);
}
*/
/*
  Função para chamar todas as funções de ordenação de uma vez só
  e evitar repetição de código para cada tipo de vetor (aleatorio, crescente,
  decrescente, parcialmente ordenado)
*/
void callSortingFuncs(int vetoresAleatorios[linhas][n]) {
  LARGE_INTEGER frequency;
  LARGE_INTEGER start;
  LARGE_INTEGER end;
  double elapsed_time;

  // Obtém a frequência do contador de desempenho
  QueryPerformanceFrequency(&frequency);

  // Marca o início do intervalo que você deseja medir
  QueryPerformanceCounter(&start);

  // Função de ordenação que está contando o tempo
  selectionSort(vetoresAleatorios);

  // Marca o final do intervalo que você deseja medir
  QueryPerformanceCounter(&end);

  // Calcula o tempo decorrido em segundos
  elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

  // Calcula o tempo decorrido em milissegundos
  elapsed_time *= 1000;

  printf("Tempo decorrido: %f milissegundos\n", elapsed_time);

  QueryPerformanceCounter(&start);
  bubbleSort(vetoresAleatorios);
  QueryPerformanceCounter(&end);
  elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
  elapsed_time *= 1000;
  printf("Tempo decorrido: %f milissegundos\n", elapsed_time);

  QueryPerformanceCounter(&start);
  insertionSort(vetoresAleatorios);
  QueryPerformanceCounter(&end);
  elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
  elapsed_time *= 1000;
  printf("Tempo decorrido: %f milissegundos\n", elapsed_time);

  QueryPerformanceCounter(&start);
  shellSort(vetoresAleatorios);
  QueryPerformanceCounter(&end);
  elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
  elapsed_time *= 1000;
  printf("Tempo decorrido: %f milissegundos\n", elapsed_time);

  QueryPerformanceCounter(&start);
  callMergeSort(vetoresAleatorios);
  QueryPerformanceCounter(&end);
  elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
  elapsed_time *= 1000;
  printf("Tempo decorrido: %f milissegundos\n", elapsed_time);

  QueryPerformanceCounter(&start);
  callQuickSort(vetoresAleatorios);
  QueryPerformanceCounter(&end);
  elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
  elapsed_time *= 1000;
  printf("Tempo decorrido: %f milissegundos\n", elapsed_time);

  QueryPerformanceCounter(&start);
  dropSort(vetoresAleatorios);
  QueryPerformanceCounter(&end);
  elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
  elapsed_time *= 1000;
  printf("Tempo decorrido: %f milissegundos\n", elapsed_time);
}

void vetorAleatorio() {
  int i = 0, j;
  FILE *file;
  char c;

  system("cls");
  do {
    printf("================================  VETOR ALEATORIO "
           "=======================================\n");
    printf("Selecionar tamanho do vetor: \n");
    printf("|ESC - Voltar |\n");
    printf("1 - 10 Valores\n");
    printf("2 - 100 Valores\n");
    printf("3 - 1000 Valores\n");
    c = getch();

    if ((c < '1' || c > '4') && c != ESC && c != 0 && c != F1 && c != F2) {
      printf("Valor invalido.\n");
      system("pause");
    }

    if (c == ESC) {
      return;
    }

    switch (c) {
    case '1':
      n = 10;
      break;

    case '2':
      n = 100;
      break;

    case '3':
      n = 1000;
      break;
    }
  } while ((c < '1' || c > '3') && c != ESC);

  int vetoresAleatorios[linhas][n];

  if (n == 10) {
    file = abrirArquivo("10_random_values.txt", "r");
  } else if (n == 100) {
    file = abrirArquivo("100_random_values.txt", "r");
  } else {
    file = abrirArquivo("1000_random_values.txt", "r");
  }

  while (fscanf(file, "%d", &vetoresAleatorios[0][i]) == 1) {
    i++;
  }

  fclose(file);

  // copia primeira linha para as sucessivas linhas
  for (i = 1; i < linhas; i++) {
    for (j = 0; j < n; j++) {
      vetoresAleatorios[i][j] = vetoresAleatorios[0][j];
    }
  }

  system("cls");

  for (i = 0; i < linhas; i++) {
    printf("Linha %d: ", i);
    for (j = 0; j < n; j++) {
      printf("%d ", vetoresAleatorios[i][j]);
    }
    printf("\n\n");
  }

  callSortingFuncs(vetoresAleatorios);

  system("pause");
}

void vetorCrescente() {
  int i = 0, j;
  FILE *file;
  char c;

  system("cls");
  do {
    printf("================================  VETOR CRESCENTE "
           "=======================================\n");
    printf("Selecionar tamanho do vetor: \n");
    printf("|ESC - Voltar |\n");
    printf("1 - 10 Valores\n");
    printf("2 - 100 Valores\n");
    printf("3 - 1000 Valores\n");
    c = getch();

    if ((c < '1' || c > '4') && c != ESC && c != 0 && c != F1 && c != F2) {
      printf("Valor invalido.\n");
      system("pause");
    }

    if (c == ESC) {
      return;
    }

    switch (c) {
    case '1':
      n = 10;
      break;

    case '2':
      n = 100;
      break;

    case '3':
      n = 1000;
      break;
    }
  } while ((c < '1' || c > '3') && c != ESC);

  int vetoresAleatorios[linhas][n];

  if (n == 10) {
    file = abrirArquivo("10_random_values.txt", "r");
  } else if (n == 100) {
    file = abrirArquivo("100_random_values.txt", "r");
  } else {
    file = abrirArquivo("1000_random_values.txt", "r");
  }

  while (fscanf(file, "%d", &vetoresAleatorios[0][i]) == 1) {
    i++;
  }

  fclose(file);

  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (vetoresAleatorios[0][i] > vetoresAleatorios[0][j]) {
        troca(&vetoresAleatorios[0][i], &vetoresAleatorios[0][j]);
      }
    }
  }

  // copia primeira linha para as sucessiva linhas
  for (i = 1; i < linhas; i++) {
    for (j = 0; j < n; j++) {
      vetoresAleatorios[i][j] = vetoresAleatorios[0][j];
    }
  }

  system("cls");

  for (i = 0; i < linhas; i++) {
    printf("Linha %d: ", i);
    for (j = 0; j < n; j++) {
      printf("%d ", vetoresAleatorios[i][j]);
    }
    printf("\n\n");
  }

  callSortingFuncs(vetoresAleatorios);

  system("pause");
}

int main() {
  char c;

  do {
    system("cls");
    printf("================================  MENU  "
           "=======================================\n");
    printf("|ESC - Sair | F1 - Ajuda | F2 - Sobre o Programa|\n");
    printf("1 - Vetor em ordem aleatoria\n");
    printf("2 - Vetor em ordem crescente\n");
    printf("3 - Vetor em ordem decrescente\n");
    printf("4 - Vetor parcialmente ordenado\n");
    c = getch();

    if ((c < '1' || c > '4') && c != ESC && c != 0 && c != F1 && c != F2) {
      printf("Valor invalido.\n");
      system("pause");
    }

    switch (c) {
    case '1':
      vetorAleatorio();
      break;

    case '2':
      vetorCrescente();
      break;

    case '3':
      break;

    case '4':
      break;

    case '5':
      break;

    case '6':
      break;

    case '7':
      break;

    case '8':
      break;

    case '9':
      break;

    case F1:
      // help();
      break;

    case F2:
      sobre();
      break;
    }
  } while (c != ESC);

  return 0;
}