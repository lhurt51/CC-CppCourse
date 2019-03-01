#ifndef GAME_CLASS_HPP
  #define GAME_CLASS_HPP

  #include <ncurses.h>
  #include "GameState.class.hpp"

  class Game {
    static WINDOW*              _window;

  public:

    // Constructors --
    Game(void);
    Game(Game const &src);
    ~Game(void);

    // Getters --
    static WINDOW*              getWindow(void);

    // Non Static update window --
    static bool                 updateWinDem(GameState& gameState);

    // Static helper methods --
    static void                 run(void);
    static bool                 isWindowToSmall(void);

    // Destructors --
    static void                  destroyWin(void);
  };

  // To print the game thread info
  std::ostream                  &operator<<(std::ostream &o, Game const &i);

#endif
