#ifndef GAME_ENGINE_CLASS_HPP
  #define GAME_ENGINE_CLASS_HPP

  #include <includes.hpp>

  // Forward declaring classes and types
  typedef struct _win_st WINDOW;
  template<typename T> class Vector2D;
  class GameState;

  // Game Engine class responsible for handling the window
  class GameEngine {
    // Keeping track of a reference to the window
    static WINDOW*              _window;

  public:

    // Constructors --
    GameEngine(void);
    ~GameEngine(void);

    // Static getter --
    static WINDOW*              getWindow(void);

    // Static helper methods --
    static bool                 isWindowToSmall(const Vector2D<uint_fast32_t> v);
    static float                calculateFPS(void);
    static void                 printMiddle(const Vector2D<uint_fast32_t> pos, const std::string msg);
    static void                 printPos(const Vector2D<uint_fast32_t> pos, const std::string msg);
    static void                 printBorder(void);
    static void                 useMenuTitleAttr(bool bUse);
    static void                 useMenuItemAttr(bool bUse);

    // Regular class methods --
    void                        start(void);

private:
    // Private Initializer --
    void                        _initWindow(void);

    // Private class methods --
    void                        _updateWinDem(GameState& gameState);
    void                        _handleInput(GameState& gameState);

    // Destructors --
    void                        _destroyWin(void);
  };

  // To print the game thread info
  std::ostream                  &operator<<(std::ostream &o, GameEngine const &i);

  // A string split function because I cant access boost functions
  std::vector<std::string>      split(const std::string& s, char const delimiter);

#endif
