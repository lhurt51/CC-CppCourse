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
#include "ExitGameItem.class.hpp"
#include "Handlers/GameStateHandler.class.hpp"

// Default constructors to initialize the pos and sprite
ExitGameItem::ExitGameItem(Vector2D<uint_fast32_t> const pos) : MenuItem(pos, "Exit") {
	return;
}

// Copy constructor
ExitGameItem::ExitGameItem(ExitGameItem const &src) : MenuItem(src) {
	*this = src;
	return;
}

// De-constructor
ExitGameItem::~ExitGameItem(void) {
	return;
}

// Overload equals operator
ExitGameItem		&ExitGameItem::operator=(ExitGameItem const &rhs) {
	if (this != &rhs) {}
	return *this;
}

void				ExitGameItem::_execute(void) {
	GameStateHandler::setCurState(EXITING);
}
