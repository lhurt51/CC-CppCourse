#ifndef TYPEDEFS_H
  #define TYPEDEFS_H

  #define DEFAULT_SPAWN 2
  #define MIN_WIN_SIZE 30
  #define BOARD_ROW 5
  #define BOARD_COLUMN 6
  #define IS_COL_INVALID(col) (col > BOARD_COLUMN - 1 || col < 0)
  #define IS_ROW_INVALID(row) (row > BOARD_ROW - 1 || row < 0)
  #define IS_SIZE_INVALID(row, col) (row > BOARD_ROW - 1 || row < 0 || col > BOARD_COLUMN - 1 || col < 0)
  #define HALF_OF_VAL(val) ((int)(val * 0.5f))

#endif
