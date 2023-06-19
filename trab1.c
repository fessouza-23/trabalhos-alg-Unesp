#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define esc 27
#define f1 59
#define f2 60

void bemVindo();

void lerDimensao(int *m, int *n);

void lerMatriz(int v[][100], int m, int n);

void mostrarMatriz(int v[][100], int m, int n);

void trocarLinhas(int v[][100], int m, int n);

void matrizSimetrica(int v[][100], int n, int m);

void quadradoMagico(int v[][100], int n, int m);

void help();

void menu(int v[][100], int m, int n);

int main() {
    bemVindo();

    int m, n;
    lerDimensao(&m, &n);

    int v[100][100];
    lerMatriz(v, m, n);

    menu(v, m, n);

    return 0;
}

void bemVindo() {
    system("cls");
    printf("--- Bem-vindo ao programa de Manipulacao de Matrizes! ---\n");
    printf("Neste programa sera possivel escolher diversas opcoes de manipulacao de matrizes\n");
    printf("Como a troca de linhas entre duas matrizes, colunas, verificar se eh um quadrado magico etc.\n");
    printf("Mas antes, sera necessario digitar a dimensao e os elementos da matriz\n");
    printf("Aperte qualquer botao para continuar.\n");
    getch();
}

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
    printf("OBS: USAR '0' PARA ESCOLHER A 1a LINHA");
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

void trocarColunas(int v[][100], int m, int n) {
    int colunaX, colunaY;

    system("cls");
    printf("OBS: USAR '0' PARA ESCOLHER A 1a COLUNA");
    printf("Digite o valor da coluna X: ");
    scanf("%d", &colunaX);

    printf("Digite o valor da coluna Y: ");
    scanf("%d", &colunaY);

    if (colunaX >= 0 && colunaX < n && colunaY >= 0 && colunaY < n) {
        int temp;
        for (int j = 0; j < m; j++) {
            temp = v[j][colunaX];
            v[j][colunaX] = v[j][colunaY];
            v[j][colunaY] = temp;
            printf("COLUNA X: v[%d][%d]\n", v[j][colunaX]);
            printf("COLUNA Y: v[%d][%d]\n", v[j][colunaY]);
        }
        printf("Colunas trocadas com sucesso.\n");
    } else {
        printf("Valores de colunas invalidos.\n");
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
    int i, j, soma = 0, somaCol = 0, somaDiagPrin = 0, somaDiagSec = 0;
    //int temp[100], tempCol[100], tempDiag[100];

    if (m != n) {
        printf("Nao eh um quadrado magico!\n");
    } else {
        for (i = 0; i < m; i++) {
            soma = 0;
            for (j = 0; j < n; j++) {
                soma += v[i][j];
                //temp[i] = soma;
            }
            somaDiagPrin += v[i][i];
            somaDiagSec += v[i][m - i - 1];
            //printf("somaLinha Linha %d = %d\n", i, temp[i]);
            //printf("somaDiag = %d\n", somaDiag);
        }

        for (i = 0; i < n; i++) {
            somaCol = 0;
            for (j = 0; j < m; j++) {
                somaCol += v[j][i];
                //tempCol[i] = somaCol;
            }
            //printf("somaCol Col %d = %d\n", i, tempCol[i]);
        }

        if (soma == somaCol && soma == somaDiagPrin && soma == somaDiagPrin) {
            printf("Eh um quadrado magico!\n");
        } else {
            printf("Nao eh um quadrado magico.\n");
        }

        //printf("%d %d %d", soma, somaCol, somaDiag);

        system("pause");
    }
}

void quadradoLatino(int v[][100], int n, int m) {
    int i, j, qL = 0, qC = 0;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (v[i][j] == v[i][j + 1]) {
                printf("Nao eh um quadrado latino.\n");
                system("pause");
                return;
            }
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (v[j][i] == v[j + 1][i]) {
                printf("Nao eh um quadrado latino.\n");
                system("pause");
                return;
            } 
        }
    }

    printf("Eh um quadrado latino!\n");

    system("pause");
}

void trocarDiagonais(int v[][100], int n, int m) {
    int diagX[100], diagY[100], i, j, temp;

    system("cls");

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (j == i) {
                diagX[i] = v[i][j];
            } 
            if (j == m - i - 1) {
                diagY[i] = v[i][j];
            }
            temp = diagX[i];
            diagX[i] = diagY[i];
            diagY[i] = temp;
        }
        //printf("Diag prin: %d\n", diagX[i]);
        //printf("Diag sec: %d\n", diagY[i]);
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (j == i) {
                v[i][j] = diagX[i];
            } 
            if (j == m - i - 1) {
                v[i][j] = diagY[i];
            }
        }
    }
}

void verificarPermutacao(int v[][100], int n, int m) {
    int i, j;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (v[i][j] != 1 && v[i][j] != 0) {
                printf("Nao eh uma matriz permutada. TESTE1\n");
                system("pause");
                return;
            }
            if (v[i][j] == 1) {
                if (v[i][j] == v[i][j - 1]) {
                    printf("Nao eh uma matriz permutada. TESTE2\n");
                    system("pause");
                    return;
                }
            }
        }
    }

    printf("Eh uma matriz permutada!\n");

    system("pause");
}

void help() {
    system("cls");
    printf("================================  AJUDA  =======================================\n");
    printf("Bem-vindo ao programa de manipulacao de matrizes!\n");
    printf("Neste programa, voce pode criar uma matriz, realizar diversas operacoes e verificar algumas propriedades.\n");
    printf("Aqui esta um guia sobre as opcoes disponiveis:\n\n");
    printf("1. Gerar nova matriz:\n");
    printf("   - Permite criar uma nova matriz com dimensoes especificadas.\n");
    printf("   - Voce sera solicitado a informar o numero de linhas e colunas da matriz.\n");
    printf("   - Em seguida, insira os elementos da matriz.\n\n");
    printf("2. Mostrar matriz:\n");
    printf("   - Exibe a matriz atualmente armazenada no programa.\n\n");
    printf("3. Trocar os elementos de duas linhas:\n");
    printf("   - Permite trocar os elementos de duas linhas da matriz.\n");
    printf("   - Voce sera solicitado a fornecer os numeros das linhas que deseja trocar.\n\n");
    printf("4. Trocar os elementos de duas colunas:\n");
    printf("   - Permite trocar os elementos de duas colunas da matriz.\n");
    printf("   - Voce sera solicitado a fornecer os numeros das colunas que deseja trocar.\n\n");
    printf("5. Trocar os elementos da diagonal principal com a diagonal secundaria:\n");
    printf("   - Permite trocar os elementos da diagonal principal com a diagonal secundaria da matriz.\n");
    printf("   - Esta opcao altera a configuracao dos elementos na matriz.\n\n");
    printf("6. Verificar se uma matriz e simetrica:\n");
    printf("   - Verifica se a matriz e simetrica em relacao a sua diagonal principal.\n");
    printf("   - Uma matriz simetrica tem a propriedade de que os elementos a[i][j] são iguais aos elementos a[j][i].\n");
    printf("   - Se a matriz for simetrica, a mensagem 'A matriz eh simetrica!' sera exibida.\n");
    printf("   - Caso contrario, sera exibida a mensagem 'A matriz nao eh simetrica!'\n\n");
    printf("7. Verificar se uma matriz eh um quadrado magico:\n");
    printf("   - Verifica se a matriz eh um quadrado magico.\n");
    printf("   - Um quadrado magico eh uma matriz quadrada em que a soma dos elementos de cada linha, cada coluna e ambas as diagonais e a mesma.\n");
    printf("   - Para um quadrado magico 3x3, a soma deve ser igual a 15.\n");
    printf("   - Se a matriz for um quadrado mágico, a mensagem 'A matriz eh um quadrado magico!' sera exibida.\n");
    printf("   - Caso contrario, sera exibida a mensagem 'A matriz nao eh um quadrado magico!'\n\n");
    printf("8. Verificar se uma matriz eh um quadrado latino:\n");
    printf("   - Verifica se a matriz eh um quadrado latino.\n");
    printf("   - Um quadrado latino eh uma matriz quadrada em que cada linha e cada coluna contem elementos distintos.\n");
    printf("   - Se a matriz for um quadrado latino, a mensagem 'A matriz e um quadrado latino!' sera exibida.\n");
    printf("   - Caso contrario, sera exibida a mensagem 'A matriz nao eh um quadrado latino!'\n\n");
    printf("9. Verificar se uma matriz eh uma matriz de permutacao:\n");
    printf("   - Verifica se a matriz eh uma matriz de permutacao.\n");
    printf("   - Uma matriz de permutação eh uma matriz quadrada em que cada linha e cada coluna contem exatamente um elemento igual a 1 e os demais elementos sao iguais a 0.\n");
    printf("   - Se a matriz for uma matriz de permutacao, a mensagem 'A matriz eh uma matriz de permutacao!' sera exibida.\n");
    printf("   - Caso contrario, sera exibida a mensagem 'A matriz nao eh uma matriz de permutacao!'\n\n");
    printf("Pressione qualquer tecla para voltar ao menu.\n");
    getch();
}

void about() {
    system("cls");
    printf("================================  SOBRE O PROGRAMA  =======================================\n");
    printf("Programa desenvolvido por Eduardo R. Teixeira e Joao V. F. Souza para a disciplina de Algoritmos I do curso de BSI\n");
    printf("Criado em 2023\n");
    printf("Pressione qualquer tecla para voltar ao menu.\n");
    getch();
}

void menu(int v[][100], int m, int n) {
    char c;

    do {
        system("cls");
        printf("================================  MENU  =======================================\n");
        printf("|ESC - Sair | F1 - Ajuda | F2 - Sobre o Programa|\n");
        printf("1 - Gerar nova matriz\n");
        printf("2 - Mostrar matriz\n");
        printf("3 - Trocar os elementos da linha X pela linha Y\n");
        printf("4 - Trocar os elementos da coluna X pela coluna Y\n");
        printf("5 - Trocar os elementos da diagonal principal com a diagonal secundaria\n");
        printf("6 - Verificar se uma matriz eh simetrica\n");
        printf("7 - Verificar se uma matriz eh um quadrado magico\n");
        printf("8 - Verificar se uma matriz eh quadrado latino.\n");
        printf("9 - Verificar se uma matriz eh matriz de permutacao\n\n");
        c = getch();

        if ((c < '1' || c > '9') && c != esc && c != 0 && c != f1 && c != f2) {
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
                trocarColunas(v, m, n);
                mostrarMatriz(v, m, n);
                break;

            case '5':
                trocarDiagonais(v, m, n);
                mostrarMatriz(v, m, n);
                break;

            case '6':
                matrizSimetrica(v, m, n);
                break;

            case '7':
                quadradoMagico(v, m, n);
                break;

            case '8':
                quadradoLatino(v, m, n);
                break;

            case '9':
                verificarPermutacao(v, m, n);
                break;

            case f1:
                help();
                break;

            case f2:
                about();
                break;
        }
    } while (c != esc);
}