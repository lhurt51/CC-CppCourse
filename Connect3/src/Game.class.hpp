#ifndef GAME_CLASS_HPP
  #define GAME_CLASS_HPP

  #include <includes.hpp>
  #include <ncurses.h>
  #include "Vector2D.class.hpp"

  class Game {
    WINDOW*         _window;
    Vector2D        _maxWinDem;

  public:
    // Static so it is accessable outside the class
    static Vector2D minWinDem;

    Game(void);
    Game(Game const &src);
    ~Game(void);

    Game            &operator=(Game const &rhs);

    // All the getters
    WINDOW*         getWindow(void) const;
    Vector2D        getWinMaxDem(void) const;

    // All the setters
    bool            updateWinDem(void);

    // Methods
    void            run(void);
    bool            isWindowToSmall(void);

    // Destructors
    void            destroyWin(void);
  };

  // To print the game thread info
  std::ostream      &operator<<(std::ostream &o, Game const &i);

#endif
