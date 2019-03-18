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

#include <typedefs.hpp>
#include "Vector2D.class.hpp"
#include "GameState.class.hpp"

// Initializer for window dimensions Constructor
GameState::GameState(Vector2D<uint_fast32_t>& winDem) : _winDem(winDem) {
	return;
}

// Copy constructor
GameState::GameState(GameState const &src) : _winDem(src.getWinDem()) {
	*this = src;
	return;
}

// Deconstructor
GameState::~GameState(void) {
	return;
}

// Equal sign overload for the copy constructor
GameState						&GameState::operator=(GameState const &rhs) {
	if (this != &rhs) {
		this->_winDem = rhs.getWinDem();
	}
	return *this;
}

// Game State Getters --
Vector2D<uint_fast32_t>&		GameState::getWinDem(void) const {
	return this->_winDem;
}

// Out stream overload for testing
std::ostream					&operator<<(std::ostream &o, GameState const &i) {
	return o << "Game State Info:" << std::endl <<
	"window demensions: " << i.getWinDem() << std::endl;
}
