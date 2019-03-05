#ifndef GAME_ENGINE_CLASS_HPP
  #define GAME_ENGINE_CLASS_HPP

  #include <ncurses.h>
  #include "GameState.class.hpp"

  class GameEngine {
    // Keeping track of a reference to the window
    static WINDOW*              _window;

  public:

    GameEngine(void);
    ~GameEngine(void);

    // Getters --
    static WINDOW*              getWindow(void);

    // Static helper methods --
    static bool                 isWindowToSmall(Vector2D<uint_fast32_t> v);
    static float                calculateFPS(void);
    static void                 printMiddle(Vector2D<uint_fast32_t> pos, std::string msg, Vector2D<uint_fast32_t> size);

    // Regular class methods --
    void                        start(void);

private:
    void                        _initWindow(void);

    // Private class methods --
    void                        _updateWinDem(GameState& gameState);

    // Destructors --
    void                        _destroyWin(void);
  };

  // To print the game thread info
  std::ostream                  &operator<<(std::ostream &o, GameEngine const &i);

#endif
