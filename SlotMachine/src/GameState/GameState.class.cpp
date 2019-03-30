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

#include "GameState.class.hpp"
#include "Handlers/ActorHandler.class.hpp"

// Initializer for window dimensions Constructor
GameState::GameState(void) {
	return;
}

// Copy constructor
GameState::GameState(GameState const &src) {
	*this = src;
	return;
}

// De-constructor
GameState::~GameState(void) {
	ActorHandler::clearAllObjects();
	return;
}

// Equal sign overload for the copy constructor
GameState						&GameState::operator=(GameState const &rhs) {
	if (this != &rhs) {}
	return *this;
}

void							GameState::hideAllGameObjects(void) {
	ActorHandler::setAllObjectsCanDraw(false);
}

void							GameState::showAllGameObjects(void) {
	ActorHandler::setAllObjectsCanDraw(true);
}

void							GameState::printAllGameObjects(void) {
	ActorHandler::printAllObjects();
}

bool							GameState::checkForActorUpdate(void) {
	if (ActorHandler::anyActorNeedsUpdate()) {
		ActorHandler::setAllActorsNeedsUpdate();
		return true;
	}
	return false;
}

void							GameState::handleTick(void) {
	ActorHandler::tickAllActors();
}

// Out stream overload for testing
std::ostream					&operator<<(std::ostream &o, GameState const &i) {
	return o << "Game State Info:" << &i << std::endl;
}
