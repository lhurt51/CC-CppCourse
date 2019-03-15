/******************************************************************************
* Programmer Name:
* Liam Hurt
*
* Date:
* 2/6/2019
*
* Assignment Requirement:
* - Ask the user to guess a whole number between 1 and 1000 or character 'A'
*   to 'Z'
* - Your program will try to find the number
* - Keep track of the number of guesses by the computer
* - Use Recursive one of two search techniques: linear search or binary search
*   or randomize guess of a number.
* - Use a template class so the program could be used for integer or character,
*   your test function within your class should run with integer first then a
*   character
* - Use a randomized random number or letter generator for the item to guess
* - Allow the computer to have only 15 guesses
* - Your game class will have two functions or methods: playTheGame and static
*   Test
* - Your game shall have two modes: automatic where the computer tries to guess
*   you number without any input from you (except for the guess number) and
*   manual mode where each guess of the computer requires your input of Higher,
*   Lower, Right
*
******************************************************************************/

#include <type_traits>
#include "Vector2D.class.hpp"
#include "GameState.class.hpp"
#include "Guessing.class.hpp"

template<typename T>
Guessing<T>::Guessing(GameState &gameState, std::vector<T> guessingList, T playerInput) : Actor(Vector2D<uint_fast32_t>(HALF_OF_VAL(gameState.getWinDem().x), HALF_OF_VAL(gameState.getWinDem().y) - 7), "Value to Guess: " + ((std::is_same<T, char>::value) ? std::string(1, std::toupper(playerInput)) : std::to_string(playerInput)) + "\nThe Computer Guessed: "), _gameState(gameState), _guessingList(guessingList), _playerInput(playerInput), _lastGuess(0), _numOfGuesses(0), _bShouldIncrease(false), _bShouldDecrease(false) {
    return;
}

template<typename T>
Guessing<T>::Guessing(Guessing const &src) : Actor(src), _gameState(src.getGameState()) {
    *this = src;
    return;
}

template<typename T>
Guessing<T>::~Guessing(void) {
    _numOfGuesses = GUESS_NUM_LIMIT + 1;
    _testGame(std::is_same<T, char>::value);
    return;
}

template<typename T>
Guessing<T>&        Guessing<T>::operator=(const Guessing& rhs) {
	if (this != &rhs) {
        this->_gameState = rhs.getGameState();
		this->_guessingList = rhs.getGuessingList();
		this->_playerInput = rhs.getPlayerInput();
		this->_lastGuess = rhs.getLastGuess();
		this->_numOfGuesses = rhs.getNumOfGuesses();
        this->_bShouldIncrease = rhs.getShouldIncrease();
        this->_bShouldDecrease = rhs.getShouldDecrease();
	}
	return *this;
}

template<typename T>
GameState&      Guessing<T>::getGameState(void) const {
    return this->_gameState;
}

template<typename T>
std::vector<T>  Guessing<T>::getGuessingList(void) const {
    return this->_guessingList;
}

template<typename T>
T               Guessing<T>::getPlayerInput(void) const {
    return this->_playerInput;
}

template<typename T>
T               Guessing<T>::getLastGuess(void) const {
    return this->_lastGuess;
}

template<typename T>
unsigned        Guessing<T>::getNumOfGuesses(void) const {
    return this->_numOfGuesses;
}

template<typename T>
bool            Guessing<T>::getShouldIncrease(void) const {
    return this->_bShouldIncrease;
}

template<typename T>
bool            Guessing<T>::getShouldDecrease(void) const {
    return this->_bShouldDecrease;
}

// Setters --
template<typename T>
void            Guessing<T>::setShouldIncrease(void) {
    this->_bShouldIncrease = true;
}

template<typename T>
void            Guessing<T>::setShouldDecrease(void) {
    this->_bShouldDecrease = true;
}

template<typename T>
void            Guessing<T>::setLastInput(T lastInput) {
    if (_lastGuess == lastInput) return;
    _lastGuess = lastInput;
    _numOfGuesses++;
}

// Need a game timer!!!!
template<typename T>
void            Guessing<T>::tick(void) {
    static unsigned i = 0;

    setPos(Vector2D<uint_fast32_t>(HALF_OF_VAL(_gameState.getWinDem().x), HALF_OF_VAL(_gameState.getWinDem().y) - 7));
    if (i > 1000) {
        if (_gameState.bIsPlaying)
            _playGame(std::is_same<T, char>::value);
        else
            _testGame(std::is_same<T, char>::value);
        i = 0;
    }
    i++;
}

template<typename T>
void            Guessing<T>::_testGame(bool bIsChar) {
    static unsigned count = 0;
    static unsigned start = 0;
    static unsigned end = _guessingList.size();
    static unsigned mid = (end + start) / 2;
    std::string     sprite = this->_sprite;

    if (_numOfGuesses > GUESS_NUM_LIMIT) {
        count = 0;
        start = 0;
        end = _guessingList.size();
        mid = (end + start) / 2;
        if (_gameState.getCurState() == TESTING || _gameState.getCurState() == PLAYING)
            _gameState.setCurState(GAMEOVER);
        if (_lastGuess != _playerInput && getSprite().find(GUESSING_FAILED) == std::string::npos)
            sprite += GUESSING_FAILED;
    } else {
        if (count % GUESS_DELAY == 0) {
            if (count >= GUESS_DELAY) {
                sprite.erase(sprite.end() - _sizeOfLastGuess(bIsChar), sprite.end());
                if (_lastGuess > _playerInput) {
                    end = mid;
                    mid = (end + start) / 2;
                } else if (_lastGuess < _playerInput) {
                    start = mid;
                    mid = (end + start) / 2;
                }
            }
            setLastInput(_binarySearch(start, end, _guessingList[mid]));
            sprite += (bIsChar) ? std::string(1, std::toupper(_lastGuess)) : std::to_string(_lastGuess);
            if (_lastGuess == _playerInput) {
                sprite += GUESSING_SUCCEDED_B + std::to_string(_numOfGuesses) + GUESSING_SUCCEDED_E;
                _numOfGuesses = GUESS_NUM_LIMIT + 1;
            }
        }
        count++;
    }
    setSprite(sprite);
}

template<typename T>
void            Guessing<T>::_playGame(bool bIsChar) {
    static unsigned start = 0;
    static unsigned end = _guessingList.size();
    static unsigned mid = (end + start) / 2;
    std::string     sprite = this->_sprite;

    if (_numOfGuesses > GUESS_NUM_LIMIT || start == end) {
        start = 0;
        end = _guessingList.size();
        mid = (end + start) / 2;
        _numOfGuesses = GUESS_NUM_LIMIT + 1;
        if (_gameState.getCurState() == TESTING || _gameState.getCurState() == PLAYING)
            _gameState.setCurState(GAMEOVER);
        if (_lastGuess != _playerInput && getSprite().find(GUESSING_FAILED) == std::string::npos)
            sprite += GUESSING_FAILED;
    } else {
        if (_numOfGuesses > 0) {
            sprite.erase(sprite.end() - _sizeOfLastGuess(bIsChar), sprite.end());
            if (_bShouldIncrease) {
                _bShouldIncrease = false;
                end = mid;
                mid = (end + start) / 2;
            } else if (_bShouldDecrease) {
                _bShouldDecrease = false;
                start = mid;
                mid = (end + start) / 2;
            }
        }
        setLastInput(_binarySearch(start, end, _guessingList[mid]));
        sprite += (bIsChar) ? std::string(1, std::toupper(_lastGuess)) : std::to_string(_lastGuess);
        if (_lastGuess == _playerInput) {
            sprite += GUESSING_SUCCEDED_B + std::to_string(_numOfGuesses) + GUESSING_SUCCEDED_E;
            _numOfGuesses = GUESS_NUM_LIMIT + 1;
        }
    }
    setSprite(sprite);
}

template<typename T>
unsigned        Guessing<T>::_sizeOfLastGuess(bool bIsChar) {
    unsigned size = 0;

    if (bIsChar) return 1;
    int number = _lastGuess;
    while (number/=10) size++;
    return ++size;
}

template<typename T>
T               Guessing<T>::_binarySearch(unsigned start, unsigned end, const T& key)
{
    if (start >= _guessingList.size() && end >= _guessingList.size())
        return -1;
    while(start <= end)
    {
        int mid = (start+end)/2;

        if(key < _guessingList[mid])
            end = mid - 1;
        else if(key > _guessingList[mid])
            start = mid + 1;
        else
            return _guessingList[mid];
    }
    return -1;
}

/*******************************************************************************************\
* RECURSION DOES NOT WORK WITH TEMPLATES                                                    *
* template<typename T>                                                                      *
* int             Guessing<T>::_binarySearch(int start, int end, const T& key)              *
* {                                                                                         *
*     // Termination condition: start index greater than end index                          *
*     if(start > end) return -1;                                                            *
*                                                                                           *
*     // Find the middle element of the vector and use that for splitting                   *
*     // the array into two pieces.                                                         *
*     const int middle = start + ((end - start) / 2);                                       *
*                                                                                           *
*     if(_guessingList[middle] == key) return middle;                                       *
*     else if(_guessingList[middle] > key) return _binary_search(start, middle - 1, key);   *
*     else return _binary_search(middle + 1, end, key);                                     *
* }                                                                                         *
\*******************************************************************************************/
