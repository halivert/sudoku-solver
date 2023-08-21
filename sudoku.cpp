#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>

using std::pair, std::vector;

const int BOARD_SIZE = 9;
const char ZERO = '0';

typedef vector<vector<char>> Board;

Board readBoard();
void printBoard(Board);
void printBoard(Board, char);
pair<bool, Board> solve(Board);
bool isValid(Board);
pair<int, int> firstZero(Board);

int main(int argc, char *argv[]) {
  static struct option long_options[] = {{"per-number", no_argument, 0, 'p'},
                                         {0, 0, 0, 0}};

  int option;
  int option_index = 0;

  bool showPerNumber = false;

  while ((option = getopt_long(argc, argv, "p", long_options, &option_index)) !=
         -1) {
    switch (option) {
    case 'p':
      showPerNumber = true;
      break;
    }
  }

  Board board = readBoard();

  if (!isValid(board)) {
    printf("Initial board is not valid");
    return 1;
  }

  printBoard(board);

  pair<bool, Board> solved = solve(board);

  if (!solved.first) {
    printf("Cannot solve\n");
    printBoard(board);
    return 1;
  }

  printf("\nSolved!\n");
  printBoard(solved.second);

  if (showPerNumber) {
    printf("\nPer number\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
      printBoard(solved.second, i + '1');
    }
  }

  return 0;
}

Board readBoard() {
  Board board(BOARD_SIZE, vector<char>(BOARD_SIZE, '0'));
  char sp;
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int column = 0; column < BOARD_SIZE; column++) {
      scanf("%c%c", &board[row][column], &sp);
      if (sp != ' ' && sp != '\n') {
        board[row][++column] = sp;
      }
    }
  }
  return board;
}

void printBoard(Board board) {
  printf("_______________________\n");
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int column = 0; column < BOARD_SIZE; column++) {
      char number = board[row][column];

      printf("%c", number != '0' ? number : '_');

      if (!((column + 1) % 3)) {
        printf(" | ");
      } else if (column < BOARD_SIZE - 1) {
        printf(" ");
      }

      if (column == BOARD_SIZE - 1) {
        printf("\n");
      }
    }

    if (!((row + 1) % 3))
      printf("_______________________\n");
  }
}

void printBoard(Board board, char num) {
  for (vector<char> &row : board) {
    for (char &c : row) {
      if (c != num) {
        c = '0';
      }
    }
  }

  printBoard(board);
}

pair<bool, Board> solve(Board board) {
  if (!isValid(board)) {
    return pair(false, board);
  }

  pair<int, int> fz = firstZero(board);

  if (fz.first == -1 && fz.second == -1) {
    return pair(isValid(board), board);
  }

  vector<Board> valids;

  for (int i = 0; i < BOARD_SIZE; i++) {
    board[fz.first][fz.second] = i + '1';
    if (!isValid(board))
      continue;

    pair<bool, Board> solved = solve(board);
    if (solved.first)
      valids.push_back(solved.second);
  }

  return (valids.size() >= 1) ? pair(true, valids[0]) : pair(false, board);
}

bool isValid(Board board) {
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

pair<int, int> firstZero(Board board) {
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
