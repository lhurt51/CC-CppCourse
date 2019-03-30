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
#include "StartGameItem.class.hpp"
#include "Handlers/GameStateHandler.class.hpp"

// Default constructors to initialize the pos and sprite
StartGameItem::StartGameItem(Vector2D<uint_fast32_t> const pos) : MenuItem(pos, "Start") {
	return;
}

// Copy constructor
StartGameItem::StartGameItem(StartGameItem const &src) : MenuItem(src) {
	*this = src;
	return;
}

// De-constructor
StartGameItem::~StartGameItem(void) {
	return;
}

// Overload equals operator
StartGameItem		&StartGameItem::operator=(StartGameItem const &rhs) {
	if (this != &rhs) {}
	return *this;
}

void			StartGameItem::_execute(void) {
	GameStateHandler::setCurState(PLAYING);
}
