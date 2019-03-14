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
Guessing<T>::Guessing(GameState &gameState, std::vector<T> guessingList, T playerInput) : Actor(Vector2D<uint_fast32_t>(HALF_OF_VAL(gameState.getWinDem().x), HALF_OF_VAL(gameState.getWinDem().y) - 6), "Your input is " + ((std::is_same<T, char>::value) ? std::string(1, playerInput) : std::to_string(playerInput)) + "\nIs your input higher or lower than\nThe Computers guess: "), _gameState(gameState), _guessingList(guessingList), _playerInput(playerInput) {
    return;
}

template<typename T>
Guessing<T>::Guessing(Guessing const &src) : Actor(src), _gameState(src.getGameState()) {
    *this = src;
    return;
}

template<typename T>
Guessing<T>::~Guessing(void) {
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
int             Guessing<T>::getLastGuess(void) const {
    return this->_lastGuess;
}

template<typename T>
int             Guessing<T>::getNumOfGuesses(void) const {
    return this->_numOfGuesses;
}

template<typename T>
void            Guessing<T>::tick(void) {
    static unsigned i = 0;
    static unsigned count = 0;

    setPos(Vector2D<uint_fast32_t>(HALF_OF_VAL(_gameState.getWinDem().x), HALF_OF_VAL(_gameState.getWinDem().y) - 6));
    if (i > 1000) {
        if (std::is_same<T, char>::value) {
            if (count == 0) setSprite((std::string&)this->_sprite + std::string(1, _guessingList[_guessingList.size()*0.5]));
            
        } else {

        }
        count++;
        i = 0;
    }
    i++;
}

template<typename T>
int             Guessing<T>::_binarySearch(unsigned start, unsigned end, const T& key)
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
