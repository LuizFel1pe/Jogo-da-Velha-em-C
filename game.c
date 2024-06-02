#include "stdio.h"
#include <stdlib.h>

#define ROWS 3
#define COLUMNS 3
#define PLAYER1 'X'
#define PLAYER2 'O'

char board[ROWS * COLUMNS];

void initialize() {
  int position = 1;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      board[ROWS * i + j] = '0' + position;
      position++;
    }
  }
}

void printboard() {
  system("clear");
  printf("------- Jogo da velha -------\n\n");
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (j == 0) {
        printf("\t");
      }
      printf(" %c ", board[ROWS * i + j]);
      if (j < 2) {
        printf("|");
      }
    }
    if (i < 2) {
      printf("\n\t-----------\n");
    }
  }
  printf("\n\n-----------------------------");
  printf("\n\n");
}

int isValid(int position) {
  int isEmpty = board[position - 1] != PLAYER1 && board[position - 1] != PLAYER2;
  if (position > 0 && position <= (ROWS * COLUMNS) && isEmpty) {
    return 1;
  }

  return 0;
}

void readCoordinates(char player) {
  int position;
  printf("Digite uma posição: ");
  scanf("%d", &position);
  while (!isValid(position)) {
    printf("Posição Inválida!\nDigite uma posição: ");
    scanf("%d", &position);
  }
  board[position - 1] = player;
}

int checkDiagonal(char player) {
  int mainDiagonal = board[0] == player && board[4] == player && board[8] == player;
  int secondaryDiagonal = board[2] == player && board[4] == player && board[6] == player;
  if (mainDiagonal || secondaryDiagonal) {
    return 1;
  }
  return 0;
}

int checkRow(char player) {
  int firstRow = board[0] == player && board[1] == player && board[2] == player;
  int secondRow = board[3] == player && board[4] == player && board[5] == player;
  int thirdRow = board[6] == player && board[7] == player && board[8] == player;
  if (firstRow || secondRow || thirdRow) {
    return 1;
  }
  return 0;
}

int checkColumn(char player) {
  int firstColumn = board[0] == player && board[3] == player && board[6] == player;
  int secondColumn = board[1] == player && board[4] == player && board[7] == player;
  int thirdColumn = board[2] == player && board[5] == player && board[8] == player;
  if (firstColumn || secondColumn || thirdColumn) {
    return 1;
  }
  return 0;
}

int win(char player) { 
  if (checkColumn(player) || checkRow(player) || checkDiagonal(player)) {
    printf("O jogador %c ganhou!", player);
    return 1;
  }

  return 0; 
}

int draw() {
  int n = 0;
  for (int i = 0; i < ROWS * COLUMNS; i++) {
    if (board[i] == PLAYER1 || board[i] == PLAYER2) {
      n++;
    }
  }

  if (n == 9) {
    printf("Empate");
    return 1;
  }

  return 0;
}

void gameLoop() {
  char player = PLAYER1;
  printboard();
  while (1) {
    readCoordinates(player);
    printboard();
    if (win(player) || draw()) {
      break;
    }
    player = player == PLAYER1 ? PLAYER2 : PLAYER1;
  }
}

int main() {
  initialize();
  gameLoop();
  return 0;
}