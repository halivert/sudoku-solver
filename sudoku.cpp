#include <stdio.h>
#include <utility>

using std::pair;

const int BOARD_SIZE = 9;
const char ZERO = '0';

void readBoard(char[][BOARD_SIZE]);
void printBoard(char[][BOARD_SIZE]);
bool solve(char[][BOARD_SIZE]);
bool isValid(char[][BOARD_SIZE]);
pair<int, int> firstZero(char[][BOARD_SIZE]);

int main() {
  char board[BOARD_SIZE][BOARD_SIZE] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0}};

  readBoard(board);
  printBoard(board);

  bool solved = solve(board);

  if (!solved) {
    printf("Cannot solve\n");
    printBoard(board);
    return 1;
  }

  printf("Solved!\n");
  printBoard(board);
  return 0;
}

void readBoard(char board[][BOARD_SIZE]) {
  char sp;
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int column = 0; column < BOARD_SIZE; column++) {
      scanf("%c%c", &board[row][column], &sp);
    }
  }
}

void printBoard(char board[][BOARD_SIZE]) {
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int column = 0; column < BOARD_SIZE; column++) {
      if (column == 0) {
        printf("[");
      }

      printf("%c", board[row][column]);

      if (column < BOARD_SIZE - 1) {
        printf(" ");
      }

      if (column == BOARD_SIZE - 1) {
        printf("]\n");
      }
    }
  }
}

bool solve(char board[][BOARD_SIZE]) {
  if (!isValid(board)) {
    return false;
  }

  pair<int, int> fz = firstZero(board);

  if (fz.first == -1 && fz.second == -1) {
    return isValid(board);
  }

  for (int i = 0; i < BOARD_SIZE; i++) {
    board[fz.first][fz.second] = i + '1';
  }

  return false;
}

bool isValid(char board[][BOARD_SIZE]) {
  int nums[BOARD_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  for (int i = 0; i < BOARD_SIZE; i++) {
    // Check rows
    {
      for (int column = 0; column < BOARD_SIZE; column++) {
        char item = board[i][column];

        if (item < '1')
          continue;

        nums[item - '1']++;
      }

      for (int j = 0; j < BOARD_SIZE; j++) {
        if (nums[j] > 1) {
          return false;
        }
      }

      for (int j = 0; j < BOARD_SIZE; nums[j++] = 0)
        ;
    }

    // Check columns
    {
      for (int column = 0; column < BOARD_SIZE; column++) {
        char item = board[column][i];

        if (item < '1')
          continue;

        nums[item - '1']++;
      }

      for (int j = 0; j < BOARD_SIZE; j++) {
        if (nums[j] > 1) {
          return false;
        }
      }

      for (int j = 0; j < BOARD_SIZE; nums[j++] = 0)
        ;
    }

    // Check square
    {
      int rowOrigin = (i / 3) * 3;
      int columnOrigin = (i % 3) * 3;
      for (int columns = 0; columns < BOARD_SIZE; columns++) {
        int row = rowOrigin + (columns / 3);
        int column = columnOrigin + (columns % 3);

        char item = board[row][column];

        if (item < '1')
          continue;

        nums[item - '1']++;
      }

      for (int j = 0; j < BOARD_SIZE; j++) {
        if (nums[j] > 1) {
          return false;
        }
      }

      for (int j = 0; j < BOARD_SIZE; nums[j++] = 0)
        ;
    }
  }

  return true;
}

pair<int, int> firstZero(char board[][BOARD_SIZE]) {
  pair<int, int> result = pair(-1, -1);

  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int column = 0; column < BOARD_SIZE; column++) {
      if (board[row][column] == ZERO) {
        result.first = row;
        result.second = column;
        return result;
      }
    }
  }

  return result;
}
