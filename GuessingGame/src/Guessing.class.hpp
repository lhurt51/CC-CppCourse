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
        T               _lastGuess;
        unsigned        _numOfGuesses;
        bool            _bShouldIncrease;
        bool            _bShouldDecrease;

    public:

        // Constructors --
        Guessing(GameState &gameState, std::vector<T> guessingList, T playerInput);
        Guessing(Guessing const &src);
        ~Guessing(void);

        // Operator overloads
        Guessing&        operator=(const Guessing& rhs);

        // Getters --
        GameState&      getGameState(void) const;
        std::vector<T>  getGuessingList(void) const;
        T               getPlayerInput(void) const;
        T               getLastGuess(void) const;
        unsigned        getNumOfGuesses(void) const;
        bool            getShouldIncrease(void) const;
        bool            getShouldDecrease(void) const;

        // Setters --
        void            setShouldIncrease(void);
        void            setShouldDecrease(void);
        void            setLastInput(T lastInput);

        // Actor Abstract method overloads
        void            tick(void);

    private:
        // Private helper methods --
        void            _testGame(bool bIsChar);
        void            _playGame(bool bIsChar);
        unsigned        _sizeOfLastGuess(bool bIsChar);
        T               _binarySearch(unsigned start, unsigned end, const T& key);

    };

#endif
