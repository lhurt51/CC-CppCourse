#ifndef TYPEDEFS_H
  #define TYPEDEFS_H

  // Program name
  #define GAME_NAME "Guessing Game"
  // Default Values
  #define DEFAULT_SPAWN 7
  #define DEFAULT_PLAYER_SPRITE ' '
  // Window values
  #define MIN_WIN_SIZE 30
  #define BORDER_SIDES '|'
  #define BORDER_TOP_BOTTOM '-'
  #define BORDER_CORNERS 'o'
  // Useful Functions
  #define HALF_OF_VAL(val) ((int)(val * 0.5f))
  // Menu values
  #define MENU_ITEM_SPACE 2
  // Default In Game Msgs
  #define GAME_OVER_MSG "Game Over"
  #define GAME_OVER_STATS_S "It took the computer %d tries to guess your choice"
  #define GAME_OVER_STATS_E "The computer could not guess your choice"
  #define GAME_FPS "FPS: %f"
  // Default Errors Msgs
  #define WIN_2_SMALL_MSG "Window too small"

#endif
