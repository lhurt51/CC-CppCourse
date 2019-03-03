#ifndef GAME_CLASS_HPP
  #define GAME_CLASS_HPP

  #include <ncurses.h>
  #include "GameState.class.hpp"

  class Game {
    static WINDOW*              _window;

  public:

    // Getters --
    static WINDOW*              getWindow(void);

    // Static helper methods --
    static void                 initWindow(void);
    static void                 updateWinDem(GameState& gameState);
    static void                 run(void);
    static bool                 isWindowToSmall(void);
    static float                calculateFPS(void);

    // Destructors --
    static void                  destroyWin(void);
  };

  // To print the game thread info
  std::ostream                  &operator<<(std::ostream &o, Game const &i);

#endif
