#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 3
#define player_symb 'X'
#define player2_symb 'O'
#define computer_symb 'O'

void initBoard(char board[][size]);

void printBoard(char board[][size]);

int moveValidation(char board[][size], int row, int col);

int checkWin(char board[][size], char symb);

int checkBoardFull(char board[][size]);

void playerMove(char board[][size]);

void computerMove(char board[][size]);

void initGame();

void versusComputer();

void versusHuman();

void help();

void about();

void mainMenu();

int main() {
    mainMenu();

    initGame();

    return 0;
}

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

int checkWin(char board[][size], char symb) {
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

void player2Move(char board[][size]) {
    int row, col;
    printf("Sua vez de jogar (linha coluna): ");
    scanf("%d %d", &row, &col);

    if (!moveValidation(board, row, col)) {
        printf("Movimento invalido! Tente novamente.\n");
        playerMove(board);
        return;
    }

    board[row][col] = player2_symb;
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

void initGame() {
    printf("\e[?25h");
    system("cls");

    printf("Bem-vindo ao Jogo da Velha!\n\n");
    printf("Aperte 1 para jogar contra a maquina ou 2 para jogar contra outro humano\n");

    int numberOfPlayers = getch();

    do {
        if (numberOfPlayers == 49) {
            versusComputer();
        } else if (numberOfPlayers == 50) {
            versusHuman();
        } else {
            printf("Valor inválido! Digite novamente.\n");
        }
    } while (numberOfPlayers != 49 && numberOfPlayers != 50);

}

void versusComputer() {
    system("cls");

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
    mainMenu();
}

void versusHuman() {
    system("cls");

    char board[size][size];
    int gameOver = 0;

    initBoard(board);

    printf("Bem-vindo ao Jogo da Velha!\n\n");

    while (!gameOver) {
        printBoard(board);

        playerMove(board);
        if (checkWin(board, player_symb)) {
            printf("Parabens! O Jogador 1 ganhou!\n");
            gameOver = 1;
            break;
        }

        if (checkBoardFull(board)) {
            printf("Empate! O jogo terminou empatado.\n");
            gameOver = 1;
            break;
        }

        player2Move(board);
        if (checkWin(board, player2_symb)) {
            printf("Parabéns! O jogador 2 ganhou.\n");
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
    mainMenu();
}

void help(){
    system("cls");
    printf("-------------------------------\n");
    printf("| JOGO DA VELHA - REGRAS      |\n");
    printf("| O primeiro movimento e do X |\n");
    printf("|Vence quem fechar uma linha  |\n");
    printf("|coluna ou diagonal            |\n");
    printf("-------------------------------\n");
    getch();
    mainMenu();
}

void about() {
    system("cls");
    printf("Programa desenvolvido por Eduardo e Joao para a disciplina de Algoritmos II\n");
    printf("BSI 2023\n");
    system("pause");
    mainMenu();
}

void mainMenu() {
    system("cls");
    printf("\e[?25l");

    int position = 1;
    int keyPressed = 0;

    while (keyPressed != 13) {
        system("cls");
        printf("  ---------------------------------------------\n");
        printf("  | JOGO DA VELHA - Criado por Eduardo e Joao |\n");

        arrowSelection(1, position); printf("| Iniciar                                   |\n");
        arrowSelection(2, position); printf("| Ajuda                                     |\n");
        arrowSelection(3, position); printf("| Sobre                                     |\n");
        arrowSelection(4, position); printf("| Sair                                      |\n");

        printf("  ---------------------------------------------\n");

        keyPressed = getch();

        if (keyPressed == 80 && position != 4) {
            position++;
        } else if (keyPressed == 72 && position != 1) {
            position--;
        } else if (keyPressed == 27){
            system("cls");
            printf(" ------------------- \n");
            printf("|Obrigado por jogar!|\n");
            printf(" ------------------- \n");
            getch();
            exit(0);
        } else {
            position = position;
        }
    }

    if (position == 1) {
        initGame();
    } else if (position == 2) {
        help();
    } else if (position == 3) {
        about(); 
    } else if (position == 4) {
        system("cls");
        printf(" ------------------- \n");
        printf("|Obrigado por jogar!|\n");
        printf(" ------------------- \n");
        getch();
        exit(0);
    }
}

void arrowSelection(int actualPos, int arrowPos) {
    if (actualPos == arrowPos) {
        printf(">>");
    } else {
        printf("  ");
    }
}
