#ifndef GAME_CLASS_HPP
  #define GAME_CLASS_HPP

  #include <ncurses.h>
  #include "Vector2D.class.hpp"

  class Game {
    static WINDOW*  _window;
    Vector2D        _maxWinDem;

  public:
    Game(void);
    Game(Game const &src);
    ~Game(void);

    Game            &operator=(Game const &rhs);

    // All the getters
    static WINDOW*  getWindow(void);
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
