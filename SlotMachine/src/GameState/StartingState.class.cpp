/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 3/28/2019																		*
*																				*
* Assignment Requirement:														*
* This program will play a slot machine game. The slot machine shall have 3     *
* slots (or a single number between 0 to 9 for each slot) of the following      *
* ASCII number vector to use (see below). The user shall have the ability to    *
* make a bet and then the game will automatically spin the digits. Use a delay  *
* to simulate the numbers changing before the final numbers are revealed (if    *
* you use C++ 11 see the function below). The following conditions will be      *
* programmed:                                                                   *
*                                                                               *
* 3 matching numbers win 10 times the bet                                       *
*                                                                               *
* 2 matching numbers win 5 times the bet                                        *
*                                                                               *
* no matching number losses the bet				                     			*
*																				*
\*******************************************************************************/

#include "Vector2D.class.hpp"
#include "StartingState.class.hpp"
#include "Handlers/MenuHandler.class.hpp"

// Initializer for window dimensions Constructor
StartingState::StartingState(void) : GameState() {
	MenuHandler::setMenu(0);
	return;
}

// Copy constructor
StartingState::StartingState(StartingState const &src) : GameState(src) {
	*this = src;
	return;
}

// De-constructor
StartingState::~StartingState(void) {
	MenuHandler::deleteMenu();
	return;
}

// Equal sign overload for the copy constructor
StartingState					&StartingState::operator=(StartingState const &rhs) {
	if (this != &rhs) {}
	return *this;
}

void							StartingState::handleResize(void) {
	MenuHandler::handleResize();
}

void							StartingState::handleInput(int input) {
	MenuHandler::handleInput(input);
}

void							StartingState::handleTick(void) {
	GameState::handleTick();
}

// Out stream overload for testing
std::ostream					&operator<<(std::ostream &o, StartingState const &i) {
	return o << "Game State Info:" << &i << std::endl;
}
