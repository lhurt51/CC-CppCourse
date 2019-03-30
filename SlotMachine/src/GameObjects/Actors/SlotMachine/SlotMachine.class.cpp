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
#include "SlotMachine.class.hpp"

// Initializing the player sprite
const std::string playerSprite = "Slot Machine";

// Default constructor to initialize all attributes
SlotMachine::SlotMachine(void) : Actor(Vector2D<uint_fast32_t>(DEFAULT_SPAWN), playerSprite) {
	return;
}

// Copy constructor
SlotMachine::SlotMachine(SlotMachine const &src) : Actor(src) {
	*this = src;
	return;
}

// Deconstructor
SlotMachine::~SlotMachine(void) {
	return;
}

// Overload equals operators for copy constructor
SlotMachine&			SlotMachine::operator=(SlotMachine const &rhs) {
	if (this != &rhs) {

	}
	return *this;
}

// Getters --

// Setters --

// Overloaded Public Actor Method
void					SlotMachine::tick(void) {

}
