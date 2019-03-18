#ifndef TYPEDEFS_H
  #define TYPEDEFS_H

  // ALL MESSAGES ------
  // Default Program msgs
  #define GAME_NAME "Guessing Game"
  // Default In Game Msgs
  #define GAME_FPS "FPS: "
  // Default Errors Msgs
  #define WIN_2_SMALL_MSG "Window too small"
  // Default Guessing Msgs
  #define GUESSING_SUCCEDED_B "\nComputer found the value\n in "
  #define GUESSING_SUCCEDED_E " guesses."
  #define GUESSING_FAILED "\nComputer failed to find the value"
  // Menu messages
  #define MAIN_MENU_TITLE "Main Menu"
  #define MAIN_MENU_START_B "Play"
  #define MAIN_MENU_TEST_B "Test"
  #define MAIN_MENU_EXIT_B "Exit"
  #define IN_GAME_MENU_TITLE "In-Game Options"
  #define IN_GAME_MENU_INC_B "Above"
  #define IN_GAME_MENU_DEC_B "Below"
  #define IN_GAME_MENU_EXIT_B "Back to Menu"
  #define TESTING_MENU_TITLE "Watch as the Computer Guesses"
  #define TESTING_MENU_EXIT_B "Back"
  #define GAME_OVER_TITLE "Game Over"
  #define GAME_OVER_EXIT_B "Back to Main Menu"
  // Default Input messages
  #define INPUT_START_MSG "Please enter a value 'A' to 'Z' or 1 to 1000"
  #define INPUT_EXIT_MSG "Please enter a string only containing letter or integers"


  // ALL VALUES -------
  // Default Game Values
  #define DEFAULT_SPAWN 7
  // Default Window values
  #define MIN_WIN_SIZE 30
  #define BORDER_SIDES '|'
  #define BORDER_TOP_BOTTOM '-'
  #define BORDER_CORNERS 'o'
  // Useful Functions
  #define HALF_OF_VAL(val) ((int)(val * 0.5f))
  // Default Menu values
  #define MENU_ITEM_SPACE 2
  // Guesses Class value
  #define GUESS_NUM_LIMIT 15
  #define GUESS_DELAY 10

#endif
