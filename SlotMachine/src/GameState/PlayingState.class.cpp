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

#include <macros/main_game_macros.hpp>
#include "Vector2D.class.hpp"
#include "PlayingState.class.hpp"
#include "Handlers/MenuHandler.class.hpp"
#include "Handlers/GameStateHandler.class.hpp"

// Initializer for window dimensions Constructor
PlayingState::PlayingState(void) : GameState() {
	MenuHandler::setMenu(1);
	return;
}

// Copy constructor
PlayingState::PlayingState(PlayingState const &src) : GameState(src) {
	*this = src;
	return;
}

// De-constructor
PlayingState::~PlayingState(void) {
	MenuHandler::deleteMenu();
	return;
}

// Equal sign overload for the copy constructor
PlayingState					&PlayingState::operator=(PlayingState const &rhs) {
	if (this != &rhs) {}
	return *this;
}

void							PlayingState::handleResize(void) {
	MenuHandler::handleResize();
}

void							PlayingState::handleInput(int input) {
	MenuHandler::handleInput(input);
}

void							PlayingState::handleTick(void) {
	GameState::handleTick();
}

// Out stream overload for testing
std::ostream					&operator<<(std::ostream &o, PlayingState const &i) {
	return o << "Game State Info:" << &i << std::endl;
}
