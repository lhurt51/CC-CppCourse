#ifndef GAME_ENGINE_CLASS_HPP
  #define GAME_ENGINE_CLASS_HPP

  #include <includes.hpp>

  // Forward declaring classes and types
  template<typename T> class        Vector2D;

  // Game Engine class responsible for handling the window
  class GameEngine {

  public:

    // Static Public Helper methods --
    static void                     clearScreen(void);
    static bool                     isWindowToSmall(void);
    static float                    calculateFPS(void);
    static Vector2D<uint_fast32_t>  checkGameObjectPos(Vector2D<uint_fast32_t> pos, const std::string msg);
    static void                     printMiddle(const std::string msg);
    static void                     printPos(const Vector2D<uint_fast32_t> pos, const std::string msg);
    static void                     printBorder(void);
    static void                     useMenuTitleAttr(bool bUse);
    static void                     useMenuItemAttr(bool bUse);

    // Start the main loop
    static void                     start(void);

private:
    // Private Initializer --
    static void                     _initWindow(void);

    // Private class methods --
    static void                     _resizeHandler(void);
    static void                     _handleInput(void);

    // Destructors --
    static void                     _destroyWin(void);
  };

  // To print the game thread info
  std::ostream                      &operator<<(std::ostream &o, GameEngine const &i);

  // A string split function because I cant access boost functions
  std::vector<std::string>          split(const std::string& s, char const delimiter);

  // A string function to return the largest string length value
  unsigned					         maxStringLength(std::vector<std::string> strs);

#endif
