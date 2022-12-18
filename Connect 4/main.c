#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define ROWS 6
#define COLUMNS 7
#define FOUR 4

char scores[ROWS][COLUMNS];
char baslik[] = "  1   2   3   4   5   6   7 ";
char satir[] = "|===|===|===|===|===|===|===|";
char tas = 'R';
int col = 0, tur = 0;

void fill_scores() {
  // Fill every hole with space
  for (int a = 0; a < ROWS; a++) {

    for (int b = 0; b < COLUMNS; b++) {
      scores[a][b] = ' ';
    }
  }
}
void board() {
  // Print the game board
  printf("\033[1;34m");
  printf("%s\n", baslik);
  printf("\033[0;30m");
  printf("%s\n", satir);

  for (int i = 0; i < ROWS; i++) {

    for (int j = 0; j < COLUMNS; j++) {

      printf("| ");
      if (scores[i][j] == 'R') {
        printf("\033[0;31m");
        printf("%c ", scores[i][j]);
        printf("\033[0;30m");
      } else if (scores[i][j] == 'Y') {
        printf("\033[0;33m");
        printf("%c ", scores[i][j]);
        printf("\033[0;30m");
      } else {
        printf("%c ", scores[i][j]);
      }
    }
    printf("|\n");
    printf("%s\n", satir);
  }
  printf("\033[0m");
}
void choose() {
  // Player select a column
  int p;
  while (true) {

    printf("Enter a column number: ");
    scanf("%d", &p);
    switch (p) {
    case 1:
      col = 0;
      break;
    case 2:
      col = 1;
      break;
    case 3:
      col = 2;
      break;
    case 4:
      col = 3;
      break;
    case 5:
      col = 4;
      break;
    case 6:
      col = 5;
      break;
    case 7:
      col = 6;
      break;
    default:
      col = 31;
      printf("\033[1m");
      printf("Wrong column! Try again.\n");
      printf("\033[0m");
      board();
    }

    if ((col >= 0 && col <= 6) && (scores[0][col] == ' ')) {

      for (int x = ROWS - 1; x >= 0; x--) {

        if (scores[x][col] == ' ') {
          scores[x][col] = tas;
          break;
        }
      }
      if (tur % 2 == 0) {
        tas = 'R';
      } else {
        tas = 'Y';
      }
      break;
    }
    if((col>=0 && col<=6) && (scores[0][col]!=' ')){
      printf("\033[1m");
      printf("This column is full! Please choose another column.\n");
      printf("\033[0m");
      board();
    }
  }
}
int control(char tas) {
  int r, g, b, counter;
  // Control in Rows
  int ways = 4;
  for (r = 0; r < ROWS; ++r) {
    for (g = 0; g < ways; ++g) {
      counter = 0;
      for (b = 0; b < FOUR; ++b) {
        if (scores[r][g + b] == tas) {
          counter++;
        }
      }
      if (counter == FOUR) {
        return true;
      }
    }
  }
  // Control in Columns
  int way = 3;
  for (g = 0; g < COLUMNS; ++g) {
    for (r = 0; r < way; ++r) {
      counter = 0;
      for (b = 0; b < FOUR; ++b) {
        if (scores[r + b][g] == tas) {
          counter++;
        }
      }
      if (counter == FOUR) {
        return true;
      }
    }
  }
  // Control in Diagonal
  int rr, gg;
  for (r = 1; r < ROWS - 1; r++) {
    for (g = 1; g < COLUMNS - 1; g++) {
      counter = 0;
      for (rr = r, gg = g; (rr >= 0) || (gg >= 0); rr--, gg--) {
        if (scores[rr][gg] == tas) {
          counter++;
          if (counter == FOUR) {
            return true;
          }
        } else {
          break;
        }
      }
      for (rr = r + 1, gg = g + 1; (rr <= ROWS - 1) || (gg <= COLUMNS - 1);
           rr++, gg++) {
        if (scores[rr][gg] == tas) {
          counter++;
          if (counter == FOUR) {
            return true;
          }
        } else {
          break;
        }
      }
      counter = 0;
      for (rr = r, gg = g; (rr <= ROWS - 1) || (gg >= 0); rr++, gg--) {
        if (scores[rr][gg] == tas) {
          counter++;
          if (counter == FOUR) {
            return true;
          }
        } else {
          break;
        }
      }
      for (rr = r - 1, gg = g + 1; (rr >= 0) || (gg <= COLUMNS - 1);
           rr--, g++) {
        if (scores[rr][gg] == tas) {
          counter++;
          if (counter == FOUR) {
            return true;
          }
        } else {
          break;
        }
      }
    }
  }
  return false;
}

int main() {
  fill_scores();
  board();

  while (true) {
    tur = tur + 1;
    printf("Player %c, your turn!\n", tas);
    choose();
    system("clear");
    board();
    if (control('R')) {
      printf("\033[0;31m");
      printf("\nPlayer Red win!");
      printf("\033[0m");
      break;
    }
    if (control('Y')) {
      printf("\033[0;33m");
      printf("\nPlayer Yellow win!");
      printf("\033[0m");
      break;
    }
    if(tur==42){
      printf("\033[1;34m");
      printf("\nDraw!!");
      printf("\033[0m");
      break;
    }
  }
}