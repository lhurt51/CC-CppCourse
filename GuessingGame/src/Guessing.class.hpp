#ifndef GUESSING_CLASS_HPP
    #define GUESSING_CLASS_HPP

    #include <typedefs.hpp>
    #include <vector>

    #include "Actor.class.hpp"

    class               GameState;

    template<typename T>
    class Guessing : public Actor {

        GameState&      _gameState;
        // The list the computer should guess from
        std::vector<T>  _guessingList;
        // The players guess
        T               _playerInput;
        int             _lastGuess;
        int             _numOfGuesses;

    public:

        // Constructors --
        Guessing(GameState &gameState, std::vector<T> guessingList, T playerInput);
        Guessing(Guessing const &src);
        ~Guessing(void);

        // Operator overloads
        Guessing&        operator=(const Guessing& rhs);

        // Getters --
        GameState&       getGameState(void) const;
        std::vector<T>  getGuessingList(void) const;
        T               getPlayerInput(void) const;
        int             getLastGuess(void) const;
        int             getNumOfGuesses(void) const;

        // Actor Abstract method overloads
        void            tick(void);

    private:
        // Private helper methods
        int             _binarySearch(unsigned start, unsigned end, const T& key);

    };

#endif
