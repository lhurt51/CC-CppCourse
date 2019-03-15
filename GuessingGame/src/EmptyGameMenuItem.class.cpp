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

#include "Vector2D.class.hpp"
#include "GameState.class.hpp"
#include "EmptyGameMenuItem.class.hpp"

// Default constructor for initializing variables
EmptyGameMenuItem::EmptyGameMenuItem(GameState& gameState, Vector2D<uint_fast32_t> const pos, std::string const &sprite) : MenuItem(pos, sprite), _gameState(gameState) {
	return;
}

// Copy constructor
EmptyGameMenuItem::EmptyGameMenuItem(EmptyGameMenuItem const &src) : MenuItem(src), _gameState(src.getGameState()) {
	*this = src;
	return;
}

// Deconstructor
EmptyGameMenuItem::~EmptyGameMenuItem(void) {
	return;
}

// Overload equals operators for copy constructor
EmptyGameMenuItem		&EmptyGameMenuItem::operator=(EmptyGameMenuItem const &rhs) {
	if (this != &rhs) {}
	return *this;
}

// Getters --
GameState				&EmptyGameMenuItem::getGameState(void) const {
	return this->_gameState;
}

// Menu item abstract method implementation
void					EmptyGameMenuItem::_execute(void) {
	
}
