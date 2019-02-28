#ifndef GAME_CLASS_HPP
  #define GAME_CLASS_HPP

  #include <ncurses.h>
  #include "Vector2D.class.hpp"

  class Game {
    static WINDOW*  _window;
    //Vector2D        _maxWinDem;

  public:

    // Constructors --
    Game(void);
    Game(Game const &src);
    ~Game(void);

    // Overload operators --
    Game            &operator=(Game const &rhs);

    // Getters --
    static WINDOW*  getWindow(void);
    //Vector2D        getWinMaxDem(void) const;

    // Setters --
    bool            updateWinDem(void);

    // Helper methods --
    void            run(void);
    bool            isWindowToSmall(void);

    // Destructors --
    void            destroyWin(void);
  };

  // To print the game thread info
  std::ostream      &operator<<(std::ostream &o, Game const &i);

#endif
