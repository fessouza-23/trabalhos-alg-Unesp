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

        if (*m <= 0)
            printf("Valor invalido.\n");
    } while (*m <= 0);

    do {
        printf("Digite a quantidade de colunas: ");
        scanf("%d", n);

        if (*n <= 0)
            printf("Valor invalido.\n");
    } while (*n <= 0);
}

void lerMatriz(int v[][100], int m, int n) {
    int i, j;

    system("cls");
    printf("Matriz de dimensao %d x %d\n", m, n);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("Elemento[%d][%d]: ", i, j);
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
            printf("%2d ", v[i][j]);
        }
        printf("\n");
    }
    system("pause");
}

void trocarLinhas(int v[][100], int m, int n) {
    int linhaX, linhaY;

    system("cls");
    printf("Digite o valor da linha X: ");
    scanf("%d", &linhaX);

    printf("Digite o valor da linha Y: ");
    scanf("%d", &linhaY);

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
}

void matrizSimetrica(int v[][100], int n, int m) {
    int i, j;

    system("cls");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (v[i][j] != v[j][i]) {
                printf("Matriz nao eh simetrica!\n");
                system("pause");
                return;
            }
        }
    }
    printf("Matriz eh simetrica!\n");
    system("pause");
}


void menu(int v[][100], int m, int n) {
    char c;

    do {
        system("cls");
        printf("================================  MENU  =======================================\n");
        printf("1 - Gerar nova matriz\n");
        printf("2 - Mostrar matriz\n");
        printf("3 - Trocar os elementos da linha X pela linha Y\n");
        printf("4 - Trocar os elementos da coluna X pela coluna Y\n");
        printf("5 - Trocar os elementos da diagonal principal com a diagonal secundaria\n");
        printf("6 - Verificar se uma matriz eh simetrica\n");
        printf("7 - Verificar se uma matriz eh um quadrado magico\n");
        printf("8 - Verificar se uma matriz eh quadrado latino.\n");
        printf("9 - Verificar se uma matriz eh matriz de permutacao\n");
        printf("F1 - Help\n");
        printf("ESC - Sair\n\n");

        printf("Comando: ");
        c = getch();
        if ((c < '1' || c > '8') && c != esc && c != 112) {
            printf("Valor invalido.\n");
            system("pause");
        }

        switch (c) {
            case '1':
                lerDimensao(&m, &n);
                lerMatriz(v, m, n);
                mostrarMatriz(v, m, n);
                break;

            case '2':
                mostrarMatriz(v, m, n);
                break;

            case '3':
                trocarLinhas(v, m, n);
                mostrarMatriz(v, m, n);
                break;

            case '4':
                printf("Funcao nao implementada.\n");
                system("pause");
                break;

            case '5':
                printf("Funcao nao implementada.\n");
                system("pause");
                break;

            case '6':
                matrizSimetrica(v, m, n);
                break;

            case '7':
                printf("Funcao nao implementada.\n");
                system("pause");
                break;

            case '8':
                printf("Funcao nao implementada.\n");
                system("pause");
                break;
            
            case '9':
                printf("Funcao nao implementada.\n");
                system("pause");
                break;

            default:
                printf("Comando desconhecido!\n");
                system("pause");
                break;
        }
    } while (c != esc);
}

int main() {
    int m, n;
    lerDimensao(&m, &n);

    int v[100][100];
    lerMatriz(v, m, n);

    menu(v, m, n);

    return 0;
}
