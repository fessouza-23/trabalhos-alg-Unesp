#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 3
#define player_symb 'X'
#define computer_symb 'O'

void initBoard(char board[][size]) {
    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard(char board[][size]) {
    printf("\n");
    printf("    0    1    2  \n");
    for (int i = 0; i < size; i++) {
        printf("%d ", i);
        for (int j = 0; j < size; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
        if (i != size - 1) {
            printf("  -------------\n");
        }
    }
    printf("\n");
}

int moveValidation(char board[][size], int row, int col) {
    if (row < 0 || row >= size || col < 0 || col >= size)
        return 0;
    if (board[row][col] != ' ')
        return 0;
    // else
    return 1;
}

int checkWin(char board[0][size], char symb) {
    int i, j;

    // verificação por linha
    for (i = 0; i < size; i++) {
        if (board[i][0] == symb && board[i][1] == symb && board[i][2] == symb)
            return 1;
    }

    // verificação por coluna
    for (j = 0; j < size; j++) {
        if (board[0][j] == symb && board[1][j] == symb && board[2][j] == symb)
            return 1;
    }

    // verificação por diagonal
    if (board[0][0] == symb && board[1][1] == symb && board[2][2] == symb)
        return 1; // Diagonal principal
    if (board[2][0] == symb && board[1][1] == symb && board[0][2] == symb)
        return 1; // Diagonal secundária
    // else
    return 0; 
}

int checkBoardFull(char board[][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1; // Tabuleiro completo
}

void playerMove(char board[][size]) {
    int row, col;
    printf("Sua vez de jogar (linha coluna): ");
    scanf("%d %d", &row, &col);

    if (!moveValidation(board, row, col)) {
        printf("Movimento invalido! Tente novamente.\n");
        playerMove(board);
        return;
    }

    board[row][col] = player_symb;
}

void computerMove(char board[][size]) {
    srand(time(NULL));

    int row, col;
    do {
        row = rand() % size;
        col = rand() % size;
    } while (!moveValidation(board, row, col));

    board[row][col] = computer_symb;
}

int main() {
    char board[size][size];
    int gameOver = 0;

    initBoard(board);

    printf("Bem-vindo ao Jogo da Velha!\n\n");

    while (!gameOver) {
        printBoard(board);

        playerMove(board);
        if (checkWin(board, player_symb)) {
            printf("Parabens! Voce ganhou!\n");
            gameOver = 1;
            break;
        }

        if (checkBoardFull(board)) {
            printf("Empate! O jogo terminou empatado.\n");
            gameOver = 1;
            break;
        }

        computerMove(board);
        if (checkWin(board, computer_symb)) {
            printf("Voce perdeu! O computador ganhou.\n");
            gameOver = 1;
            break;
        }

        if (checkBoardFull(board)) {
            printf("Empate! O jogo terminou empatado.\n");
            gameOver = 1;
        }
    }

    printBoard(board);
    printf("Fim do jogo!\n");
    system("pause");

    return 0;
}