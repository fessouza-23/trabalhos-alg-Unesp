#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define esc 27

void lerDimensao(int *m, int *n) {
    system("cls");

    do {
        printf("Digite a quantidade de linhas: ");
        scanf("%d", m);

        if (*m <= 0) printf("Valor invalido.\n");
    } while (*m <= 0);

    do {
        printf("Digite a quantidade de colunas: ");
        scanf("%d", n);

        if (*n <= 0) printf("Valor invalido.\n");
    } while (*n <= 0);
}

void lerMatriz(int v[][100], int m, int n) {
    int i, j;

    system("cls");
    printf("Matriz de dimensao %d x %d\n", m, n);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("Elemento[%d][%d]: ", i+1, j+1);
            scanf("%d", &v[i][j]);
        }
    }
}

void mostrarMatriz(int v[][100], int m, int n) {
    int i, j;

    system("cls");
    printf("MATRIZ: \n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%3d ", v[i][j]);
        }
        printf("\n");
    }
    system("pause");
}

void menu(int v[][100], int m, int n) {
    int linhaX, linhaY, colunaX, colunaY;
    char c;

    do {
        system("cls");
        printf("================================  MENU  =======================================\n");
        printf("1 - Gerar nova matriz\n");
        printf("2 - Mostrar matriz\n");
        printf("3 - Trocar os elementos da linha X pela linha Y\n");
        printf("4 - Trocar os elementos da coluna X pela coluna Y\n");
        printf("5 - Trocar os elementos da diagonal principal com a diagonal secundaria\n");
        printf("6 - Verifique se uma matriz eh um quadrado magico\n");
        printf("7 - Verifique se uma matriz eh quadrado latino.\n");
        printf("8 - Verifique se uma matriz eh matriz de permutacao\n");
        printf("F1 - Help\n");
        printf("ESC - Sair\n\n");

        printf("Comando: ");
        c = getch();
        if ((c < '1' || c > '8') && c != esc && c != 112) {
            printf("Valor invalido.\n");
        }

        switch (c) {
            case '1':
                lerDimensao(&m, &n);
                lerMatriz(v, m, n);
                menu(v, m, n);
                break;
    
            case '2':
                mostrarMatriz(v, m, n);
                menu(v, m, n);
                break;

            case '3':
                printf("Digite o valor da linha X: ");
                scanf("%d", &linhaX);
                printf("Digite o valor da linha Y: ");
                scanf("%d", &linhaY);
                // Swap the elements of line X and line Y in the matrix
                if (linhaX >= 0 && linhaX < m && linhaY >= 0 && linhaY < m) {
                    int temp;
                    for (int j = 0; j < n; j++) {
                        temp = v[linhaX][j];
                        v[linhaX][j] = v[linhaY][j];
                        v[linhaY][j] = temp;
                    }
                    printf("Linhas trocadas com sucesso.\n");
                } else {
                    printf("Valores de linha invalidos.\n");
                }
                system("pause");
                break;

            case '4':
                printf("Digite o valor da coluna X: ");
                scanf("%d", &colunaX);
                printf("Digite o valor da coluna Y: ");
                scanf("%d", &colunaY);
                // Swap the elements of column X and column Y in the matrix
                if (colunaX >= 0 && colunaX < n && colunaY >= 0 && colunaY < n) {
                    int temp;
                    for (int i = 0; i < m; i++) {
                        temp = v[i][colunaX];
                        v[i][colunaX] = v[i][colunaY];
                        v[i][colunaY] = temp;
                    }
                    printf("Colunas trocadas com sucesso.\n");
                } else {
                    printf("Valores de coluna invalidos.\n");
                }
                system("pause");
                break;

            case '5':
                // Swap the elements of the main diagonal with the secondary diagonal
                if (m == n) {
                    int temp;
                    for (int i = 0; i < m; i++) {
                        temp = v[i][i];
                        v[i][i] = v[i][n - 1 - i];
                        v[i][n - 1 - i] = temp;
                    }
                    printf("Diagonais trocadas com sucesso.\n");
                } else {
                    printf("A matriz nao eh quadrada.\n");
                }
                system("pause");
                break;

            case '6':
                // Check if the matrix is a magic square
                // (not implemented in this code snippet)
                printf("Funcao nao implementada.\n");
                system("pause");
                break;

            case '7':
                // Check if the matrix is a Latin square
                // (not implemented in this code snippet)
                printf("Funcao nao implementada.\n");
                system("pause");
                break;

            case '8':
                // Check if the matrix is a permutation matrix
                // (not implemented in this code snippet)
                printf("Funcao nao implementada.\n");
                system("pause");
                break;

            default:
                printf("Comando desconhecido!\n");
                system("pause");
                break;
        }
    } while ((c < '1' || c > '8') && c != esc && c != 112);
}


int main() {
    int m, n;
    lerDimensao(&m, &n);

    int v[100][100];
    lerMatriz(v, m, n);
    menu(v, m, n);
    return 0;
}
