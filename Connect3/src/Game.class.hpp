#ifndef GAME_CLASS_HPP
  #define GAME_CLASS_HPP

  #include <ncurses.h>

  class Game {
    WINDOW*     _window;
    static int  _maxWinX;
    static int  _maxWinY;

  public:
    Game(void);
    Game(Game const &src);
    ~Game(void);

    Game        &operator=(Game const &rhs);

    void        run(void);
    WINDOW*     getWindow(void) const;
    static int  getWinMaxX(void) const;
    static int  getWinMaxY()
  };

#endif
