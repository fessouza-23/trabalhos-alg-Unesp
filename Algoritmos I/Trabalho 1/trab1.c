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

void quadradoMagico(int v[][100], int n, int m) {
    int soma, i, j;
    int somaDiagonalPrincipal = 0;
    int somaDiagonalSecundaria = 0;

    for (i = 0; i < m; i++) {
        soma = 0;
        for (j = 0; j < n; j++) {
            soma += v[i][j];
        }
        if (soma != 15) {
            printf("Nao eh quadrado magico!\n");
            system("pause");
            return;
        }
    }

    for (j = 0; j < n; j++) {
        soma = 0;
        for (i = 0; i < m; i++) {
            soma += v[i][j];
        }
        if (soma != 15) {
            printf("Nao eh quadrado magico!\n");
            system("pause");
            return;
        }
    }

    for (i = 0; i < m; i++) {
        somaDiagonalPrincipal += v[i][i];
    }

    for (i = 0; i < m; i++) {
        somaDiagonalSecundaria += v[i][m - i - 1];
    }

    if (somaDiagonalPrincipal != 15 || somaDiagonalSecundaria != 15) {
        printf("Nao eh quadrado magico!\n");
        system("pause");
        return;
    }

    printf("Eh quadrado magico!\n");
    system("pause");
}

void help() {
    system("cls");
    printf("================================  HELP  =======================================\n");
    printf("Bem-vindo ao programa de manipulação de matrizes!\n");
    printf("Neste programa, você pode criar uma matriz, realizar diversas operações e verificar algumas propriedades.\n");
    printf("Aqui está um guia sobre as opções disponíveis:\n\n");
    printf("1. Gerar nova matriz:\n");
    printf("   - Permite criar uma nova matriz com dimensões especificadas.\n");
    printf("   - Você será solicitado a informar o número de linhas e colunas da matriz.\n");
    printf("   - Em seguida, insira os elementos da matriz.\n\n");
    printf("2. Mostrar matriz:\n");
    printf("   - Exibe a matriz atualmente armazenada no programa.\n\n");
    printf("3. Trocar os elementos de duas linhas:\n");
    printf("   - Permite trocar os elementos de duas linhas da matriz.\n");
    printf("   - Você será solicitado a fornecer os números das linhas que deseja trocar.\n\n");
    printf("4. Trocar os elementos de duas colunas:\n");
    printf("   - Permite trocar os elementos de duas colunas da matriz.\n");
    printf("   - Você será solicitado a fornecer os números das colunas que deseja trocar.\n\n");
    printf("5. Trocar os elementos da diagonal principal com a diagonal secundária:\n");
    printf("   - Permite trocar os elementos da diagonal principal com a diagonal secundária da matriz.\n");
    printf("   - Esta opção altera a configuração dos elementos na matriz.\n\n");
    printf("6. Verificar se uma matriz é simétrica:\n");
    printf("   - Verifica se a matriz é simétrica em relação à sua diagonal principal.\n");
    printf("   - Uma matriz simétrica tem a propriedade de que os elementos a[i][j] são iguais aos elementos a[j][i].\n");
    printf("   - Se a matriz for simétrica, a mensagem 'A matriz é simétrica!' será exibida.\n");
    printf("   - Caso contrário, será exibida a mensagem 'A matriz não é simétrica!'\n\n");
    printf("7. Verificar se uma matriz é um quadrado mágico:\n");
    printf("   - Verifica se a matriz é um quadrado mágico.\n");
    printf("   - Um quadrado mágico é uma matriz quadrada em que a soma dos elementos de cada linha, cada coluna e ambas as diagonais é a mesma.\n");
    printf("   - Para um quadrado mágico 3x3, a soma deve ser igual a 15.\n");
    printf("   - Se a matriz for um quadrado mágico, a mensagem 'A matriz é um quadrado mágico!' será exibida.\n");
    printf("   - Caso contrário, será exibida a mensagem 'A matriz não é um quadrado mágico!'\n\n");
    printf("8. Verificar se uma matriz é um quadrado latino:\n");
    printf("   - Verifica se a matriz é um quadrado latino.\n");
    printf("   - Um quadrado latino é uma matriz quadrada em que cada linha e cada coluna contêm elementos distintos.\n");
    printf("   - Se a matriz for um quadrado latino, a mensagem 'A matriz é um quadrado latino!' será exibida.\n");
    printf("   - Caso contrário, será exibida a mensagem 'A matriz não é um quadrado latino!'\n\n");
    printf("9. Verificar se uma matriz é uma matriz de permutação:\n");
    printf("   - Verifica se a matriz é uma matriz de permutação.\n");
    printf("   - Uma matriz de permutação é uma matriz quadrada em que cada linha e cada coluna contêm exatamente um elemento igual a 1 e os demais elementos são iguais a 0.\n");
    printf("   - Se a matriz for uma matriz de permutação, a mensagem 'A matriz é uma matriz de permutação!' será exibida.\n");
    printf("   - Caso contrário, será exibida a mensagem 'A matriz não é uma matriz de permutação!'\n\n");
    printf("Pressione qualquer tecla para voltar ao menu.\n");
    getch();
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
        c = getch();

        if ((c < '1' || c > '9') && c != esc && c != 0) {
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
                quadradoMagico(v, m, n);
                break;

            case '8':
                printf("Funcao nao implementada.\n");
                system("pause");
                break;

            case '9':
                printf("Funcao nao implementada.\n");
                system("pause");
                break;

            case 0:
                if (getch() == 59) {
                    help();
                }
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
