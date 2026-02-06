/*  Jeu Tic-Tac-Toe  (Morpion) developé en c
   - Menu (recommencer / menu / quitter)
   - Mode Joueur vs Joueur
   - Mode Joueur vs Ordinateur (IA Minimax)
   
   Travail de  Ayed Yomna 2024/2025
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

/* ===== Prototypes ===== */

void initBoard(char board[SIZE][SIZE]);
void printBoard(char board[SIZE][SIZE]);
int checkWin(char board[SIZE][SIZE], char player);
int isFull(char board[SIZE][SIZE]);
int playerMove(char board[SIZE][SIZE], char player);
int minimax(char board[SIZE][SIZE], int depth, int isMax);
void aiMove(char board[SIZE][SIZE]);

/* ===== Fonctions ===== */

void initBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = ' ';
}

void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ')
                printf(" %d ", i * SIZE + j + 1);
            else
                printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---+---+---\n");
    }
    printf("\n");
}

int checkWin(char board[SIZE][SIZE], char player) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return 1;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return 1;
    return 0;
}

int isFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

int playerMove(char board[SIZE][SIZE], char player) {
    int pos;
    printf("Joueur %c, choisissez une case (1-9) : ", player);
    if (scanf("%d", &pos) != 1) {
        while (getchar() != '\n');
        return 0;
    }
    while (getchar() != '\n');

    if (pos < 1 || pos > 9) return 0;

    int row = (pos - 1) / SIZE;
    int col = (pos - 1) % SIZE;

    if (board[row][col] != ' ') return 0;

    board[row][col] = player;
    return 1;
}

/* ===== IA Minimax ===== */

int minimax(char board[SIZE][SIZE], int depth, int isMax) {
    if (checkWin(board, 'O')) return 10 - depth;
    if (checkWin(board, 'X')) return depth - 10;
    if (isFull(board)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(board, depth + 1, 0);
                    board[i][j] = ' ';
                    if (score > best) best = score;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(board, depth + 1, 1);
                    board[i][j] = ' ';
                    if (score < best) best = score;
                }
            }
        }
        return best;
    }
}

void aiMove(char board[SIZE][SIZE]) {
    int bestScore = -1000;
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(board, 0, 0);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    board[bestRow][bestCol] = 'O';
    printf("Ordinateur joue en %d\n", bestRow * SIZE + bestCol + 1);
}

/* ===== MAIN ===== */

int main() {
    char board[SIZE][SIZE];
    int mode;

    while (1) {
        printf("\n=== TIC TAC TOE ===\n");
        printf("1. Joueur vs Ordinateur\n");
        printf("2. Joueur vs Joueur\n");
        printf("3. Quitter\n");
        printf("Choix : ");

        if (scanf("%d", &mode) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (mode == 3) break;
        if (mode != 1 && mode != 2) continue;

        initBoard(board);
        char current = 'X';
        int fin = 0;

        printBoard(board);

        while (!fin) {
            if (mode == 1 && current == 'O') {
                aiMove(board);
            } else {
                while (!playerMove(board, current)) {
                    printf("Coup invalide. Réessayez.\n");
                }
            }

            printBoard(board);

            if (checkWin(board, current)) {
                printf(" Joueur %c a gagné !\n", current);
                fin = 1;
            } else if (isFull(board)) {
                printf(" Match nul !\n");
                fin = 1;
            } else {
                current = (current == 'X') ? 'O' : 'X';
            }
        }

        printf("\n1. Recommencer\n2. Menu\n3. Quitter\nChoix : ");
        int c;
        scanf("%d", &c);
        while (getchar() != '\n');
        if (c == 3) break;
    }

    printf("Au revoir !\n");
    return 0;
}
